#include <bits/stdc++.h>
using namespace std;
const int V = 1000010;
typedef pair<int, int> PI;
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
int n, siz[V], son[V], S, rt, Sum, Tot, Ci, ans[V];
set<PI, greater<PI>> s;
void makeroot(int u, int fa) {
	siz[u] = 1; son[u] = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue;
		makeroot(v, u); siz[u] += siz[v]; son[u] = max(son[u], siz[v]);
	}
	son[u] = max(son[u], S - siz[u]);
	if (son[u] < son[rt]) rt = u;
}
void dfs1(int u, int fa) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue; dfs1(v, u); siz[u] += siz[v];
	}
}
void dfs2(int u, int fa, int csiz) {
	ans[u] = Tot; if ((n - siz[u] - csiz) * 2 > n) ans[u]++;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue; dfs2(v, u, csiz);
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	int x, y;
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	S = son[rt = 0] = n; makeroot(1, 0); dfs1(rt, 0);
	for (int i = head[rt], v; i; i = edge[i].nxt) {
		v = edge[i].to; s.insert(PI(siz[v], v));
	}
	for (auto e : s) {
		Ci = e.first;
		if ((Sum + e.first + 1) * 2 > n) break; 
		Sum += e.first; ++Tot;
	}
	for (int i = head[rt], v; i; i = edge[i].nxt) {
		v = edge[i].to; 
		if (siz[v] < Ci) dfs2(v, rt, Sum);
		else dfs2(v, rt, Sum + Ci - siz[v]);
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
