#include <bits/stdc++.h>
using namespace std;
typedef double db;
const int V = 200010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c; int f = 0;
	for (; !isdigit(c); c = get()) if (c == '-') f ^= 1;
	for (; isdigit(c); x = x * 10 + c - '0', c = get()); if (f) x = -x;
}
const int N = 500;
int n, k, a[N];
int head[N], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[N << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int low[N], dfn[N], s[N], t, scc[N], pT, pT1, tot[N], deg[V];
void Tarjan(int u) {
	dfn[u] = low[u] = ++pT; s[++t] = u;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (!dfn[v]) {
			Tarjan(v); low[u] = min(low[u], low[v]);
		}
		else if (!scc[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++pT1; tot[pT1] = 0;
		for (int v = -1; v != u; ) {
			v = s[t--]; scc[v] = pT1; tot[pT1]++;
		}
	}
}
db C[N][N], f[N][N];
void Pre(int n) {
	C[0][0] = 1;
	for (int i = 1; i <= N; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
}
void Clear() {
	pT = pT1 = sub = 0;
	memset(head, 0, sizeof head);
	memset(low, 0, sizeof low);
	memset(dfn, 0, sizeof dfn);
	memset(scc, 0, sizeof scc);
	memset(deg, 0, sizeof deg);
	memset(f, 0, sizeof f);
}
void Solve() {
	Clear(); Read(n); Read(k);
	int x;
	for (int i = 1; i <= n; i++) {
		Read(x); Add(i, x);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) Tarjan(i);
	int m = 0, sum = n;
	for (int u = 1; u <= n; u++)
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (scc[u] == scc[v]) continue;
			deg[scc[v]]++;
		}
	for (int i = 1; i <= pT1; i++)
		if (!deg[i]) {
			a[++m] = tot[i]; sum -= tot[i];
		}
	f[0][0] = 1;
	for (int i = 1; i <= m; i++)
		for (int j = i; j <= n; j++)
			for (int k = 1; k <= min(j, a[i]); k++)
				f[i][j] = f[i][j] + f[i - 1][j - k] * C[a[i]][k];
	db ans = 0;
	for (int i = 1; i <= k; i++)
		ans += f[m][i] * C[sum][k - i];
	printf("%.9lf\n", ans / C[n][k]);
}
int main() {
	//freopen("5004.in", "r", stdin);
	//freopen("5004.out", "w", stdout);
	Pre(N - 1); Read(t);
	while (t--) Solve();
	return 0;
}
