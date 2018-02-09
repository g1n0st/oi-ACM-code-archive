#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
const int M_R = 50;
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
int n, a[V], m;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int fa[V], dep[V], siz[V], pos[V], top[V], id[V], pT;
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; dep[v] = u; Dfs1(v); siz[u] += siz[v];
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
int lca(int x, int y) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}
int s[V], t;
int Check(int x, int y) {
	int l = lca(x, y);
	s[t = 1] = a[l];
	while (x ^ l) {
		s[++t] = a[x], x = fa[x];
		if (t > M_R) return 1;
	}
	while (y ^ l) {
		s[++t] = a[y], y = fa[y];
		if (t > M_R) return 1;
	}
	sort(s + 1, s + t + 1);
	for (int i = 3; i <= t; i++)
		if (s[i] - s[i - 2] < s[i - 1]) return 1;
	return 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	Read(n); Read(m);
	int op, x, y;
	for (int i = 1; i <= n; i++) Read(a[i]);
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	Dfs1(1); Dfs2(1, 1);
	while (m--) {
		Read(op); Read(x); Read(y);
		if (op & 1) a[x] = y;
		else putchar(Check(x, y) ? 'Y' : 'N'), putchar('\n');
	}
	return 0;
}
