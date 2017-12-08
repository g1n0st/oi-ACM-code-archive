#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
typedef long long LL;
const int V = 300010;
const int INF = 1 << 30;
using namespace std;
 
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
    while (c > '9' || c < '0') c = get();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = get();
    }
}
 
vector<int> s[V];
int N, M, K;
int ll[V], rr[V], vv[V];
int id[V], Ans[V], tag[V], Vis[V], tmp[V], T;
LL c[V];
int lowbit(int x) {
    return x & (-x);
}
LL Ask(int x) {
    LL Ret = 0;
    while (x) {
        Ret += c[x];
        x -= lowbit(x);
    }
    return Ret;
}
void Modify(int x, int v) {
    while (x <= M) {
        c[x] += v;
        x += lowbit(x);
    }
}
void Add(int x, int o) {
    if (ll[x] <= rr[x]) {
        Modify(ll[x], o * vv[x]);
        Modify(rr[x] + 1, (-o) * vv[x]);
    } else {
        Modify(1, o * vv[x]);
        Modify(rr[x] + 1, (-o) * vv[x]);
        Modify(ll[x], o * vv[x]);
    }
}
void Solve(int l, int r, int L, int R) {
    int i, j, v;
    if (l > r) return;
    if (L == R) {
        for (i = l; i <= r; i++) Ans[id[i]] = L;
        return;
    }
    int Mid = (L + R) >> 1;
    while (T < Mid) ++T, Add(T, 1);
    while (T > Mid) Add(T, -1), T--;
    int cnt = 0; LL tot;
    for (i = l; i <= r; i++) {
        tot = 0;
        for (j = 0; j < s[id[i]].size(); j++)
            if (v = s[id[i]][j], (tot += Ask(v)) >= tag[id[i]]) break;
        cnt += (Vis[i] = tot >= tag[id[i]]);
    }
    int t1 = l, t2 = l + cnt;
    for (i = l; i <= r; i++)
        if (Vis[i]) tmp[t1++] = id[i];
        else tmp[t2++] = id[i];
    for (i = l; i <= r; i++) id[i] = tmp[i];
    Solve(l, t1 - 1, L, Mid); Solve(t1, t2 - 1, Mid + 1, R);
}
int main(void) {
    int i, j, x, y;
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(N); Read(M);
    for (i = 1; i <= M; i++) {
        Read(x); s[x].push_back(i);
    }
    for (i = 1; i <= N; i++) Read(tag[i]);
    for (i = 1; i <= N; i++) id[i] = i;
    Read(K);
    for (i = 1; i <= K; i++) {
        Read(ll[i]); Read(rr[i]); Read(vv[i]);
    }
    ++K; ll[i] = 1; rr[i] = M; vv[i] = INF;
    Solve(1, N, 1, K);
    for (i = 1; i <= N; i++)
        if (Ans[i] ^ K) printf("%d\n", Ans[i]);
        else printf("NIE\n");
    return 0;
}
