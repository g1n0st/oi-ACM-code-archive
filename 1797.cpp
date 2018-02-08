#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
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
    for (; !isdigit(c); c = get());
    for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
namespace Net {
    const int N = 100010;
    const int M = 1000100;
    int S, T, tot;
    namespace E {
        int head[N], cur[N], sub;
        struct Edge {
            int to, nxt, v;
            Edge() {}
            Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
        } edge[M];
    }
    using namespace E;
    void Init(int n) {
        memset(head, 0, sizeof head); sub = 1; tot = n;
    }
    void Add(int a, int b, int v) {
        edge[++sub] = Edge(b, head[a], v); head[a] = sub;
    }
    void Link(int a, int b, int v) {
        Add(a, b, v); Add(b, a, 0);
    }
    int h[N];
    bool bfs() {
        memset(h, -1, sizeof h); h[S] = 0;
        queue<int> qu; qu.push(S);
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for (int i = head[u], v; i; i = edge[i].nxt) {
                v = edge[i].to; if (~h[v] || !edge[i].v) continue;
                h[v] = h[u] + 1; qu.push(v);
            }
        }
        return ~h[T];
    }
    LL dfs(int u, LL flow) {
        if (u == T) return flow;
        LL used = 0, w;
        for (int &i = cur[u], v; i; i = edge[i].nxt) {
            v = edge[i].to; if (h[v] != h[u] + 1) continue;
            w = dfs(v, min((LL)edge[i].v, flow - used));
            used += w; edge[i].v -= w; edge[i ^ 1].v += w;
            if (used == flow) return flow;
        }
        if (!used) h[u] = -1;
        return used;
    }
    LL dinic() {
        LL r = 0;
        while (bfs()) {
            for (int i = 1; i <= tot; i++) cur[i] = head[i];
            r += dfs(S, 1LL << 60);
        }
        return r;
    }
}
int N, M;
int scc[V], low[V], dfn[V], s[V], t, pT, pT1;
void Tarjan(int u) {
    using namespace Net::E;
    low[u] = dfn[u] = ++pT; s[++t] = u;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (!edge[i].v) continue;
        if (!dfn[v]) {
            Tarjan(v); low[u] = min(low[u], low[v]);
        }
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++pT1; for (int v = -1; v != u; ) v = s[t--], scc[v] = pT1;
    }
}
int a1[V * 10], a2[V * 10];
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(N); Read(M); Read(Net::S); Read(Net::T); Net::Init(N);
    int u, v, w;
    for (int i = 1; i <= M; i++) {
        Read(u); Read(v); Read(w);
        Net::Link(u, v, w);
    }
    Net::dinic();
    using namespace Net::E;
    for (int i = 1; i <= N; i++)
        if (!dfn[i]) Tarjan(i);
    for (int u = 1; u <= N; u++)
        for (int i = head[u], v; i; i = edge[i].nxt) {
            v = edge[i].to; if (i & 1) continue;
            if (edge[i].v) continue;
            a1[i >> 1] = scc[u] != scc[v];
            a2[i >> 1] = (scc[u] == scc[Net::S] && scc[v] == scc[Net::T]);
        }
    for (int i = 1; i <= M; i++) {
        putchar('0' + a1[i]); putchar(' '); putchar('0' + a2[i]); putchar('\n');
    }
    return 0;
}
