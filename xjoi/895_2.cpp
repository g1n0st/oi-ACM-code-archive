#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long U;
const int V = 100010;
U Rd() {
    return (((U)rand() << 16 | rand()) << 16 | rand());
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
int head[V], sub;
struct Edge {
    int to, nxt, v;
    Edge(int to = 0, int nxt = 0, int v = 0) : to(to), nxt(nxt) , v(v) {}
} edge[V << 1];
void Add(int a, int b, int v) {
    edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
 
int n, m, Sa, cir[V], tr[V];
int dep[V], siz[V], fa[V], pos[V], top[V], vis[V], id[V], pT;
void dfs1(int u) {
    vis[u] = 1; siz[u] = 1;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (vis[v]) continue;
        tr[edge[i].v] = 1;
        fa[v] = u; dep[v] = dep[u] + 1; dfs1(v); siz[u] += siz[v];
    }
}
void dfs2(int u, int path) {
    id[pos[u] = ++pT] = u; top[u] = path;
    int k = 0;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (!tr[edge[i].v]) continue;
        if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
    }
    if (!k) return; dfs2(k, path);
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (!tr[edge[i].v]) continue;
        if (dep[v] > dep[u] && v != k) dfs2(v, v);
    }
}
U tag[V << 2];
map<U, int> mp;
void modify(int o, int l, int r, int L, int R, U v) {
    if (l >= L && r <= R) {
        tag[o] ^= v; return ;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) modify(o << 1, l, mid, L, R, v);
    if (mid < R) modify(o << 1 | 1, mid + 1, r, L, R, v);
}
void modify(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    U val = Rd();
    while (top[u] ^ top[v]) {
        modify(1, 1, n, pos[top[v]], pos[v], val);
        v = fa[top[v]];
    }
    if (u ^ v) modify(1, 1, n, pos[u] + 1, pos[v], val);
    mp[val]++;
}
void query(int o, int l, int r, U val) {
    val ^= tag[o];
    if (l == r) {
        if (l == 1) return ;
        mp[val]++; return ;
    }
    int mid = (l + r) >> 1;
    query(o << 1, l, mid, val); query(o << 1 | 1, mid + 1, r, val);
}
int x[V], y[V];
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("b.txt", "w", stdout);
    Read(n); Read(m);
    for (int i = 1; i <= m; i++) {
        Read(x[i]); Read(y[i]);
        if (x[i] == y[i]) {
            Sa++; cir[i] = 1; continue;
        }
        Add(x[i], y[i], i); Add(y[i], x[i], i);
    }
    dfs1(1); dfs2(1, 1);
    for (int i = 1; i <= m; i++) {
        if (!tr[i] && !cir[i]) modify(x[i], y[i]);
    }
    query(1, 1, n, 0);
    LL ans = 0;
    ans += (LL)mp[0] * (m - mp[0]);
    for (map<U, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
        ans += (LL)it->second * (it->second - 1) / 2;
    }
    cout << ans << endl;
    return 0;
}
