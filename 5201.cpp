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
} edge[V * 10];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int T, n, m, tot;
int low[V], dfn[V], pT, s[V], t, lst[V], chi[V * 10], scc[V];
void Clr() {
	pT = sub = tot = 0;
	for (int i = 1; i <= n; i++)
		head[i] = low[i] = dfn[i] = scc[i] = lst[i] = 0;
	for (int i = 1; i <= m; i++) chi[i] = 0;
}
void Tarjan(int u) {
	s[++t] = u; low[u] = dfn[u] = ++pT;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (!dfn[v]) {
			chi[i] = 1; Tarjan(v); low[u] = min(low[u], low[v]); ++tot;
		}
		else if (!scc[v] && dfn[v] < low[u]) {
			low[u] = min(low[u], dfn[v]); lst[u] = i;
		}
	}
	if (lst[u]) chi[lst[u]] = 1, tot++;
	if (low[u] == dfn[u]) {
		for (int v = -1; v != u; ) v = s[t--], scc[v] = 1;
	}
}
void Solve() {
	Clr(); Read(n); Read(m);
	int u, v;
	for (int i = 1; i <= m; i++) {
		Read(u); Read(v); Add(u, v);
	}
	Tarjan(1);
	tot = n * 2 - tot;
	if (tot) for (int i = 1; i <= sub; i++)
		if (!chi[i]) {
			chi[i] = 1; if (!--tot) break;
		}
	for (int u = 1; u <= n; u++)
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (!chi[i]) printf("%d %d\n", u, v);
		}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T);
	while (T--) Solve();
	return 0;
}
