#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;
const int V = 30010;
int Max(int a, int b) {
	return a > b ? a : b;
}
int Min(int a, int b) {
	return a < b ? a : b;
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
LL Ans;
int N, M, a[V], b[V][20];
int S, siz[V], root, vis[V], son[V], p[V];
LL fdis[V][20][2], dis[V][20][2], dn[V][20][2], vs0[V], vn0[V];
int head[V], sub;
struct Edge {
	int to, nxt, v;
	Edge() {}
	Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
} edge[V * 2];
void Add(int a, int b, int v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}

namespace LCA {
	int ff[V][25], dep[V], len[V];
	inline void dfs1(int u, int fa) {
		ff[u][0] = fa;
		for (int i = 1; i <= 20; i++) {
			ff[u][i] = ff[ff[u][i - 1]][i - 1];
		}
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to;
			if (v == fa) continue;
			dep[v] = dep[u] + 1; len[v] = len[u] + edge[i].v;
			dfs1(v, u);
		}
	}
	inline int lca(int x, int y) {
		if (dep[x] < dep[y]) swap(x, y);
		int tmp = dep[x] - dep[y];
		for (int k = 0, j = 1; j <= tmp; j <<= 1, k++)
			if (tmp & j) x = ff[x][k];
		while (x != y) {
			int j = 0;
			while (ff[x][j] != ff[y][j]) j++;
			if (j) j--;
			x = ff[x][j], y = ff[y][j];
		}
		return x;
	}
	inline int dist(int x, int y) {
		return len[x] + len[y] - (len[lca(x, y)] << 1);
	}
};

void getRoot(int u, int fa) {
	siz[u] = 1; son[u] = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (vis[v] || v == fa) continue;
		getRoot(v, u);
		siz[u] += siz[v]; son[u] = Max(son[u], siz[v]);
	}
	son[u] = Max(son[u], S - siz[u]);
	if (son[u] < son[root]) root = u;
}
struct Node {
	int x, d, bel, v;
	Node() {}
	Node(int x, int d, int bel, int v) : x(x), d(d), bel(bel), v(v) {}
} s[V], tmp[V]; int top, t1;
void Dfs(int u, int fa, int S, int dep) {
	s[++top] = Node(u, dep, S, a[u]);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (vis[v] || v == fa) continue;
		Dfs(v, u, S, dep + edge[i].v);
	}
}
LL Update(int v, int x, int c) {
	int d = (c ^ 1);
	LL t = dis[v][x][c] - dis[v][x][d], s0, n0, len;
	for (int u = v;; u = p[u]) {
		if (!p[u]) break;
		len = LCA::dist(v, p[u]);
		s0 = dis[p[u]][x][c] - fdis[u][x][c];
		n0 = dn[p[u]][x][c] - dn[u][x][c];
		t += s0 + n0 * len;
		s0 = dis[p[u]][x][d] - fdis[u][x][d];
		n0 = dn[p[u]][x][d] - dn[u][x][d];
		t -= s0 + n0 * len;
	}
	for (int u = v;; u = p[u]) {
		dn[u][x][d]++, dn[u][x][c]--;
		if (!p[u]) break;
		len = LCA::dist(v, p[u]);
		fdis[u][x][d] += len, fdis[u][x][c] -= len;
		dis[p[u]][x][d] += len, dis[p[u]][x][c] -= len;
	}
	return t;
}
void Wrk(int x) {
	int i, j;
	top = 0;
	for (int i = head[x], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v]) continue;
		Dfs(v, x, v, edge[i].v);
	}
	for (i = 1; i <= top; i++) Ans += 1LL * (s[i].v ^ a[x]) * s[i].d;
	for (j = 0; j < 16; j++) {
		LL s0 = 0, n0 = 0, t = 0; t1 = 0;
		dn[x][j][b[x][j]] = 1; fdis[x][j][b[x][j]] = LCA::dist(p[x], x);
		for (i = 1; i <= top; i++) {
			int c = b[s[i].x][j];
			dn[x][j][c]++; dis[x][j][c] += s[i].d;
			fdis[x][j][c] += LCA::dist(p[x], s[i].x);
			if (c) tmp[++t1] = s[i];
			else {
				s0 += s[i].d; n0++;
				vs0[s[i].bel] += s[i].d; vn0[s[i].bel]++;
			}
		}
		for (i = 1; i <= t1; i++) {
			t += 1LL * tmp[i].d * (n0 - vn0[tmp[i].bel]) + (s0 - vs0[tmp[i].bel]);
		}
		Ans += t * (1 << j);
		for (int i = head[x], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (vis[v]) continue;
			vs0[v] = vn0[v] = 0LL;
		}
	}
}
void Solve(int x) {
	vis[x] = 1; Wrk(x);
	for (int i = head[x], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (vis[v]) continue;
		S = siz[v]; root = 0;
		getRoot(v, 0);
		p[root] = x;
		Solve(root);
	}
}
int main() {
	int i, j, u, v, w;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]); w = a[i];
		for (j = 0; j < 16; j++) {
			b[i][j] = w & 1;
			w >>= 1;
		}
	}
	for (i = 1; i < N; i++) {
		Read(u); Read(v); Read(w);
		Add(u, v, w); Add(v, u, w);
	}
	LCA::dfs1(1, 0);
	S = son[root = 0] = N; getRoot(1, 0);
	Solve(root); Read(M);
	while (M--) {
		Read(v); Read(w);
		for (i = 0; i < 16; i++) {
			int c = w & 1;
			if (c ^ b[v][i]) Ans += (1 << i) * Update(v, i, b[v][i]);
			b[v][i] = c;
			w >>= 1;
		}
		printf("%lld\n", Ans);
	}
	return 0;
}
