#include <bits/stdc++.h>
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
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
namespace SGT {
	const int N = V * 20;
	int ls[N], rs[N], sum[N], rt[V], pT;
	void Upd(int &x, int y, int l, int r, int p) {
		x = ++pT; ls[x] = ls[y]; rs[x] = rs[y]; sum[x] = sum[y] + 1;
		if (l == r) return;
		int Mid = (l + r) >> 1;
		if (p <= Mid) Upd(ls[x], ls[y], l, Mid, p);
		else Upd(rs[x], rs[y], Mid + 1, r, p);
	}
	int Query(int a1, int a2, int s1, int s2, int l, int r, int k) {
		if (l == r) return l;
		int Mid = (l + r) >> 1;
		int lsum = sum[ls[a1]] + sum[ls[a2]] - sum[ls[s1]] - sum[ls[s2]];
		if (k <= lsum) return Query(ls[a1], ls[a2], ls[s1], ls[s2], l, Mid, k);
		else return Query(rs[a1], rs[a2], rs[s1], rs[s2], Mid + 1, r, k - lsum);
	}
}
using SGT::rt; using SGT::Upd;
vector<int> g;
int id(int x) {
	return lower_bound(g.begin(), g.end(), x) - g.begin();
}
int n, m, M, a[V], lstAns;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int siz[V], dep[V], fa[V], top[V], pos[V], pT;
void Dfs1(int u) {
	siz[u] = 1; Upd(rt[u], rt[fa[u]], 0, M, id(a[u]));
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (fa[u] == v) continue;
		fa[v] = u; dep[v] = dep[u] + 1; Dfs1(v); siz[u] += siz[v];
	}
}
void Dfs2(int u, int path) {
	pos[u] = ++pT; top[u] = path;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return; Dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && v ^ k) Dfs2(v, v);
	}
}
int lca(int x, int y) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}
int Solve(int x, int y, int k) {
	int l = lca(x, y);
	return SGT::Query(rt[x], rt[y], rt[l], rt[fa[l]], 0, M, k);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); g.push_back(a[i]);
	}
	sort(g.begin(), g.end()); 
	g.erase(unique(g.begin(), g.end()), g.end()); M = g.size();
	int x, y, k;
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	Dfs1(1); Dfs2(1, 1);
	while (m--) {
		Read(x); Read(y); Read(k);
		lstAns = g[Solve(x ^ lstAns, y, k)];
		printf("%d", lstAns);
		if (m) putchar('\n');
	}
	return 0;
}
