#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;
const int V = 200010;
const LL INF = 123456789123456789LL;
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
int N, M;
int head[V], sub;
struct Edge {
    int to, nxt, v;
    Edge() {}
    Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
} edge[V * 2];
void Add(int a, int b, int v) {
    edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
LL dis[V];
int fa[V], dep[V], siz[V], pos[V], top[V], id[V], pT;
void Dfs1(int u) {
    siz[u] = 1;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (v == fa[u]) continue;
        fa[v] = u; dep[v] = dep[u] + 1; dis[v] = dis[u] + edge[i].v;
        Dfs1(v); siz[u] += siz[v];
    }
}
void Dfs2(int u, int path) {
    pos[u] = ++pT; id[pT] = u; top[u] = path;
    int k = 0;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to;
        if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
    }
    if (!k) return; Dfs2(k, path);
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to;
        if (dep[v] > dep[u] && v != k) Dfs2(v, v);
    }
}
int lca(int x, int y) {
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
struct Li {
    LL k, b;
    Li() {}
    Li(LL k, LL b) : k(k), b(b) {}
    LL f(LL x) {
        return k * x + b;
    }
} li[V << 2];
LL cross(Li a, Li b) {
    return (LL)floor((a.b - b.b) / (b.k - a.k));
}
LL vy[V << 2]; int tag[V << 2];
void Build(int o, int l, int r) {
    vy[o] = INF; if (l == r) return;
    int Mid = (l + r) >> 1;
    Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
}
void Merge(int o, int l, int r) {
    if (l < r) vy[o] = min(vy[o << 1], vy[o << 1 | 1]); else vy[o] = INF;
    if (tag[o]) vy[o] = min(vy[o], min(li[o].f(dis[id[l]]), li[o].f(dis[id[r]])));
}
void Modify(int o, int l, int r, Li x) {
    int Mid = (l + r) >> 1;
    if (!tag[o]) {
        li[o] = x;  tag[o] = 1; Merge(o, l, r); return;
    }
    int lf = (x.f(dis[id[l]]) - li[o].f(dis[id[l]])) < 0;
    int rf = (x.f(dis[id[r]]) - li[o].f(dis[id[r]])) < 0;
    if (lf && rf) {
        li[o] = x;
    }
    else if (lf || rf) {
        LL t = cross(x, li[o]);
        if (t <= dis[id[Mid]] && lf) Modify(o << 1, l, Mid, x);
        if (t <= dis[id[Mid]] && rf) Modify(o << 1, l, Mid, li[o]), li[o] = x;
        if (dis[id[Mid]] < t && rf) Modify(o << 1 | 1, Mid + 1, r, x);
        if (dis[id[Mid]] < t && lf) Modify(o << 1 | 1, Mid + 1, r, li[o]), li[o] = x;
    }
    else return;
    Merge(o, l, r);
}
void Cha(int o, int l, int r, int L, int R, Li x) {
    int Mid = (l + r) >> 1;
    if (l >= L && r <= R) {
        Modify(o, l, r, x); return;
    }
    if (L <= Mid) Cha(o << 1, l, Mid, L, R, x);
    if (Mid < R) Cha(o << 1 | 1, Mid + 1, r, L, R, x);
    Merge(o, l, r);
}
LL Ans;
void Query(int o, int l, int r, int L, int R) {
    if (l == L && r == R) {
        Ans = min(Ans, vy[o]); return;
    }
    if (tag[o]) Ans = min(Ans, min(li[o].f(dis[id[L]]), li[o].f(dis[id[R]])));
    int Mid = (l + r) >> 1;
    if (R <= Mid) Query(o << 1, l, Mid, L, R);
    else if (Mid < L) Query(o << 1 | 1, Mid + 1, r, L, R);
    else {
        Query(o << 1, l, Mid, L, Mid);
        Query(o << 1 | 1, Mid + 1, r, Mid + 1, R);
    }
}
int main() {
    int i, j, x, y, w; Read(N); Read(M);
    Build(1, 1, N);
    for (i = 1; i < N; i++) {
        Read(x); Read(y); Read(w);
        Add(x, y, w); Add(y, x, w);
    }
    Dfs1(1); Dfs2(1, 1);
    int op, z, u, v; LL tmp;
    while (M--) {
        Read(op); Read(x); Read(y);
        if (op & 1) {
            Read(u); Read(v); z = lca(x, y);
            tmp = dis[x] * u + v;
            for (; top[x] ^ top[z]; x = fa[top[x]])
                Cha(1, 1, N, pos[top[x]], pos[x], Li(-u, tmp));
            Cha(1, 1, N, pos[z], pos[x], Li(-u, tmp));
            tmp -= (dis[z] * 2) * u;
            for (; top[y] ^ top[z]; y = fa[top[y]])
                Cha(1, 1, N, pos[top[y]], pos[y], Li(u, tmp));
            Cha(1, 1, N, pos[z], pos[y], Li(u, tmp));
        }
        else {
            Ans = INF;
            while (top[x] ^ top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                Query(1, 1, N, pos[top[x]], pos[x]);
                x = fa[top[x]];
            }
            if (dep[x] > dep[y]) swap(x, y);
            Query(1, 1, N, pos[x], pos[y]);
            printf("%lld\n", Ans);
        }
    }
    return 0;
}
