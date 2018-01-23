#include <bits/stdc++.h>
using namespace std;
const int V = 500010;
inline char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
inline void Read(int &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
inline void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int N, M, f[V][2], g[V][2];
int low[V], dfn[V], pT, fa[V];
void Solve(int rt, int v) {
	static int s[V], t, p[2], i; p[0] = p[1] = 0; s[t = 1] = v;
	for (int x = v; x ^ rt; x = fa[x]) s[++t] = fa[x];
	g[v][0] = f[v][0]; g[v][1] = -1 << 30;
	for (i = 2; i <= t; i++) {
		int(&gn)[2] = g[s[i]], (&fn)[2] = f[s[i]], (&pr)[2] = g[s[i - 1]];
		gn[0] = fn[0] + max(pr[0], pr[1]);
		gn[1] = fn[1] + pr[0];
	}
	p[0] = max(f[rt][0], g[rt][0]);
	p[1] = max(f[rt][1], g[rt][1]);
	g[v][0] = f[v][0]; g[v][1] = f[v][1];
	for (i = 2; i <= t; i++) {
		int(&gn)[2] = g[s[i]], (&fn)[2] = f[s[i]], (&pr)[2] = g[s[i - 1]];
		gn[0] = fn[0] + max(pr[0], pr[1]);
		gn[1] = fn[1] + pr[0];
	}
	p[0] = max(p[0], g[rt][0]);
	f[rt][0] = p[0]; f[rt][1] = p[1];
}
void Dfs(int u) {
	low[u] = dfn[u] = ++pT; f[u][1] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		if (!dfn[v]) {
			fa[v] = u; Dfs(v);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				f[u][0] += max(f[v][0], f[v][1]);
				f[u][1] += f[v][0];
			}
		}
		else low[u] = min(low[u], dfn[v]);
	}
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (fa[v] ^ u && dfn[u] < dfn[v]) Solve(u, v);
	}
}
int main() {
	int i, j, x, y;
	Read(N); Read(M);
	for (i = 1; i <= M; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	Dfs(1);
	printf("%d\n", max(f[1][0], f[1][1]));
	return 0;
}
