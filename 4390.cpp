#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int V = 100010;
int Max(int a, int b) {
	return a > b ? a : b;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = get();
	}
}
int N, M;
int t[V];
int lowbit(int x) {
	return x & (-x);
}
void Modify(int x, int v) {
	while (x <= N) {
		t[x] += v;
		x += lowbit(x);
	}
}
int Query(int x) {
	int Ret = 0;
	while (x) {
		Ret += t[x];
		x -= lowbit(x);
	}
	return Ret;
}
int Query(int l, int r) {
	return Query(r) - Query(l - 1);
}
int siz[V], dep[V], fa[V], pos[V], top[V], pT;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge () {}
	Edge (int to, int nxt) : to(to), nxt(nxt) {}
} edge[V * 2];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (v == fa[u]) continue;
		fa[v] = u; dep[v] = dep[u] + 1;
		Dfs1(v); siz[u] += siz[v];
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
int lca(int x, int y) {
	int tx, ty;
	while (top[x] != top[y]) {
		tx = top[x]; ty = top[y];
		if (dep[ty] > dep[tx]) {
			swap(x, y); swap(tx, ty);
		}
		x = fa[tx];
	}
	return dep[x] > dep[y] ? y : x;
}
int main() {
	int i, j, x, y, l;
	Read(N); Read(M);
	for (i = 1; i < N; i++) {
		Read(x); Read(y);
		Add(x, y); Add(y, x);
	}
	Dfs1(1); Dfs2(1, 1);
	while (M--) {
		Read(x); Read(y); l = lca(x, y);
		Modify(pos[x], 1); Modify(pos[y], 1);
		Modify(pos[l], -1);
		if (l != 1) Modify(pos[fa[l]], -1);
	}
	int Ans = 0;
	for (i = 1; i <= N; i++) Ans = Max(Ans, Query(pos[i], pos[i] + siz[i] - 1));
	printf("%d\n", Ans);
	return 0;
}
