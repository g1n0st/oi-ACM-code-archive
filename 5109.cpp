#include <bits/stdc++.h>
using namespace std;
const int V = 50100;
const int B = V / 32 + 1;
typedef long long LL;
typedef unsigned U;
U Rd() {
    return (U)rand() << 16 | rand();
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
    for (; !isdigit(c); c = get());
    for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
struct Bitset {
    U a[B];
    void operator |= (Bitset b) {
        for (int i = 0; i < B; i++) a[i] |= b.a[i];
    }
    void operator |= (int x) {
        a[x >> 5] |= (1u << (x & 31));
    }
    int Query(int x) {
        return (a[x >> 5] >> (x & 31)) & 1;
    }
} bg[V];
int head[V], sub;
struct Edge {
    int to, nxt, v;
    Edge() {}
    Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
} edge[V * 10];
void Add(int a, int b, int v) {
    edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
int N, M, S, T;
int vis[V]; LL dis[V];
void Spfa() {
    memset(dis, 0x3f, sizeof dis); dis[S] = 0;
    queue<int> qu; qu.push(S);
    while (!qu.empty()) {
        int u = qu.front(); qu.pop(); vis[u] = 0;
        for (int i = head[u], v; i; i = edge[i].nxt) {
            v = edge[i].to; if (dis[v] > dis[u] + edge[i].v) {
                dis[v] = dis[u] + edge[i].v;
                if (!vis[v]) {
                    vis[v] = 1; qu.push(v);
                }
            }
        }
    }
}
struct Node {
    int v; LL dis, val;
    Node() {}
    Node(int v, LL dis, LL val) : v(v), dis(dis), val(val) {}
    friend bool operator < (const Node &a, const Node &b) {
        return a.val != b.val ? a.val < b.val : a.dis > b.dis;
    }
} e[V]; int tot;
int fa[V];
U val[V];
void Dfs1(int u) {
    vis[u] = 1;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (dis[u] - dis[v] != edge[i].v) continue;
        if (!vis[v]) {
            fa[v] = u; Dfs1(v);
        }
        else {
            U vv = Rd(); val[u] ^= vv; val[fa[v]] ^= vv;
        }
    }
}
int n0, w0;
void Dfs2(int u) {
    vis[u] = 0; bg[u] |= u;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (dis[u] - dis[v] != edge[i].v) continue;
        if (vis[v]) {
            Dfs2(v); val[u] ^= val[v];
        }
        bg[u] |= bg[v];
    }
    if (val[u]) e[++tot] = Node(u, dis[u], val[u]), n0++;
    else w0++;
}
void Calc() {
 
    Dfs1(T); Dfs2(T);
    sort(e + 1, e + 1 + tot);
    int i = 1, j = 1, tmp;
    LL Ans = 0;
    for (; i <= tot; i = j) {
        tmp = 1;
        for (j++; j <= tot && e[i].val == e[j].val; j++) tmp += bg[e[i].v].Query(e[j].v);
        Ans += (LL)tmp * (j - i - tmp);
    }
    Ans += (LL)w0 * (N - w0 - n0);
    printf("%lld\n", Ans);
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int u, v, w;
    Read(N); Read(M); Read(S); Read(T);
    for (int i = 1; i <= M; i++) {
        Read(u); Read(v); Read(w); Add(u, v, w); Add(v, u, w);
    }
    Spfa();
    if (dis[T] == dis[N + 1]) printf("%lld\n", (LL)N * (N - 1) / 2);
    else Calc();
    return 0;
}
