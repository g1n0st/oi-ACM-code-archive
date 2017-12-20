#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
const int V = 100010;
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
int Ans;
int N, M; 
int main() {
	int i, j;
	Read(N); Read(M);
	Net::Init(); Net::S = 1, Net::T = N + M + 2;
	int a, b, c;
	for (i = 1; i <= N; i++) {
		Read(a); Net::Link(Net::S, i + 1, a);
	}
	for (i = 1; i <= M; i++) {
		Read(a); Read(b); Read(c);
		Net::Link(a + 1, N + i + 1, INF);
		Net::Link(b + 1, N + i + 1, INF);
		Net::Link(N + i + 1, Net::T, c);
		Ans += c;
	}
	Ans -= Net::dinic();
	printf("%d\n", Ans);
	return 0;
}
