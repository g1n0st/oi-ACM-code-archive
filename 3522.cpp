#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
char get(void) {
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
    Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V * 2];
void Add(int a, int b) {
    edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
LL poor[V * 10];
LL *f[V], *g[V], *pr, Ans;
int N, Mx[V], dep[V];
void CrtM(int x) {
    //cout << x << endl;
    pr += x;
}
void Dfs1(int u, int fa) {
    Mx[u] = u;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to;
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        Dfs1(v, u);
        if (dep[Mx[v]] > dep[Mx[u]])
            Mx[u] = Mx[v];
    }
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to;
        if (v == fa || (Mx[v] == Mx[u] && u != 1)) continue;
        v = Mx[v];
        CrtM(dep[v] - dep[u] + 1);
        f[v] = pr;
        CrtM(1);
        g[v] = pr;
        CrtM((dep[v] - dep[u]) * 2 + 1);
    }
}
void Dfs2(int u, int fa) {
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to;
        if (v == fa) continue;
        Dfs2(v, u);
        if (Mx[u] == Mx[v]) {
            f[u] = f[v] - 1;
            g[u] = g[v] + 1;
        }
    }
    Ans += g[u][0];
    f[u][0] = 1LL;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to;
        if (v == fa || Mx[u] == Mx[v]) continue;
        for (int j = 0; j <= dep[Mx[v]] - dep[u]; j++)
            Ans += g[v][j + 1] * f[u][j] + g[u][j] * f[v][j - 1];
        for (int j = 0; j <= dep[Mx[v]] - dep[u]; j++) {
            g[u][j - 1] += g[v][j];
            g[u][j + 1] += f[u][j + 1] * f[v][j];
            f[u][j + 1] += f[v][j];
        }
    }
}
int main(void) {
    int i, j, x, y;
    //freopen("in.txt", "r", stdin);
    //freopen("A.txt", "w", stdout);
    Read(N);
    for (i = 1; i < N; i++) {
        Read(x); Read(y);
        Add(x, y); Add(y, x);
    }
    memset(poor, 0, sizeof poor); pr = poor + 10;
    Dfs1(1, 0); 
    Dfs2(1, 0);
    cout << Ans << endl;
    return 0;
}
