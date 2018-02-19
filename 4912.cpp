#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PI;
typedef list<int>::iterator IT;
const int V = 50000 + 10;
const int INF = ~0U >> 1;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
struct E {
	int a, b, c, d;
	E() {}
	E(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}
} e[V];
template<const int N, const int M>
struct G {
	int head[N], sub;
	struct Edge {
		int to, nxt, v;
		Edge() {}
		Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
	} edge[M];
	void Add(int a, int b, int v = 0) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void _init(int n) {
		for (int i = 1; i <= n; i++) head[i] = 0; sub = 0;
	}
};
struct Trie : G<V, V> {
	int fa[V], dep[V], siz[V], pos[V], top[V], pT;
	void init(int n) {
		_init(n); pT = 0;
	}
	void dfs1(int u) {
		siz[u] = 1;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (v == fa[u]) continue;
			fa[v] = u; dep[v] = dep[u] + 1; dfs1(v); siz[u] += siz[v];
		}
	}
	void dfs2(int u, int path) {
		pos[u] = ++pT; top[u] = path;
		int k = 0;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
		}
		if (!k) return; dfs2(k, path);
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (dep[v] > dep[u] && v ^ k) dfs2(v, v);
		}
	}
	int lca(int x, int y) {
		while (top[x] ^ top[y]) {
			if (dep[top[x]] > dep[top[y]]) swap(x, y);
			y = fa[top[y]];
		}
		return dep[x] < dep[y] ? x : y;
	}
} trie;
const int N = 450000 + 10, M = 800000 + 10;
struct Graph : G<N, M> {
	int val[N];
	void init(int n) {
		_init(n);
	}
	priority_queue<PI, vector<PI>, greater<PI> >q;
	int dis[N];
	void ext(int x, int y) {
		y += val[x]; if (y < dis[x]) q.push(PI(dis[x] = y, x));
	}
	void solve(int n, int m) {
		for (int i = 1; i <= n; i++) dis[i] = INF;
		for (int i = 1; i <= m; i++) if (e[i].a == 1) ext(i, 0);
		while (!q.empty()) {
			PI t = q.top(); q.pop();
			for (int i = head[t.second], v; i; i = edge[i].nxt) {
				v = edge[i].to; ext(v, t.first + edge[i].v);
			}
		}
	}
} gph;
int T, n, m, k, cnt;
list<int> fr[V], to[V];
bool cmp(const int &a, const int &b) {
	return trie.pos[e[abs(a)].d] < trie.pos[e[abs(b)].d];
}
void Work(int x) {
	static int s[V], pfr[V], pto[V], sfr[V], sto[V], tot; tot = 0;
	if (!fr[x].size() || !to[x].size()) return;
	for (IT it = fr[x].begin(); it != fr[x].end(); s[++tot] = *it, ++it);
	for (IT it = to[x].begin(); it != to[x].end(); s[++tot] = -*it, ++it);
	sort(s + 1, s + 1 + tot, cmp);
	for (int i = 1; i <= tot; i++) {
		pfr[i] = ++cnt; sfr[i] = ++cnt; pto[i] = ++cnt; sto[i] = ++cnt;
		if (i > 1) {
			gph.Add(pfr[i - 1], pfr[i]); gph.Add(pto[i - 1], pto[i]);
			gph.Add(sfr[i], sfr[i - 1]); gph.Add(sto[i], sto[i - 1]);
			int t = trie.lca(e[abs(s[i])].d, e[abs(s[i - 1])].d), d = trie.dep[t];
			gph.Add(pfr[i - 1], pto[i], d); gph.Add(sfr[i], sto[i - 1], d);
		}
		if (s[i] > 0) {
			gph.Add(s[i], pfr[i]); gph.Add(s[i], sfr[i]);
		}
		else {
			gph.Add(pto[i], -s[i]); gph.Add(sto[i], -s[i]);
		}
	}
}
void Solve() {
	read(n); read(m); read(k); cnt = m;
	int a, b, c, d;
	for (int i = 1; i <= m; i++) {
		read(a); read(b); read(c); read(d); e[i] = E(a, b, c, d);
		gph.val[i] = c; fr[b].push_back(i); to[a].push_back(i);
	}
	for (int i = 1; i < k; i++) {
		read(a); read(b); read(c); trie.Add(a, b);
	}
	trie.dfs1(1); trie.dfs2(1, 1);
	for (int i = 1; i <= n; i++) Work(i);
	gph.solve(cnt, m);
	for (int i = 2; i <= n; i++) {
		int ans = INF;
		for (IT it = fr[i].begin(); it != fr[i].end(); ++it)
			ans = min(ans, gph.dis[*it]);
		printf("%d\n", ans);
	}
}
void Clear() {
	trie.init(k); gph.init(cnt);
	for (int i = 1; i <= n; i++) {
		fr[i].clear(); to[i].clear();
	}
	for (int i = 1; i <= cnt; i++)  gph.val[i] = 0;
}
int main() {
	read(T);
	while (T--) {
		Solve(); Clear();
	}
	return 0;
}
