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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
char getc() {
	char c = get();
	while (c > 'Z' || c < 'A') c = get();
	return c;
}
map<int, int> mp; int cnt;
int N, M, a[V], b[V];
int ls[V * 100], rs[V * 100], sum[V * 100], rt[3 * V], PT;
void Modify(int &x, int l, int r, int p, int v) {
	if (!x) x = ++PT;
	sum[x] += v;
	if (l == r) return;
	int Mid = (l + r) >> 1;
	if (p <= Mid) Modify(ls[x], l, Mid, p, v);
	if (Mid < p) Modify(rs[x], Mid + 1, r, p, v);
}
int Query(int x, int l, int r, int L, int R) {
	if (!x) return 0;
	if (l == L && r == R) return sum[x];
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Query(ls[x], l, Mid, L, R);
	if (Mid < L) return Query(rs[x], Mid + 1, r, L, R);
	return Query(ls[x], l, Mid, L, Mid) + Query(rs[x], Mid + 1, r, Mid + 1, R);
}
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V * 2];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int dep[V], siz[V], fa[V], top[V], pos[V], pT;
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (v == fa[u]) continue;
		dep[v] = dep[u] + 1; fa[v] = u;
		Dfs1(v);
		siz[u] += siz[v];
	}
}
void Dfs2(int u, int path) {
	pos[u] = ++pT; top[u] = path;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return;
	Dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (dep[v] > dep[u] && v != k) Dfs2(v, v);
	}
}
int Query(int x, int y, int v) {
	int Ret = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		Ret += Query(rt[v], 1, N, pos[top[y]], pos[y]);
		y = fa[top[y]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	Ret += Query(rt[v], 1, N, pos[x], pos[y]);
	return Ret;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x, y, v;
	Read(N); Read(M);
	for (i = 1; i <= N; i++) {
		Read(a[i]);
		if (!mp.count(a[i])) mp[a[i]] = ++cnt;
		b[i] = mp[a[i]];
	}
	for (i = 1; i < N; i++) {
		Read(x); Read(y);
		Add(x, y); Add(y, x);
	}
	Dfs1(1); Dfs2(1, 1);
	for (i = 1; i <= N; i++) Modify(rt[b[i]], 1, N, pos[i], 1);
	char op;
	while (M--) {
		op = getc();
		if (op == 'C') {
			Read(x); Read(v);
			if (!mp.count(v)) mp[v] = ++cnt;
			v = mp[v];
			Modify(rt[b[x]], 1, N, pos[x], -1);
			b[x] = v;
			Modify(rt[b[x]], 1, N, pos[x], 1);
		}
		else {
			Read(x); Read(y); Read(v);
			if (!mp.count(v)) mp[v] = ++cnt;
			v = mp[v];
			printf("%d\n", Query(x, y, v));
		}
	}
	return 0;
}
