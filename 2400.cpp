#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
void Read(int &x) {
	scanf("%d", &x);
}
const int INF = 0x3f3f3f3f;
namespace Net {
	const int N = 100010;
	const int M = 100010;
	int S, T;
	int cur[V], head[N], sub;
	struct Edge {
		int to, nxt, v;
		Edge(int to = 0, int nxt = 0, int v = 0) : to(to), nxt(nxt), v(v) {}
	} edge[M];
	void Add(int a, int b, int v) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void Link(int a, int b, int v) {
		Add(a, b, v); Add(b, a, 0);
	}
	void Init(int s = 0, int t = 0) {
		S = s; T = t; memset(head, 0, sizeof head); sub = 1;
	}
	int h[V];
	bool bfs() {
		memset(h, -1, sizeof h); h[S] = 0;
		queue<int> qu; qu.push(S);
		while (!qu.empty()) {
			int u = qu.front(); qu.pop();
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to; if (~h[v] || !edge[i].v) continue;
				h[v] = h[u] + 1; qu.push(v);
 			}
		}
		return ~h[T];
	}
	int Dfs(int u, int flow) {
		if (u == T) return flow;
		int used = 0, w;
		for (int &i = cur[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (h[v] != h[u] + 1) continue;
			w = Dfs(v, min(flow - used, edge[i].v));
			used += w; edge[i].v -= w; edge[i ^ 1].v += w;
			if (used == flow) return used;
		}
		if (!used) h[u] = -1;
		return used;
	}
	int dinic() {
		int r = 0;
		while (bfs()) {
			for (int i = 0; i <= T; i++) cur[i] = head[i];
			r += Dfs(S, INF);
		}
		return r;
	}
}
struct E {
	int x, y;
} e[V];
int N, M, a[V], S, T;
void Rebuild(int k) {
	Net::Init(S, T);
	for (int i = 1; i <= N; i++) {
		if (a[i] >= 0) {
			if ((a[i] >> k) & 1) {
				Net::Link(S, i, 1); Net::Link(i, T, INF);
			}
			else Net::Link(S, i, INF);
		}
		else Net::Link(S, i, 1);
	}
	for (int i = 1; i <= M; i++) {
		Net::Link(e[i].x, e[i].y, 10000); Net::Link(e[i].y, e[i].x, 10000);
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, k;
	Read(N); Read(M);
	for (i = 1; i <= N; i++) Read(a[i]);
	for (i = 1; i <= M; i++) {
		Read(e[i].x); Read(e[i].y);
	}
	S = N + 1; T = N + 2;
	LL A1 = 0, A2 = 0;
	for (k = 0; k <= 30; k++) {
		Rebuild(k);
		int res = Net::dinic();
		int r1 = res / 10000, r2 = res % 10000;
		A1 = A1 + ((LL)r1 << k);
		A2 = A2 + ((LL)r2 << k);
	}
	cout << A1 << endl;
	cout << A2 << endl;
	return 0;
}
