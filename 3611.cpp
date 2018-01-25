#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000010;
const int INF = 1 << 30;
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
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
};
struct G {
	int head[V], sub;
	Edge edge[V << 1];
	void Add(int a, int b) {
		if (a == b) return; 
		edge[++sub] = Edge(b, head[a]); head[a] = sub;
	}
} G1, G2;
int siz[V], dep[V], fa[V], pos[V], top[V], pT;
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = G1.head[u], v; i; i = G1.edge[i].nxt) {
		v = G1.edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; dep[v] = dep[u] + 1; Dfs1(v); siz[u] += siz[v];
	}
}
void Dfs2(int u, int path) {
	pos[u] = ++pT; top[u] = path;
	int k = 0;
	for (int i = G1.head[u], v; i; i = G1.edge[i].nxt) {
		v = G1.edge[i].to;
		if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return; Dfs2(k, path);
	for (int i = G1.head[u], v; i; i = G1.edge[i].nxt) {
		v = G1.edge[i].to;
		if (dep[v] > dep[u] && v ^ k) Dfs2(v, v);
	}
}
int lca(int x, int y) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}
int N, Q, M, a[V], s[V], v[V], t;
bool cmp(int x, int y) {
	return pos[x] < pos[y];
}
void reBuild() {
	int i, j; G2.sub = 0;
	Read(M);
	for (i = 1; i <= M; i++) {
		Read(a[i]);	v[a[i]] = 1;
	}
	sort(a + 1, a + 1 + M, cmp);
	s[t = 1] = 1;
	for (i = 1; i <= M; i++) {
		int now = a[i], f = lca(now, s[t]);
		while (1) {
			if (dep[f] >= dep[s[t - 1]]) {
				G2.Add(f, s[t--]);
				if (s[t] ^ f) s[++t] = f;
				break;
			}
			G2.Add(s[t - 1], s[t]); t--;
		}
		if (now ^ s[t]) s[++t] = now;
	}
	while (--t) G2.Add(s[t], s[t + 1]);
}
int AMX, AMN; LL TOT;
int mn[V], mx[V], Size[V]; LL f[V];
void Dp(int u) {
	mn[u] = v[u] ? 0 : INF;
	mx[u] = v[u] ? 0 : -INF;
	Size[u] = v[u]; f[u] = 0;
	for (int i = G2.head[u], v, val; i; i = G2.edge[i].nxt) {
		v = G2.edge[i].to; Dp(v); val = dep[v] - dep[u];
		TOT += Size[u] * f[v] + Size[v] * f[u] + (LL)Size[u] * Size[v] * val;
		AMX = max(AMX, mx[u] + mx[v] + val);
		AMN = min(AMN, mn[u] + mn[v] + val);
		mx[u] = max(mx[u], mx[v] + val);
		mn[u] = min(mn[u], mn[v] + val);
		Size[u] += Size[v];
		f[u] += f[v] + (LL)Size[v] * val;
	}
	G2.head[u] = 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x, y;
	Read(N);
	for (i = 1; i < N; i++) {
		Read(x); Read(y); G1.Add(x, y); G1.Add(y, x);
	}
	Dfs1(1); Dfs2(1, 1); Read(Q);
	while (Q--) {
		reBuild();
		AMX = -INF; AMN = INF; TOT = 0;
		Dp(1);
		printf("%lld %d %d\n", TOT, AMN, AMX);
		for (i = 1; i <= M; i++) v[a[i]] = 0;
	}
	return 0;
}
