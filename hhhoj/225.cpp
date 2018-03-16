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
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int st[V], pT, dfx[V], fa[V], ed[V];
void dfs(int u) {
	st[u] = ++pT; dfx[pT] = u;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; dfs(v);
	}
	ed[u] = ++pT; dfx[pT] = u;
}
typedef pair<int, int> PI;
int pT1, app[V], dep[V], lo2[V];
PI pp[V], mn[V][20];
void dfs1(int u) {
	++pT1; app[u] = pT1; pp[pT1] = PI(dep[u], u);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		dep[v] = dep[u] + 1; dfs1(v);
		pp[++pT1] = PI(dep[u], u);
	}
}
void build() {
	for (int i = 1; i <= pT1; i++) mn[i][0] = pp[i];
	for (int i = 1; i <= pT1; i++) {
		int g = 0; while ((1 << g) <= i) ++g;
		lo2[i] = g - 1;
	}
	for (int p = 1; p < 20; p++)
		for (int i = 1; i <= pT1; i++) {
			if (i + (1 << p) - 1 > pT1) break;
			mn[i][p] = min(mn[i][p - 1], mn[i + (1 << (p - 1))][p - 1]);
		}
}
int lca(int a, int b) {
	a = app[a]; b = app[b];
	if (a > b) swap(a, b);
	int l2 = lo2[b - a + 1];
	return min(mn[a][l2], mn[b - (1 << l2) + 1][l2]).second;
}
int B, tot, ll[V], rr[V], bel[V];
struct Query {
	int l, r, k, m, id;
	Query() {}
	Query(int l, int r, int k, int m, int id) : l(l), r(r), k(k), m(m), id(id) {}
	friend bool operator < (const Query &a, const Query &b) {
		if (a.l / B != b.l / B) return a.l < b.l;
		return a.r < b.r;
	}
} q[V];
const int M = 250;
int n, Q, a[V], ans[V]; vector<int> g;
int tim[V], bl[M], bll[M][M], blll[M][M][M]; bitset<50005> df[M][M];
int vis[V];
void Modi(int p) {
	int k;
	if (vis[p]) k = -1;
	else k = 1; vis[p] ^= 1;
	p = a[p]; int tp = tim[p];
	if (tp) {
		bl[bel[tp]]--; bll[bel[tp]][tp - ll[bel[tp]]]--; 
		blll[bel[tp]][tp - ll[bel[tp]]][bel[p]]--; df[bel[tp]][tp - ll[bel[tp]]][p] = 0;
	}
	tim[p] += k; tp = tim[p];
	if (tp) {
		bl[bel[tp]]++; bll[bel[tp]][tp - ll[bel[tp]]]++; 
		blll[bel[tp]][tp - ll[bel[tp]]][bel[p]]++; df[bel[tp]][tp - ll[bel[tp]]][p] = 1;
	}
}
struct Node {
	int t, c;
	Node() {}
	Node(int t, int c) : t(t), c(c) {}
	friend bool operator < (const Node &a, const Node &b) {
		return a.t == b.t ? a.c > b.c : a.t > b.t;
	}
} ss[V]; int tt;
int Que(int K) {
	for (int i = bel[n]; i; i--)
		if (bl[i] >= K) {
			for (int j = rr[i]; j >= ll[i]; j--)
				if (bll[i][j - ll[i]] >= K) {
					for (int k = bel[n]; k; k--)
						if (blll[i][j - ll[i]][k] >= K) {
							for (int a = rr[k]; a >= ll[k]; a--)
								if (df[i][j - ll[i]][a]) {
									--K; if (!K) return a;
								}
						}
						else K -= blll[i][j - ll[i]][k];
					} else K -= bll[i][j - ll[i]];
		} else K -= bl[i];
}
void PreBl(int n) {
	for (int i = 1; i <= n; i++) bel[i] = (i - 1) / B + 1;
	for (int i = 1; i <= n; i++) rr[bel[i]] = i;
	for (int i = n; i; i--) ll[bel[i]] = i;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(Q); B = sqrt(n) + 1;
	PreBl(n);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); g.push_back(a[i]);
	}
	sort(g.begin(), g.end()); g.erase(unique(g.begin(), g.end()), g.end());
	for (int i = 1; i <= n; i++) {
		a[i] = lower_bound(g.begin(), g.end(), a[i]) - g.begin() + 1;
	}
	int x, y, k;
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	dfs(1); dfs1(1); build();
	for (int i = 1; i <= Q; i++) {
		Read(x); Read(y); Read(k);
		int f = lca(x, y);
		if (st[x] > st[y]) swap(x, y);
		if (f == x) q[++tot] = Query(st[x], st[y], k, 0, i);
		else q[++tot] = Query(ed[x], st[y], k, f, i);
	}
	sort(q + 1, q + 1 + tot);
	int l = 1, r = 0;
	for (int i = 1; i <= tot; i++) {
		int ql = q[i].l, qr = q[i].r;
		while (l < ql) Modi(dfx[l++]);
		while (l > ql) Modi(dfx[--l]);
		while (r > qr) Modi(dfx[r--]);
		while (r < qr) Modi(dfx[++r]);
		if (q[i].m) Modi(q[i].m);
		ans[q[i].id] = Que(q[i].k) - 1;
		if (q[i].m) Modi(q[i].m);
	}
	for (int i = 1; i <= Q; i++) printf("%d\n", g[ans[i]]);
	return 0;
}
