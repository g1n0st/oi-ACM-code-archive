#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PI;
typedef long long LL;
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
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
struct Edge {
	LL to, nxt, v;
	Edge(int to = 0, int nxt = 0, LL v = 0) : to(to), nxt(nxt), v(v) {}
};
struct G {
	int head[V], sub;
	Edge edge[V << 1];
	void Add(int a, int b, LL v) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
} G1, G2;
namespace Tr {
	int dis[V], dep[V], fa[V], siz[V], pos[V], top[V], id[V], pT;
	void Dfs1(int u) {
		siz[u] = 1;
		for (int i = G2.head[u], v; i; i = G2.edge[i].nxt) {
			v = G2.edge[i].to; if (v == fa[u]) continue;
			fa[v] = u; dep[v] = dep[u] + 1; dis[v] = dis[u] + G2.edge[i].v;
			Dfs1(v); siz[u] += siz[v];
		}
	}
	void Dfs2(int u, int path) {
		id[pos[u] = ++pT] = u; top[u] = path;
		int k = 0;
		for (int i = G2.head[u], v; i; i = G2.edge[i].nxt) {
			v = G2.edge[i].to; if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
		}
		if (!k) return; Dfs2(k, path);
		for (int i = G2.head[u], v; i; i = G2.edge[i].nxt) {
			v = G2.edge[i].to; if (dep[v] > dep[u] && v ^ k) Dfs2(v, v);
		}
	}
	int lca(int x, int y) {
		while (top[x] ^ top[y]) {
			if (dep[top[x]] > dep[top[y]]) swap(x, y);
			y = fa[top[y]];
		}
		return dep[x] < dep[y] ? x : y;
	}
	int Pa(int x, int tar) {
		while (top[x] ^ top[tar]) {
			if (fa[top[x]] == tar) return top[x];
			x = fa[top[x]];
		}
		return id[pos[tar] + 1];
	}
	LL dist(int x, int y, int l) {
		return dis[x] + dis[y] - 2 * dis[l];
	}
}
int N, M, T, pT;
int fa[V], low[V], dfn[V], STM, Dis[V];
vector<int> DIS[V];
vector<PI> ID[V];
void Solve(int rt, int x, int len) {
	++pT; G2.Add(rt, pT, 0);
	static int s[V], t; 
	static LL arr[V], inv[V]; 
	s[t = 1] = x;  arr[1] = len; 
	DIS[pT].push_back(arr[1]); ID[pT].push_back(PI(x, 0));
	for (int i = x; i ^ rt; i = fa[i]) {
		s[++t] = fa[i]; arr[t] = arr[t - 1] + Dis[i];
		DIS[pT].push_back(arr[t]); ID[pT].push_back(PI(fa[i], t - 1));;
	}
	sort(ID[pT].begin(), ID[pT].end());
	inv[t] = 0; for (int i = t - 1; i; i--) {
		inv[i] = inv[i + 1] + Dis[s[i]];
	}
	for (int i = 1; i < t; i++) G2.Add(pT, s[i], min(inv[i], arr[i]));
}
void Dfs(int u) {
	low[u] = dfn[u] = ++STM;
	for (int i = G1.head[u], v; i; i = G1.edge[i].nxt) {
		v = G1.edge[i].to; if (v == fa[u]) continue;
		if (!dfn[v]) {
			fa[v] = u; Dis[v] = G1.edge[i].v;
			Dfs(v); low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				G2.Add(u, v, G1.edge[i].v);
			}
		}
		else low[u] = min(low[u], dfn[v]);
	}
	for (int i = G1.head[u], v; i; i = G1.edge[i].nxt) {
		v = G1.edge[i].to;
		if (fa[v] ^ u && dfn[u] < dfn[v]) Solve(u, v, G1.edge[i].v);
	}
}
LL Query(int x, int y, int l) {
	int px = Tr::Pa(x, l), py = Tr::Pa(y, l);
	LL nl = Tr::dist(x, px, px) + Tr::dist(y, py, py);
	int p1 = (*lower_bound(ID[l].begin(), ID[l].end(), PI(px, 0))).second;
	int p2 = (*lower_bound(ID[l].begin(), ID[l].end(), PI(py, 0))).second;
	if (p2 < p1) swap(p1, p2);
	LL q1 = DIS[l][p2] - DIS[l][p1];
	LL q2 = DIS[l][p1] + (*DIS[l].rbegin() - DIS[l][p2]);
	return min(q1, q2) + nl;
}
void Init() {
	int i, j, u, v, w;
	Read(N); Read(M); Read(T); pT = N;
	for (i = 1; i <= M; i++) {
		Read(u); Read(v); Read(w); G1.Add(u, v, w); G1.Add(v, u, w);
	}
	Dfs(1); Tr::Dfs1(1); Tr::Dfs2(1, 1);
}
int main() {
	Init();
	int x, y, l;
	while (T--) {
		Read(x); Read(y); l = Tr::lca(x, y);
		if (l <= N) printf("%lld\n", Tr::dist(x, y, l));
		else printf("%lld\n", Query(x, y, l));
	}
	return 0;
}
