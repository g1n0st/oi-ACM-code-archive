#include <bits/stdc++.h>
using namespace std;
const int V = 1000010;
const int INF = 0x3f3f3f3f;
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
int N, M, fa[V], d1[V], d2[V], ct[V * 10];
struct Edge {
	int to, nxt, v;
	Edge(int to = 0, int nxt = 0, int v = 0) : to(to), nxt(nxt), v(v) {}
};
struct G {
	int head[V], sub;
	Edge edge[V * 10];
	void Add(int a, int b, int v = 0) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void spfa(int s, int dis[]) {
		static int vis[V];
		for (int i = 1; i <= N; i++) dis[i] = INF;
		for (int i = 1; i <= N; i++) vis[i] = 0;
		dis[s] = 0; vis[s] = 1; queue<int> q; q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop(); vis[u] = 0;
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to;
				if (dis[v] > dis[u] + edge[i].v) {
					dis[v] = dis[u] + edge[i].v;
					if (!vis[v]) {
						q.push(v); vis[v] = 1;
					}
				}
			}
		}
	}
} G1, G2;
void Dfs(int u) {
	for (int i = G2.head[u], v; i; i = G2.edge[i].nxt) {
		v = G2.edge[i].to; fa[v] = (d1[v] + d2[v] == d1[N]) ? v : fa[u]; Dfs(v);
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int u, v, w;
	Read(N); Read(M);
	for (int i = 1; i <= M; i++) {
		Read(u); Read(v); Read(w); G1.Add(u, v, w); G1.Add(v, u, w);
	}
	G1.spfa(1, d1); G1.spfa(N, d2);
	for (int u = 1; u <= N; u++) {
		for (int i = G1.head[u], v; i; i = G1.edge[i].nxt) {
			v = G1.edge[i].to;
			if (d2[u] == d2[v] + G1.edge[i].v) {
				ct[i] = 1; G2.Add(v, u); break;
			}
		}
	}
	fa[N] = N; Dfs(N); int Ans = INF;
	for (int u = 1; u <= N; u++) 
		for (int i = G1.head[u], v; i; i = G1.edge[i].nxt) {
			v = G1.edge[i].to; int w = G1.edge[i].v;
			if (d1[u] <= d1[v] && fa[u] ^ fa[v] && d1[u] + w + d2[v] != d1[N])
				Ans = min(Ans, d1[u] + w + d2[v]);
		}
	if (Ans == INF) printf("-1\n");
	else printf("%d\n", Ans);
	return 0;
}
