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
int n, m, deg[V];
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
	edge[++sub] = Edge(b, head[a]); head[a] = sub; deg[b]++;
}
int low[V], dfn[V], fa[V], cnt, cutp[V], chi[V];
void Tarjan(int u) {
	dfn[u] = low[u] = ++cnt;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; ++chi[u];
		if (!dfn[v]) {
			fa[v] = u; Tarjan(v); low[u] = min(low[u], low[v]);
			if (!fa[u] && chi[u] > 1) cutp[u] = 1;
			if (fa[u] && low[v] >= dfn[u]) cutp[u] = 1;
		} else if (v != fa[u]) low[u] = min(low[u], dfn[v]);
	}
}
vector<int> G;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	int u, v;
	for (int i = 1; i <= m; i++) {
		Read(u); Read(v); Add(u, v); Add(v, u);
	}
	Tarjan(1);
	for (int i = 1; i <= n; i++)
		if (!cutp[i] && deg[i] == m - n + 2) G.push_back(i);
	sort(G.begin(), G.end());
	printf("%d\n", G.size());
	for (int i = 0; i < G.size(); i++) printf("%d ", G[i]);
	return 0;
}
