#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 250100;
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
struct Edge {
	int to, nxt, v;
	Edge() {}
	Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
};
struct G {
	int head[V], sub;
	Edge edge[V << 1];
	void Add(int a, int b, int v) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void Add(int a, int b) {
		if (a == b) return;
		//cout << a << ' ' << b << endl;
		Add(a, b, 0);
	}
} G1, G2;
LL mn[V];
int f[V][20], dep[V], bin[20], dfn[V], pT;
void Dfs(int u, int fa) {
	dfn[u] = ++pT;
	f[u][0] = fa;
	for (int i = 1; i < 20; i++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for (int i = G1.head[u], v; i; i = G1.edge[i].nxt) {
		v = G1.edge[i].to; if (v == fa) continue;
		mn[v] = min(mn[u], (LL)G1.edge[i].v);
		dep[v] = dep[u] + 1;
		Dfs(v, u);
	}
}
int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int t = dep[x] - dep[y];
	for (int i = 0; bin[i] <= t; i++)
		if (t & bin[i]) x = f[x][i];
	for (int i = 19; ~i; i--) 
		if (f[x][i] ^ f[y][i]) {
			x = f[x][i]; y = f[y][i];
	}
	if (x == y) return x;
	return f[x][0];
}
int N, M, T, a[V], s[V], t, tot;
LL dp[V];
bool cmp(int x, int y) {
	return dfn[x] < dfn[y];
}
void Dfs(int u) {
	dp[u] = 0;
	for (int i = G2.head[u], v; i; i = G2.edge[i].nxt) {
		v = G2.edge[i].to; Dfs(v);
		dp[u] += dp[v];
	}
	if (!dp[u]) dp[u] = mn[u];
	dp[u] = min(dp[u], (LL)mn[u]);
	G2.head[u] = 0;
}
void Solve() {
	int i, j;
	Read(M); G2.sub = 0;
	for (i = 1; i <= M; i++) Read(a[i]);
	sort(a + 1, a + 1 + M, cmp);

	a[tot = 1] = a[1];
	for (i = 2; i <= M; i++)
		if (lca(a[tot], a[i]) ^ a[tot])
			a[++tot] = a[i];
	s[++t] = 1;
	for (i = 1; i <= tot; i++) {
		int now = a[i], f = lca(now, s[t]);
		while (1) {
			if (dep[f] >= dep[s[t - 1]]) {
				G2.Add(f, s[t--]);
				if (s[t] ^ f) s[++t] = f;
				break;
			}
			G2.Add(s[t - 1], s[t]); t--;
		}
		if (s[t] ^ now) s[++t] = now;
	}
	while (--t) G2.Add(s[t], s[t + 1]);
	Dfs(1);
	printf("%lld\n", dp[1]);
}
int main() {
	int i, j, u, v, w;
	bin[0] = 1; for (i = 1; i <= 20; i++) bin[i] = bin[i - 1] << 1;
	Read(N);
	for (i = 1; i < N; i++) {
		Read(u); Read(v); Read(w);
		G1.Add(u, v, w); G1.Add(v, u, w);
	}
	mn[1] = 1LL << 60;
	Dfs(1, 0);
	Read(T);
	while (T--) Solve();
	return 0;
}
