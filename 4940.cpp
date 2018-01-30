#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef const int &CI;
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
int bel[V]; LL Ans[V * 10];
struct Node {
    int l, r, f, id;
    Node(CI l = 0, CI r = 0, CI f = 0, CI id = 0) : l(min(l, r)), r(max(l, r)), f(f), id(id) {}
    friend bool operator < (const Node &a, const Node &b) {
        if (bel[a.l] ^ bel[b.l]) return a.l < b.l;
        return (bel[a.l] & 1) ? a.r < b.r : a.r > b.r;
    }
} v[V * 45]; int tot;
 
int head[V], sub;
struct Edge {
    int to, nxt;
    Edge(CI to = 0, CI nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
    edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
 
int siz[V], pos[V], top[V], dep[V], fa[V], pT, id[V], epos[V];
void Dfs1(int u) {
    siz[u] = 1;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (v == fa[u]) continue;
        fa[v] = u; dep[v] = dep[u] + 1; Dfs1(v); siz[u] += siz[v];
    }
}
void Dfs2(int u, int path) {
    id[pos[u] = ++pT] = u; top[u] = path;
    int k = 0;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
    }
    if (!k) return; Dfs2(k, path);
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (dep[v] > dep[u] && v ^ k) Dfs2(v, v);
    }
}
int find(int x, int y) {
    while (top[x] ^ top[y]) {
        if (fa[top[x]] == y) return top[x];
        x = fa[top[x]];
    }
    return id[pos[y] + 1];
}
int X[V], Y[V];
int N, M, Q, rQ, Rt, B, a[V], b[V];
int tx, ty, wx[5], wy[5], fx[5], fy[5];
void Work(int x, int &tot, int *w, int *f) {
    tot = 0;
    if (x == Rt) {
        ++tot; w[tot] = N; f[tot] = 1;
    }
    else if (pos[x] >= pos[Rt] && pos[x] <= epos[Rt]) {
        ++tot; w[tot] = epos[x]; f[tot] = 1;
        ++tot; w[tot] = pos[x] - 1; f[tot] = -1;
    }
    else if (pos[Rt] < pos[x] || pos[Rt] > epos[x]) {
        ++tot; w[tot] = epos[x]; f[tot] = 1;
        ++tot; w[tot] = pos[x] - 1; f[tot] = -1;
    }
    else {
        int v = find(Rt, x);
        ++tot; w[tot] = N; f[tot] = 1;
        ++tot; w[tot] = epos[v]; f[tot] = -1;
        ++tot; w[tot] = pos[v] - 1; f[tot] = 1;
    }
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int op, x, y;
    Read(N); Read(Q); Rt = 1; B = sqrt(N) * 2;
    for (int i = 1; i <= N; i++) {
        Read(a[i]); b[i] = a[i]; bel[i] = (i - 1) / B + 1;
    }
    sort(b + 1, b + 1 + N); M = unique(b + 1, b + 1 + N) - b;
    for (int i = 1; i <= N; i++) a[i] = lower_bound(b + 1, b + M, a[i]) - b;
    for (int i = 1; i < N; i++) {
        Read(x); Read(y); Add(x, y); Add(y, x);
    }
    Dfs1(1); Dfs2(1, 1);
    for (int i = 1; i <= N; i++) b[pos[i]] = a[i];
    for (int i = 1; i <= N; i++) epos[i] = pos[i] + siz[i] - 1;
    for (int i = 1; i <= Q; i++) {
        Read(op); Read(x);
        if (op & 1) Rt = x;
        else {
            ++rQ; Read(y); Work(x, tx, wx, fx); Work(y, ty, wy, fy);
            for (int j = 1; j <= tx; j++)
                for (int k = 1; k <= ty; k++)
                    v[++tot] = Node(wx[j], wy[k], fx[j] * fy[k], rQ);
        }
    }
    sort(v + 1, v + 1 + tot);
    int L = 0, R = 0; LL Now = 0;
    for (int i = 1; i <= tot; i++) {
        while (L < v[i].l) L++, Now += X[b[L]], Y[b[L]]++;
        while (R < v[i].r) R++, Now += Y[b[R]], X[b[R]]++;
        while (L > v[i].l) Y[b[L]]--, Now -= X[b[L]], L--;
        while (R > v[i].r) X[b[R]]--, Now -= Y[b[R]], R--;
        Ans[v[i].id] += v[i].f * Now;
    }
    for (int i = 1; i <= rQ; i++) printf("%lld\n", Ans[i]);
    return 0;
}
