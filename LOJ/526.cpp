#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100000;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T>
void Read(T &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
const int INF = 0x3f3f3f3f;
namespace Net {
	const int N = V;
	const int M = V * 3;
	int S, T;
	int cur[N], head[N], sub;
	struct Edge {
		int to, nxt, v;
		Edge() {}
		Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
	} edge[M];
	void Add(int a, int b, int v) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void Link(int a, int b, int v) {
		Add(a, b, v); Add(b, a, 0);
	}
	void init() {
		sub = 1;
	}
	int h[V];
	bool bfs() {
		for (int i = 0; i <= T; i++) h[i] = -1;
		queue<int> q; q.push(S); h[S] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to; if (!edge[i].v || ~h[v]) continue;
				h[v] = h[u] + 1; q.push(v);
			}
		}
		return ~h[T];
	}
	int dfs(int u, int flow) {
		if (u == T) return flow;
		int w, used = 0;
		for (int &i = cur[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (h[v] != h[u] + 1) continue;
			w = dfs(v, min(flow - used, edge[i].v));
			used += w; edge[i].v -= w; edge[i ^ 1].v += w;
			if (used == flow) return used;
		}
		if (!used) h[u] = -1;
		return used;
	}
	int dinic() {
		int r = 0;
		while (bfs()) {
			for (int i = 1; i <= T; i++) cur[i] = head[i]; r += dfs(S, INF);
		}
		return r;
	}
}
int gcd(LL x, LL y) {
	return !y ? x : gcd(y, x % y);
}
int n; LL a[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Net::init(); Net::S = n + 1; Net::T = n + 2;
	for (int i = 1; i <= n; i++) {
		Read(a[i]); if (a[i] & 1) Net::Link(Net::S, i, 1);
		else Net::Link(i, Net::T, 1);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (gcd(a[i], a[j]) == 1 && gcd(a[i] + 1, a[j] + 1) == 1) {
				if (a[i] & 1) Net::Link(i, j, 1);
				else Net::Link(j, i, 1);
			}
	printf("%d\n", n - Net::dinic());
	return 0;
}
