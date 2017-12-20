#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
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
    x = 0; static char c; int f = 0;
    while (c > '9' || c < '0') {
        c = get(); f ^= (c == '-');
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0'; c = get();
    }
    if (f) x = -x;
}
const int INF = 0x3f3f3f3f;
namespace Net {
    const int N = 130005;
    const int M = 250005;
    int head[N], sub;
    struct Edge {
        int to, nxt, v;
        Edge(void) {}
        Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
    } edge[M];
    void Add(int a, int b, int v) {
        edge[++sub] = Edge(b, head[a], v); head[a] = sub;
    }
    void Link(int a, int b, int v) {
        Add(a, b, v); Add(b, a, 0);
    }
    int h[N], S, T;
    void Init() {
        memset(head, 0, sizeof head);
        sub = 1;
    }
    bool bfs(void) {
        queue<int> qu;
        memset(h, -1, sizeof h);
        h[S] = 0; qu.push(S);
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for (int i = head[u], v; i; i = edge[i].nxt) {
                v = edge[i].to;
                if (~h[v] || !edge[i].v) continue;
                h[v] = h[u] + 1; qu.push(v);
            }
        }
        return ~h[T];
    }
    int dfs(int u, int flow) {
        if (u == T) return flow;
        int used = 0, w;
        for (int i = head[u], v; i; i = edge[i].nxt) {
            v = edge[i].to;
            if (h[v] != h[u] + 1) continue;
            w = dfs(v, min(flow - used, edge[i].v));
            used += w; edge[i].v -= w; edge[i ^ 1].v += w;
            if (used == flow) return used;
        }
        if (!used) h[u] = -1;
        return used;
    }
    int dinic() {
        int Ret = 0;
        while (bfs()) Ret += dfs(S, INF);
        return Ret;
    }
}
int Ans;
void Val(int x, int val) {
    using namespace Net;
    if (val > 0) Ans += val, Link(S, x, val);
    if (val < 0) Link(x, T, -val);
}
const int T = 110;
int N, M, v[T][T], idv[T][T], a[T * T], ida[T * T], RA, pT;
int main() {
    int i, j;
    Read(N); Read(M);
    Net::Init(); Net::S = ++pT; Net::T = ++pT;
    for (i = 1; i <= N; i++) {
        Read(a[i]); RA = max(RA, a[i]);
    }
    for (i = 1; i <= RA; i++) ida[i] = ++pT;
    for (i = 1; i <= N; i++)
        for (j = i; j <= N; j++) {
            Read(v[i][j]); idv[i][j] = ++pT;
        }
    for (i = 1; i <= N; i++)
        for (j = i; j <= N; j++) {
            if (i == j) {
                Val(idv[i][j], v[i][j] - a[i]);
            }
            else {
                Val(idv[i][j], v[i][j]);
                Net::Link(idv[i][j], idv[i + 1][j], INF);
                Net::Link(idv[i][j], idv[i][j - 1], INF);
            }
        }
    for (i = 1; i <= RA; i++) Val(ida[i], -M * i * i);
    for (i = 1; i <= N; i++) Net::Link(idv[i][i], ida[a[i]], INF);
    Ans -= Net::dinic();
    printf("%d\n", Ans);
    return 0;
}
