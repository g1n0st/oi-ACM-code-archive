#include <bits/stdc++.h>
using namespace std;
typedef int BIT;
const int V = 100005;
const int B = 650;
char get() {
    static char buf[V], *p1 = buf, *p2 = buf;
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
int N, M, a[V], pre[V], pos[V];
int mx[V / B + 2], tag[V / B + 2];
int bel[V], bl[V / B + 2], br[V / B + 2];
struct Node {
    BIT rt, num;
    void clear() {
        rt = num = 0;
    }
} k[V / B + 2][V];
int find(int x) {
    while (x ^ pre[x]) x = (pre[x] = pre[pre[x]]);
    return x;
}
void pushDown(int x) {
    for (int i = bl[x]; i <= br[x]; i++) {
        a[i] = pos[find(i)]; k[x][a[i]].clear(); a[i] -= tag[x];
    }
    for (int i = bl[x]; i <= br[x]; i++) pre[i] = 0;
    tag[x] = 0;
}
void pushUp(int x) {
    mx[x] = 0;
    for (int i = bl[x]; i <= br[x]; i++) {
        mx[x] = max(mx[x], a[i]);
        if (!k[x][a[i]].rt) {
            k[x][a[i]].rt = i - bl[x] + 1; pre[i] = i; pos[i] = a[i];
        }
        else pre[i] = k[x][a[i]].rt + bl[x] - 1;
        k[x][a[i]].num++;
    }
}
void ModiVal(int x, int s, int t) {
    Node &S = k[x][s], &T = k[x][t];
    if (!S.rt) return;
    if (T.rt) {
        pre[S.rt + bl[x] - 1] = T.rt + bl[x] - 1;
    }
    else {
        T.rt = S.rt; pos[S.rt + bl[x] - 1] = t;
    }
    T.num += S.num; S.clear();
}
void Modify(int x, int v) {
    if (v * 2 <= mx[x] - tag[x]) {
        for (int i = tag[x] + 1; i <= tag[x] + v; i++)
            ModiVal(x, i, i + v);
        tag[x] += v;
    }
    else {
        for (int i = mx[x]; i > tag[x] + v; i--)
            ModiVal(x, i, i - v);
        mx[x] = min(mx[x], tag[x] + v);
    }
}
void Modify(int l, int r, int v) {
    int bL = bel[l], bR = bel[r];
    if (bL == bR) {
        pushDown(bL);
        for (int i = l; i <= r; i++) if (a[i] > v) a[i] -= v;
        pushUp(bL); return;
    }
    pushDown(bL); pushDown(bR);
    for (int i = l; i <= br[bL]; i++) if (a[i] > v) a[i] -= v;
    for (int i = bl[bR]; i <= r; i++) if (a[i] > v) a[i] -= v;
    pushUp(bL); pushUp(bR);
    for (int i = bL + 1; i < bR; i++) Modify(i, v);
}
int Query(int l, int r, int v) {
    int bL = bel[l], bR = bel[r], ret = 0;
    if (bL == bR) {
        for (int i = l; i <= r; i++) if (pos[find(i)] - tag[bL] == v) ret++;
        return ret;
    }
    for (int i = l; i <= br[bL]; i++) if (pos[find(i)] - tag[bL] == v) ret++;
    for (int i = bl[bR]; i <= r; i++) if (pos[find(i)] - tag[bR] == v) ret++;
    for (int i = bL + 1; i < bR; i++)
        if (v + tag[i] <= 100000) ret += k[i][v + tag[i]].num;
    return ret;
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(N); Read(M);
    for (int i = 1; i <= N; i++) Read(a[i]);
    for (int i = 1; i <= N; i++) bel[i] = (i - 1) / B + 1;
    for (int i = 1; i <= N; i++) br[bel[i]] = i;
    for (int i = N; i; i--) bl[bel[i]] = i;
    for (int i = 1; i <= bel[N]; i++) pushUp(i);
    int op, l, r, x; int cnt = 0;
    while (M--) {
        Read(op); Read(l); Read(r); Read(x);
        if (op & 1) Modify(l, r, x);
        else {
            printf("%d\n", Query(l, r, x));
        }
    }
    return 0;
}
