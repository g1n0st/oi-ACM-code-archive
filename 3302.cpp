#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 1LL << 60;
const int V = 100010;
LL Min(LL a, LL b) {
    return a < b ? a : b;
}
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
int head[V], sub;
struct Edge {
    int to, nxt;
    Edge() {
    }
    Edge(int to, int nxt) : to(to), nxt(nxt) {
    }
} edge[V * 2];
void Add(int a, int b) {
    edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
 
int N, a[V], fa[V], dep[V];
LL fi[V], se[V], res[V], sum[V], Ans;
void Dfs(int u) {
    sum[u] = a[u];
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to;
        if (v == fa[u]) continue;
        fa[v] = u; dep[v] = dep[u] + 1; Dfs(v);
        sum[u] += sum[v]; res[u] += res[v] + sum[v];
        if (!fi[u] || sum[v] > sum[fi[u]]) {
            se[u] = fi[u]; fi[u] = v;
        } else if (!se[u] || sum[v] > sum[se[u]])
            se[u] = v;
    }
}
int X;
void Cet(LL &r, int root, int x, LL k) {
    r = Min(r, k);
    int v = fi[x];
    if (v == X || sum[se[x]] > sum[fi[x]]) v = se[x];
    if (!v) return ;
    Cet(r, root, v, k + sum[root] - 2 * sum[v]);
}
void Work(int u) {
    for (int i = head[u], v; i; i = edge[i].nxt) {
        X = v = edge[i].to;
        if (v == fa[u]) continue;
        LL gx = INF, gy = INF;
        for (int j = u; j; j = fa[j]) sum[j] -= sum[v];
        Cet(gy, v, v, res[v]);
        Cet(gx, 1, 1, res[1] - res[v] - sum[v] * dep[v]);
        Ans = Min(Ans, gx + gy);
        for (int j = u; j; j = fa[j]) sum[j] += sum[v];
        Work(v);
    }
}
int main(void) {
    int i, j, x, y;
    //freopen("in.txt", "r", stdin);
    Read(N);
    for (i = 1; i < N; i++) {
        Read(x); Read(y);
        Add(x, y); Add(y, x);
    }
    for (i = 1; i <= N; i++) Read(a[i]);
    Dfs(1);
    Ans = INF;
    Work(1);
    cout << Ans << endl;
    return 0;
}
