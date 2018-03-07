#include <bits/stdc++.h>
using namespace std;
const int V = 1600010;
typedef long long LL;
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
	const int N = V;
	const int M = N;
	int head[V], sub;
	struct Edge {
		int to, nxt, cap, flow, w;
		Edge() {}
		Edge(int to, int nxt, int cap, int flow, int w) :
			to(to), nxt(nxt), cap(cap), flow(flow), w(w) {}
	} edge[M];
	void Add(int a, int b, int c, int f, int w) {
		edge[++sub] = Edge(b, head[a], c, f, w); head[a] = sub;
	}
	void Link(int u, int v, int c, int w) {
		Add(u, v, c, 0, w); Add(v, u, 0, 0, -w);
	}
	void init() {
		sub = 1;
	}
	int vis[N], pre[N];
	LL dis[N];
	bool spfa(int S, int T) {
		memset(vis, 0, sizeof vis);
		memset(dis, 0xc0, sizeof dis);
		memset(pre, 0, sizeof pre);
		queue<int>q; q.push(S); vis[S] = 1; dis[S] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop(); vis[u] = 0;
			for (int i = head[u], v; i; i = edge[i].nxt) {
				Edge &e = edge[i]; v = e.to;
				if (dis[v] < dis[u] + e.w && e.cap > e.flow) {
					dis[v] = dis[u] + e.w; pre[v] = i;
					if (!vis[v]) vis[v] = 1, q.push(v);
				}
			}
		}
		return dis[T] > 0;
	}
	void mcmf(int S, int T, LL &cost, int &flow) {
		cost = 0; flow = 0;
		while (spfa(S, T)) {
			int Mn = INF;
			for (int i = pre[T]; i; i = pre[edge[i ^ 1].to]) Mn = min(Mn, edge[i].cap - edge[i].flow);
			cost += (LL)Mn * dis[T];
			for (int i = pre[T]; i; i = pre[edge[i ^ 1].to]) {
				edge[i].flow += Mn; edge[i ^ 1].flow -= Mn;
			}
			flow += Mn;
		}
	}
}
int clz(int x) {
	int r = 0;
	for (; x; x >>= 1) {
		if (x & 1) break; r++;
	}
	return r;
}
int lowbit(int x) {
	return x & (-x);
}
int a[V], b[V], n, m, K, na[V], nb[V], nc[V];
map<int, int> ma, mb;
LL ans;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Net::init();
	for (int i = 1; i <= n; i++) {
		Read(a[i]); if (!a[i]) continue;
		ans += lowbit(a[i]); na[clz(a[i])]++; ma[a[i]]++;
	}
	Read(m);
	for (int i = 1; i <= m; i++) {
		Read(b[i]); if (!b[i]) continue;
		nb[clz(b[i])]++; mb[b[i]]++;
	}
	Read(K);
	for (auto ea : ma) nc[clz(ea.first)] += min(ea.second, mb[ea.first]);
	int S = 170, T = 171;
	for (int i = 0; i <= 30; i++) {
		for (int j = 0; j < i; j++)
			Net::Link(i + 1, j + 133, INF, (1 << i) - (1 << j));
		Net::Link(i + 1, i + 133, nc[i], (1 << i));
		Net::Link(S, i + 1, na[i], 0);
		Net::Link(i + 133, T, nb[i], 0);
	}
	Net::Link(T, T + 1, K, 0);
	int f; LL c; Net::mcmf(S, ++T, c, f); ans -= c;
	cout << ans << endl;
	return 0;
}
