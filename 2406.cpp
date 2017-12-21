#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
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
const int V = 310;
int s1[V], s2[V], N, M, a[V][V], L, R, totF[V * V];
bool check(int x) {
	int i, j;
	int S = N + M + 1, T = N + M + 2, SS = N + M + 3, TT = N + M + 4;
	Net::Init(); Net::S = SS; Net::T = TT;
	memset(totF, 0, sizeof totF);
	for (i = 1; i <= N; i++)
		for (j = 1; j <= M; j++) {
			Net::Link(i, j + N, R - L); totF[i] -= L; totF[j + N] += L;
		}
	for (i = 1; i <= N; i++) {
		int la = max(0, s1[i] - x), ra = s1[i] + x;
		Net::Link(S, i, ra - la); totF[S] -= la; totF[i] += la;
	}
	for (j = 1; j <= M; j++) {
		int la = max(0, s2[j] - x), ra = s2[j] + x;
		Net::Link(j + N, T, ra - la); totF[j + N] -= la; totF[T] += la;
	}
	Net::Link(T, S, INF);
	int t1 = 0;
	for (i = 1; i <= N + M + 2; i++)
		if (totF[i] < 0) Net::Link(i, TT, -totF[i]);
		else Net::Link(SS, i, totF[i]), t1 += totF[i];
	return Net::dinic() >= t1;
}
int main() {
	int i, j;
	Read(N); Read(M);
	for (i = 1; i <= N; i++)
		for (j = 1; j <= M; j++) {
			Read(a[i][j]); s1[i] += a[i][j]; s2[j] += a[i][j];
		}
	Read(L); Read(R);
	int L = -1, R = 2000000, Mid;
	while (L < R - 1) {
		Mid = (L + R) >> 1;
		if (check(Mid)) R = Mid;
		else L = Mid;
	}
	printf("%d\n", R);
	return 0;
}
