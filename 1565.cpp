#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int V = 360010;
void Read(int &x) {
	scanf("%d", &x);
}
struct Edge {
	int to, nxt, v;
	Edge() {}
	Edge(int to, int nxt, int v = 0) : to(to), nxt(nxt), v(v) {}
};
int head[V], sub, deg[V], del[V];
Edge edge[V];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
	deg[b]++;
}
void Dfs(int u) {
	del[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (!del[v]) Dfs(v);
	}
}
const int INF = 0x3f3f3f3f;
namespace Net {
	const int N = 800005;
	const int M = 1000010;
	int S, T;
	int head[N], sub;
	Edge edge[M];
	void Add(int a, int b, int v) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void Link(int a, int b, int v) {
		Add(a, b, v); Add(b, a, 0);
	}
	void Init() {
		memset(head, 0, sizeof head); sub = 1;
	}
	int h[V];
	bool bfs() {
		queue<int> qu; qu.push(S);
		memset(h, -1, sizeof h); h[S] = 0;
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
	int Dfs(int u, int flow) {
		if (u == T) return flow;
		int used = 0, w;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to;
			if (h[v] != h[u] + 1) continue;
			w = Dfs(v, min(edge[i].v, flow - used));
			used += w; edge[i].v -= w; edge[i ^ 1].v += w;
			if (used == flow) return flow;
		}
		if (!used) h[u] = -1;
		return used;
	}
	int dinic() {
		int Ret = 0;
		while (bfs()) Ret += Dfs(S, INF);
		return Ret;
	}
}
int N, M, v[V];
int p(int x, int y) {
	return (x - 1) * M + y;
}
int main() {
	int i, j, tot, x, y;
	Read(N); Read(M);
	for (i = 1; i <= N; i++)
		for (j = 1; j <= M; j++) {
			Read(v[p(i, j)]);
			Read(tot);
			while (tot--) {
				Read(x); Read(y);
				Add(p(i, j), p(x + 1, y + 1));
			}
		}
	for (i = 1; i <= N; i++)
		for (j = M; j > 1; j--)
			Add(p(i, j), p(i, j - 1));
	queue<int> qu;
	for (i = 1; i <= N * M; i++)
		if (!deg[i]) qu.push(i);
		else del[i] = 1;
	while (!qu.empty()) {
		int u = qu.front(); qu.pop(); del[u] = 0;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to;
			if (!--deg[v]) qu.push(v);
		}
	}
	for (i = 1; i <= N * M; i++)
		if (del[i]) Dfs(i);
	int S = N * M + 1, T = N * M + 2, Ans = 0;
	Net::Init(); Net::S = S; Net::T = T;
	for (x = 1; x <= N * M; x++) 
		if (!del[x]) {
			if (v[x] < 0) Net::Link(S, x, -v[x]);
			if (v[x] > 0) Ans += v[x], Net::Link(x, T, v[x]);
			for (int i = head[x], v; i; i = edge[i].nxt) {
				v = edge[i].to;
				if (!del[v]) Net::Link(x, v, INF);
			}
	}
	Ans -= Net::dinic();
	printf("%d\n", Ans);
	return 0;
}
