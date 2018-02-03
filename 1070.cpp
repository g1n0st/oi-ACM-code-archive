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
namespace Net {
	const int N = 10010;
	const int M = 500100;
	int head[N], sub;
	struct Edge {
		int to, nxt, cap, flow, w;
		Edge() {}
		Edge(int to, int nxt, int cap, int flow, int w) :
			to(to), nxt(nxt), cap(cap), flow(flow), w(w) {}
	} edge[M];
	void Init() {
		sub = 1; memset(head, 0, sizeof head);
	}
	void Add(int a, int b, int c, int f, int w) {
		edge[++sub] = Edge(b, head[a], c, f, w); head[a] = sub;
	}
	void Link(int u, int v, int c, int w) {
		Add(u, v, c, 0, w); Add(v, u, 0, 0, -w);
	}
	int dis[V], pre[V], vis[V];
	bool spfa(int s, int t) {
		memset(dis, 0x3f, sizeof dis);
		memset(pre, 0, sizeof pre);
		memset(vis, 0, sizeof vis);
		queue<int>q; q.push(s); dis[s] = 0; vis[s] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop(); vis[u] = 0;
			for (int i = head[u]; i; i = edge[i].nxt) {
				Edge e = edge[i];
				if (dis[e.to] > dis[u] + e.w && e.cap > e.flow) {
					dis[e.to] = dis[u] + e.w; pre[e.to] = i;
					if (!vis[e.to]) {
						vis[e.to] = 1; q.push(e.to);
					}
				}
			}
		}
		return pre[t];
	}
	void mcmf(int s, int t, int &cost, int &flow) {
		cost = flow = 0;
		while (spfa(s, t)) {
			int Mn = INF;
			for (int i = pre[t]; i; i = pre[edge[i ^ 1].to]) {
				Edge e = edge[i]; Mn = min(Mn, e.cap - e.flow);
			}
			for (int i = pre[t]; i; i = pre[edge[i ^ 1].to]) {
				edge[i].flow += Mn; edge[i ^ 1].flow -= Mn; cost += edge[i].w * Mn;
			}
			flow += Mn;
		}
	}
}
int N, M, f[160][160];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(M); Read(N);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) Read(f[i][j]);
	int S = (N + 1) * (M + 1) + 10, T = (N + 1) * (M + 1) + 20; Net::Init();
	for (int i = 1; i <= N * M; i++) Net::Link(i, T, 1, 0);
	for (int i = 1; i <= N; i++) Net::Link(S, N * M + i, 1, 0);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			for (int k = 1; k <= N; k++)
				Net::Link(N * M + i, (j - 1) * N + k, 1, f[i][j] * k);
	int c, f; Net::mcmf(S, T, c, f);
	printf("%.2lf\n", 1.0 * c / N);
	return 0;
}
