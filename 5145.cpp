#include <bits/stdc++.h>
const int V = 100005;
const int B = 512;
const int K = 9;
const int vB = (V / B) + 5;
using namespace std;
char get() {
    static char buf[V << 1], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, V, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}
void Read(int &x) {
    x = 0; static char c;
    for (; !(c >= '0' && c <= '9'); c = get());
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int N, M, a[V], di[V], nB, nVal;
int cnt[vB][V], Bcnt[vB][vB], id[vB][V], fid[vB][V];
int bL[vB], bR[vB], bel[V];
void pushUp(int x) {
    int pT = 0, L = bL[x], R = bR[x];
    for (int i = 1; i <= B; i++) id[x][fid[x][i]] = 0;
    for (int i = L; i <= R; i++)
        if (!id[x][a[i]]) {
            id[x][a[i]] = ++pT; fid[x][pT] = a[i];
        }
    for (int i = L; i <= R; i++) di[i] = id[x][a[i]];
}
void pushDown(int x) {
    int L = bL[x], R = bR[x];
    for (int i = L; i <= R; i++) a[i] = fid[x][di[i]];
}
void Modify(int l, int r, int x, int y) {
    int L = bel[l], R = bel[r], X = x >> K, Y = y >> K;
    if (cnt[R][x] - cnt[L - 1][x] == 0) return;
    for (int i = nB; i >= L; i--) {
        cnt[i][x] -= cnt[i - 1][x]; cnt[i][y] -= cnt[i - 1][y];
        Bcnt[i][X] -= Bcnt[i - 1][X]; Bcnt[i][Y] -= Bcnt[i - 1][Y];
    }
    if (L == R) {
        pushDown(L); int n = 0;
        for (int i = l; i <= r; i++)
            if (a[i] == x) {
                a[i] = y; n++;
            } cnt[L][x] -= n; cnt[L][y] += n; Bcnt[L][X] -= n; Bcnt[L][Y] += n;
        pushUp(L);
    }
    else {
        pushDown(L); pushDown(R); int n = 0;
        for (int i = l; i <= bR[L]; i++)
            if (a[i] == x) {
                a[i] = y; n++;
            } cnt[L][x] -= n; cnt[L][y] += n; Bcnt[L][X] -= n; Bcnt[L][Y] += n;
            n = 0;
        for (int i = bL[R]; i <= r; i++)
            if (a[i] == x) {
                a[i] = y; n++;
            } cnt[R][x] -= n; cnt[R][y] += n; Bcnt[R][X] -= n; Bcnt[R][Y] += n;
        pushUp(L); pushUp(R);
        for (int i = L + 1; i < R; i++) if (cnt[i][x]) {
            if (cnt[i][y]) {
                pushDown(i); n = 0;
                for (int j = bL[i]; j <= bR[i]; j++) if (a[j] == x) {
                    a[j] = y; n++;
                } cnt[i][x] -= n; cnt[i][y] += n; Bcnt[i][X] -= n; Bcnt[i][Y] += n;
                pushUp(i);
            }
            else {
                Bcnt[i][Y] += cnt[i][x]; Bcnt[i][X] -= cnt[i][x];
                cnt[i][y] += cnt[i][x]; cnt[i][x] = 0;
                int h = id[i][x]; id[i][y] = h; fid[i][h] = y; id[i][x] = 0;
            }
        }
    }
    for (int i = L; i <= nB; i++) {
        cnt[i][x] += cnt[i - 1][x]; cnt[i][y] += cnt[i - 1][y];
        Bcnt[i][X] += Bcnt[i - 1][X]; Bcnt[i][Y] += Bcnt[i - 1][Y];
    }
}
int ls[V], Bls[vB];
void Kth(int l, int r, int x) {
    int L = bel[l], R = bel[r], X = x / B;
    if (L == R) {
        pushDown(L);
        for (int i = l; i <= r; i++) ls[i] = a[i];
        nth_element(ls + l, ls + l + x - 1, ls + r + 1);
        printf("%d\n", ls[l + x - 1]);
        for (int i = l; i <= r; i++) ls[i] = 0;
        return;
    }
    pushDown(L); pushDown(R);
    for (int i = l; i <= bR[L]; i++) ls[a[i]]++, Bls[a[i] >> K]++;
    for (int i = bL[R]; i <= r; i++) ls[a[i]]++, Bls[a[i] >> K]++;
    int sum = 0;
    for (int i = 0; i <= nVal; i++)
        if (Bls[i] + Bcnt[R - 1][i] - Bcnt[L][i] + sum >= x) {
            for (int j = i * B; j < (i + 1) * B; j++)
                if (ls[j] + cnt[R - 1][j] - cnt[L][j] + sum >= x) {
                    printf("%d\n", j); i = j = 1 << 30; break;
                }
                else sum += ls[j] + cnt[R - 1][j] - cnt[L][j];
        }
        else sum += Bls[i] + Bcnt[R - 1][i] - Bcnt[L][i];
        for (int i = l; i <= bR[L]; i++) ls[a[i]]--, Bls[a[i] >> K]--;
        for (int i = bL[R]; i <= r; i++) ls[a[i]]--, Bls[a[i] >> K]--;
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
 
    Read(N); Read(M); nB = (N - 1) / B + 1; nVal = V >> K;
    for (int i = 1; i <= N; i++) bel[i] = (i - 1) / B + 1;
    for (int i = 1; i <= N; i++) bR[bel[i]] = i;
    for (int i = N; i; i--) bL[bel[i]] = i;
    for (int i = 1; i <= N; i++) Read(a[i]);
    for (int i = 1; i <= nB; i++) pushUp(i);
    for (int i = 1; i <= nB; i++) {
        for (int j = 1; j < V; j++) cnt[i][j] += cnt[i - 1][j];
        for (int j = 0; j <= nVal; j++) Bcnt[i][j] += Bcnt[i - 1][j];
        for (int j = bL[i]; j <= bR[i]; j++) cnt[i][a[j]]++;
        for (int j = bL[i]; j <= bR[i]; j++) Bcnt[i][a[j] >> K]++;
    }
    int op, l, r, x, y;
    while (M--) {
        Read(op); Read(l); Read(r);
        if (op & 1) {
            Read(x); Read(y); Modify(l, r, x, y);
        }
        else {
            Read(x); Kth(l, r, x);
        }
    }
    return 0;
}
