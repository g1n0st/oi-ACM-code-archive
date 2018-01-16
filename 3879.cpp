#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000010;
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
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !(c >= 'a' && c <= 'z'); c = get());
	for (; c >= 'a' && c <= 'z'; s[len++] = c, c = get());
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

int dfn[V], dep[V], f[V][25], pT, bin[25];
void Dfs(int u, int fa) {
	dfn[u] = ++pT; f[u][0] = fa;
	for (int i = 1; i <= 21; i++) f[u][i] = f[f[u][i - 1]][i - 1];
	for (int i = G1.head[u], v; i; i = G1.edge[i].nxt) {
		v = G1.edge[i].to; if (v == fa) continue;
		dep[v] = dep[u] + 1; Dfs(v, u);
	}
}
int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int t = dep[x] - dep[y];
	for (int i = 0; bin[i] <= t; i++)
		if (t & bin[i]) x = f[x][i];
	for (int i = 21; ~i; i--)
		if (f[x][i] ^ f[y][i]) {
			x = f[x][i]; y = f[y][i];
		}
	if (x == y) return x;
	return f[x][0];
}

namespace SAM {
	int c[V][26], len[V], fa[V], pT, lst, rt;
	void Init() {
		lst = rt = ++pT;
	}
	int Extend(int x) {
		int cur = ++pT; len[cur] = len[lst] + 1;
		int p = lst;
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) fa[cur] = rt;
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) fa[cur] = q;
			else {
				++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[q] = fa[cur] = pT;
			}
		}
		lst = cur;
		return cur;
	}
}
int N, M, T, L, id[V];
int a[V], st[V], t;
int sum[V], val[V];
bool cmp(int x, int y) {
	return dfn[x] < dfn[y];
}
LL Ans;
void Dfs(int u) {
	sum[u] = val[u];
	for (int i = G2.head[u], v; i; i = G2.edge[i].nxt) {
		v = G2.edge[i].to; Dfs(v);
		Ans += 1LL * sum[u] * sum[v] * SAM::len[u];
		sum[u] += sum[v];
	}
	G2.head[u] = 0;
}
void Solve() {
	int i, j;
	Read(M); G2.sub = 0;
	for (i = 1; i <= M; i++) {
		Read(a[i]); a[i] = id[a[i]];
	}
	sort(a + 1, a + 1 + M, cmp);
	M = unique(a + 1, a + 1 + M) - a - 1;
	for (i = 1; i <= M; i++) val[a[i]] = 1;
	st[++t] = 1;
	for (i = 1; i <= M; i++) {
		int now = a[i], f = lca(a[i], st[t]);
		while (1) {
			if (dep[f] >= dep[st[t - 1]]) {
				G2.Add(f, st[t--]);
				if (f ^ st[t]) st[++t] = f;
				break;
			}
			G2.Add(st[t - 1], st[t]); t--;
		}
		if (st[t] ^ now) st[++t] = now;
	}
	while (--t) G2.Add(st[t], st[t + 1]);

	Ans = 0; Dfs(1);
	printf("%lld\n", Ans);

	for (i = 1; i <= M; i++) val[a[i]] = 0;
}
char s[V];
int main() {
	int i, j;
	bin[0] = 1; for (i = 1; i <= 21; i++) bin[i] = bin[i - 1] << 1;
	Read(N); Read(T); Read(s + 1, L);
	SAM::Init();
	for (i = N; i; i--) id[i] = SAM::Extend(s[i] - 'a');
	for (i = 1; i <= SAM::pT; i++)
		if (SAM::fa[i]) G1.Add(SAM::fa[i], i);
	Dfs(1, 0);
	while (T--) Solve();
	return 0;
}
