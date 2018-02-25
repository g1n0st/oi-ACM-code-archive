#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db INF = 1LL << 30;
const int V = 100000;
const db eps = 1e-8;
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
int dcmp(db x) {
	return x > eps ? 1 : (x < -eps ? -1 : 0);
}
namespace Net {
	const int N = 20000;
	const int M = 200000;
	int head[N], sub;
	struct Edge {
		int to, nxt, cap, flow; db w;
		Edge() {}
		Edge(int to, int nxt, int cap, int flow, db w)
			: to(to), nxt(nxt), cap(cap), flow(flow), w(w) {}
	} edge[M];
	void Add(int a, int b, int cap, int flow, db w) {
		edge[++sub] = Edge(b, head[a], cap, flow, w); head[a] = sub;
	}
	void Link(int a, int b, db w) {
		Add(a, b, 1, 0, w); Add(b, a, 0, 0, -w);
	}
	void init() {
		memset(head, 0, sizeof head); sub = 1;
	}
	int vis[N], pre[N]; db dis[N];
	bool spfa(int S, int T) {
		memset(vis, 0, sizeof vis);
		memset(pre, 0, sizeof pre);
		for (int i = 1; i <= T; i++) dis[i] = INF;
		queue<int> q; q.push(S); vis[S] = 1; dis[S] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop(); vis[u] = 0;
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to;
				if (dcmp(dis[v] - dis[u] - edge[i].w) > 0 && edge[i].cap > edge[i].flow) {
					dis[v] = dis[u] + edge[i].w; pre[v] = i;
					if (!vis[v]) {
						vis[v] = 1; q.push(v);
					}
				}
			}
		}
		return pre[T];
	}
	void mcmf(int S, int T, int &flow, db &cost) {
		flow = 0; cost = 0;
		while (spfa(S, T)) {
			int Mn = 1 << 30;
			for (int i = pre[T]; i; i = pre[edge[i ^ 1].to]) {
				Mn = min(Mn, edge[i].cap - edge[i].flow);
			}
			for (int i = pre[T]; i; i = pre[edge[i ^ 1].to]) {
				edge[i].flow += Mn; edge[i ^ 1].flow -= Mn; cost += Mn * edge[i].w;
			}
			flow += Mn;
		}
	}
}
const int N = 110;
int a[N][N], b[N][N], n;
bool chk(db x) {
	db c; int f;
	Net::init();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			Net::Link(i, j + n, x * b[i][j] - a[i][j]);
	int S = 2 * n + 1, T = 2 * n + 2;
	for (int i = 1; i <= n; i++) Net::Link(S, i, 0);
	for (int i = 1; i <= n; i++) Net::Link(i + n, T, 0);
	Net::mcmf(S, T, f, c); c = -c;
	return dcmp(c) > 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			Read(a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			Read(b[i][j]);
	db l = 0.0, r = 1000000.0, mid;
	while (r - l >= eps) {
		mid = (l + r) / 2.0;
		if (chk(mid)) l = mid;
		else r = mid;
	}
	printf("%.6lf\n", l);
	return 0;
}
