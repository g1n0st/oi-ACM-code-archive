#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000010;
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

LL ans;

int path[V], tree[V], st[V];
int getf(int *f, int x) {
	return f[x] < 0 ? x : f[x] = getf(f, f[x]);
}
void merge(int u, int v, int w) {
	u = getf(st, u); v = getf(st, v);
	if (u ^ v) {
		ans += w; st[u] = v;
	}
}
typedef pair<int, int> PI;
typedef pair<PI, PI> PIII;
typedef pair<PI, int> PII;
#define x first
#define y second

PIII d[V];
vector<PI> lim[V];

int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int dep[V], siz[V], fa[V], top[V];
void dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; dep[v] = dep[u] + 1; dfs1(v); siz[u] += siz[v];
	}
}
void dfs2(int u, int path) {
	top[u] = path; int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (siz[v] > siz[k]) k = v;
	}
	if (!k) return; dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (k ^ v) dfs2(v, v);
	}
}
int LCA(int u, int v) {
	while (top[u] ^ top[v]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
		v = fa[top[v]];
	}
	return dep[u] < dep[v] ? u : v;
}
int n, m, p;
int id[V], li[V], L[V], R[V], t[V], len;
PI g[V];
void dfs(int u, int v, int w) {
	if (u ^ v) merge(li[u], li[v], w);
	path[getf(path, u)] = u + 1;
	for (int i = getf(path, 0); i <= len; i = getf(path, i + 1)) {
		int p = lower_bound(t + L[u], t + R[u] + 1, i) - t;
		if (t[p] ^ i) dfs(i, v, w);
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Read(p);
	for (int i = 2; i <= n; i++) {
		Read(fa[i]); Add(fa[i], i);
	}
	dfs1(1); dfs2(1, 1);
	for (int i = 1; i <= n; i++) st[i] = tree[i] = -1;
	int u, v, w, day;
	for (int i = 1; i <= m; i++) {
		Read(u); Read(v); Read(w);
		d[i] = PIII(PI(w, i), PI(u, v));
	}
	sort(d + 1, d + 1 + m);
	for (int i = 1; i <= p; i++) {
		Read(w); Read(u); Read(v);
		lim[w].emplace_back(PI(u, v));
	}
	for (int i = 1; i <= m; i++) {
		day = d[i].x.y; w = d[i].x.x; u = d[i].y.x; v = d[i].y.y;
		int lca = LCA(u, v); len = dep[u] + dep[v] - (dep[lca] << 1);
		if (len > lim[day].size()) {
			while (dep[u = getf(tree, u)] > dep[lca]) merge(u, tree[u] = fa[u], w);
			while (dep[v = getf(tree, v)] > dep[lca]) merge(v, tree[v] = fa[v], w);
			continue;
		}
		int t1 = 0, t2 = 0;
		while (u ^ lca) {
			id[li[t1] = u] = t1; u = fa[u]; ++t1;
		}
		while (v ^ lca) {
			id[li[t1] = v] = t1; v = fa[v]; ++t1;
		}
		id[li[t1] = lca] = t1; ++t1;
		for (auto e : lim[day]) {
			g[++t2] = PI(id[e.x], id[e.y]); g[++t2] = PI(id[e.y], id[e.x]);
		}
		for (int i = 0; i <= len + 1; i++) path[i] = -1;
		sort(g + 1, g + 1 + t2); t[1] = g[1].y; L[g[1].x] = 1;
		for (int i = 2; i <= t2 + 1; i++) {
			t[i] = g[i].y; 
			if (g[i].x ^ g[i - 1].x) {
				R[g[i - 1].x] = i - 1;
				if (i != t2 + 1) L[g[i].x] = i;
			}
		}
		for (int i = 0; i <= len; i++) if (getf(path, i) == i) dfs(i, i, w);
	}
	cout << ans << endl;
	return 0;
}
