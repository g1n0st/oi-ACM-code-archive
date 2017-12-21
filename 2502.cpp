#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int V = 100100;
void Read(int &x) {
	scanf("%d", &x);
}
const int INF = 0x3f3f3f3f;
namespace Net {
	const int N = 1300005;
	const int M = 2500005;
	int head[N], sub;
	struct Edge {
		int to, nxt, v;
		Edge(void) {}
		Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
	} edge[M];
	void Add(int a, int b, int v) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void Link(int a, int b, int v) {
		Add(a, b, v); Add(b, a, 0);
	}
	int h[N], S, T;
	void Init() {
		memset(head, 0, sizeof head);
		sub = 1;
	}
	bool bfs(void) {
		queue<int> qu;
		memset(h, -1, sizeof h);
		h[S] = 0; qu.push(S);
		while (!qu.empty()) {
			int u = qu.front(); qu.pop();
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to;
				if (~h[v] || !edge[i].v) continue;
				h[v] = h[u] + 1; qu.push(v);
			}
		}
		return ~h[T];
	}
	int dfs(int u, int flow) {
		if (u == T) return flow;
		int used = 0, w;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to;
			if (h[v] != h[u] + 1) continue;
			w = dfs(v, min(flow - used, edge[i].v));
			used += w; edge[i].v -= w; edge[i ^ 1].v += w;
			if (used == flow) return used;
		}
		if (!used) h[u] = -1;
		return used;
	}
	int dinic() {
		int Ret = 0;
		while (bfs()) Ret += dfs(S, INF);
		return Ret;
	}
}
int N, totF[V];
void Del(int x) {
	using namespace Net;
	for (int i = head[x], v; i; i = edge[i].nxt) {
		edge[i].v = edge[i ^ 1].v = 0;
	}
}
int main() {
	int i, j, tot;
	Read(N); Net::Init();
	for (i = 1; i <= N; i++) {
		Read(tot);
		while (tot--) {
			Read(j); totF[i]--; totF[j]++; Net::Link(i, j, INF);
		}
	}
	int S = N + 1, T = N + 2, SS = N + 3, TT = N + 4;
	for (i = 1; i <= N; i++) {
		Net::Link(S, i, INF);
		Net::Link(i, T, INF);
	}
	for (i = 1; i <= N; i++) {
		if (totF[i] < 0) Net::Link(i, TT, -totF[i]);
		else Net::Link(SS, i, totF[i]);
	}
	Net::Link(T, S, INF);
	Net::S = SS; Net::T = TT; Net::dinic();
	int Ans = Net::edge[Net::sub].v;

	Net::edge[Net::sub].v = Net::edge[Net::sub ^ 1].v = 0;
	Del(SS); Del(TT);

	Net::S = T; Net::T = S;
	Ans -= Net::dinic();
	printf("%d\n", Ans);
	return 0;
}
