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
int n, m;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V * 10]; int id[V * 10];
void Add(int a, int b, int id) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub; ::id[sub] = id;
}
int dfn[V], low[V], fa[V], pT, s[V], t, scc[V], pT1;
void Tarjan(int u) {
	dfn[u] = low[u] = ++pT; s[++t] = u;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (id[i] == fa[u]) continue;
		if (!dfn[v]) {
			fa[v] = id[i]; Tarjan(v); low[u] = min(low[u], low[v]);
		}
		else if (!scc[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++pT1; for (int v = -1; v != u; ) v = s[t--], scc[v] = pT1;
	}
}
int num[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	int x, y;
	for (int i = 1; i <= m; i++) {
		Read(x); Read(y); Add(x, y, i); Add(y, x, i);
	}
	Tarjan(1);
	for (int u = 1; u <= n; u++)
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (scc[u] == scc[v]) continue;
			num[scc[u]]++; num[scc[v]]++;
		}
	int ans = 0;
	for (int i = 1; i <= pT1; i++)
		if (num[i] == 2) ans++;
	cout << (ans + 1) / 2 << endl;
	return 0;
}
