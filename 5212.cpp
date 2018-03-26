#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 500100;
char get() {
    static char buf[V], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, V, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}
template<class T> void Read(T &x) {
    x = 0; static char c;
    for (; !isdigit(c); c = get());
    for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
void Wt(LL x) {
    printf("%lld\n", x);
}
int head[V], sub;
struct Edge {
    int to, nxt;
    Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
    edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int n, Q; LL ans;
int fa[V], c[V][2];
LL mx[V], s[V], a[V], ms[V], mn[V], mk[V], tag[V];
void dfs(int u, int fa) {
    mx[u] = s[u] = a[u]; ::fa[u] = fa;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (v == fa) continue;
        dfs(v, u); s[u] += s[v]; mx[u] = max(mx[u], s[v]);
    }
    ms[u] = s[u];
    if (s[u] - 2 * mx[u] + 1 > 0) {
        mk[u] = 1; mn[u] = s[u] - 2 * mx[u] + 1;
    }
    else {
        mn[u] = 1LL << 60;
    }
    ans += min(s[u] - 1, 2 * (s[u] - mx[u]));
}
inline void set0(int x, LL v) {
    s[x] += v; mx[x] += v; tag[x] += v; ms[x] += v; mn[x] -= v;
}
void pushDown(int x) {
    int &l = c[x][0], &r = c[x][1];
    if (tag[x]) {
        if (l) set0(l, tag[x]); if (r) set0(r, tag[x]); tag[x] = 0;
    }
}
void pushUp(int x) {
    int &l = c[x][0], &r = c[x][1];
    ms[x] = max(max(ms[l], ms[r]), s[x]);
    mn[x] = min(mn[l], mn[r]); mk[x] = mk[l] + mk[r];
    if (s[x] - mx[x] * 2 + 1 > 0) {
        mn[x] = min(mn[x], s[x] - mx[x] * 2 + 1); mk[x]++;
    }
}
int Rt(int x) {
    return c[fa[x]][0] != x && c[fa[x]][1] != x;
}
void rotate(int x) {
    int y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
    if (!Rt(y)) {
        if (c[z][0] == y) c[z][0] = x;
        else c[z][1] = x;
    }
    fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
    c[y][l] = c[x][r]; c[x][r] = y;
    pushUp(y); pushUp(x);
}
int st[V], t;
void splay(int x) {
    st[++t] = x;
    for (int i = x; !Rt(i); i = fa[i]) st[++t] = fa[i];
    while (t) pushDown(st[t--]);
    while (!Rt(x)) {
        int y = fa[x], z = fa[y];
        if (!Rt(y)) {
            if ((c[z][0] == y) ^ (c[y][0] == x)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}
inline LL val(int x) {
    return min(s[x] - 1, 2 * (s[x] - mx[x]));
}
void Work(int x, int v) {
    if (!x) return;
    if (mn[x] > v) {
        ans += mk[x] * v; set0(x, v); return;
    }
    pushDown(x);
    Work(c[x][0], v); Work(c[x][1], v); ans -= val(x);
    s[x] += v; mx[x] += v; ans += val(x);
    pushUp(x);
}
void access(int ori, int x, int v) {
    for (int t = 0; x; t = x, x = fa[x]) {
        splay(x); ans -= val(x);
        if (x == ori) mx[x] = max(mx[x], a[x] += v); mx[x] = max(mx[x], ms[t]);
        s[x] += v; ms[x] = s[x]; ans += val(x); Work(c[x][0], v);
        if (mx[x] == ms[t]) c[x][1] = t;
        if (mx[x] != ms[c[x][1]]) c[x][1] = 0;
        pushUp(x);
    }
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(n); Read(Q); mn[0] = 1LL << 60;
    int x, y;
    for (int i = 1; i <= n; i++) Read(a[i]);
    for (int i = 1; i < n; i++) {
        Read(x); Read(y); Add(x, y); Add(y, x);
    }
    dfs(1, 0); Wt(ans);
    while (Q--) {
        Read(x); Read(y); access(x, x, y); Wt(ans);
    }
    return 0;
}
