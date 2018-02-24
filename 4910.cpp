#include <bits/stdc++.h>
using namespace std;
const int V = 500010;
const int N = 25520010;
void Max(int &x, int y) {
	x = max(x, y);
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
int ans;
int F[N], H[N], *f[V], *h[V];
int T, n, K, L, fa[V], a[V], b[V];
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
void init() {
	for (int i = 1; i <= n; i++) head[i] = 0; sub = 0;
}
void Clear() {
	init(); ans = 0;
	memset(H + K + 1, 0, L);
	memset(F + K + 1, 0, L);
}
void Work(int *f, int A, int B) {
	static int g[V], q[V];
	int h = 1, t = 0;
	for (int i = 0, j = 0; i <= K; i++, j += B) {
		f[i] -= j;
		while (h <= t && f[q[t]] < f[i]) --t;
		q[++t] = i;
		while (i - q[h] > A) ++h;
		g[i] = f[q[h]] + j;
	}
	memcpy(f, g, L);
}
void dfs1(int u) {
	if (a[u]) Work(f[u], a[u], b[u]);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; memcpy(f[v], f[u], L);
		dfs1(v);
		for (int j = 1; j <= K; j++) Max(f[u][j], f[v][j - 1] + b[v]);
	}
}
void dfs2(int u, int exval) {
	exval += b[u];
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; memcpy(h[v], h[u], L);
		dfs2(v, exval);
		for (int j = 1; j <= K; j++) Max(h[u][j], h[v][j - 1] + b[v]);
	}
	if (!head[u]) for (int i = 0; i <= K; i++) Max(ans, f[u][i] + h[u][K - i] + exval);
	if (a[u]) Work(h[u], a[u], b[u]);
}
void Solve() {
	Clear(); Read(n); Read(K); L = sizeof(int) * (K + 1);
	for (int i = 1; i <= n; i++) {
		Read(fa[i]); Read(a[i]); --a[i]; Read(b[i]); if (fa[i]) Add(fa[i], i);
	}
	for (int i = 1; i <= n; i++) f[i] = F + i * (K + 1), h[i] = H + i * (K + 1);
	dfs1(1);
	init(); for (int i = n; i; i--) if (fa[i]) Add(fa[i], i);
	dfs2(1, 0);
	printf("%d\n", ans);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T); while (T--) Solve();
	return 0;
}
