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
const int INF = 0x3f3f3f3f;
int n1, n2, M, C, cnt, mark[V], pd[V];
namespace Net {
	int S, T;
	const int N = V;
	const int M = V * 10;
	int head[N], cur[N], sub;
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
	int vis[N], h[N], pT;
	bool bfs() {
		h[S] = 0; queue<int> q; q.push(S); vis[S] = ++pT;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to; if (!edge[i].v || vis[v] == pT) continue;
				vis[v] = pT; h[v] = h[u] + 1; q.push(v);
			}
		}
		return vis[T] == pT;
	}
	int dfs(int u, int flow) {
		if (u == T) return flow;
		int used = 0, w;
		for (int &i = cur[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (h[v] != h[u] + 1) continue;
			w = dfs(v, min(flow - used, edge[i].v));
			used += w; edge[i].v -= w; edge[i ^ 1].v += w;
			if (used == flow) return flow;
		}
		if (!used) h[u] = -1;
		return used;
	}
	int dinic() {
		int r = 0;
		while (bfs()) {
			for (int i = 1; i <= cnt; i++) cur[i] = head[i];
			r += dfs(S, INF);
		}
		return r;
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(M); Read(C); Net::init(); 
	cnt = M + C; Net::S = ++cnt; Net::T = ++cnt;
	int a, b;
	Read(n1);
	for (int i = 1; i <= n1; i++) {
		Read(a); Read(b); mark[++cnt] = i;
		Net::Link(Net::S, cnt, 1);
		Net::Link(cnt, a, 1);
		Net::Link(cnt, b + M, 1);
	}
	Read(n2);
	for (int i = 1; i <= n2; i++) {
		Read(a); Read(b); ++cnt; //mark[++cnt] = i;
		Net::Link(cnt, Net::T, 1);
		Net::Link(a, cnt, 1);
		Net::Link(b + M, cnt, 1);
	}
	int r = Net::dinic();
	for (int i = 1; i <= n1; i++) pd[i] = 1;
	for (int i = Net::head[Net::S], v; i; i = Net::edge[i].nxt) {
		v = Net::edge[i].to; if (Net::edge[i].v) pd[mark[v]] = 0;
	}
	for (int i = 1; i <= cnt; i++)
		if (Net::vis[i] == Net::pT) pd[mark[i]] = 0;
	for (int i = 1; i <= n1; i++) printf("%d\n", pd[i]);
	return 0;
}
