#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
const int INF = 0x3f3f3f3f;
namespace Net {
	const int N = 130005;
	const int M = 250005;
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
const int L = 110;
int v[L][L][L], P, Q, R, D;
int b(int x, int y, int z) {
	if (!z) return 1;
	return (z - 1) * P * Q + (x - 1) * Q + y + 1;
}
int sx[] = { 0, 0, -1, 1 }, sy[] = { 1, -1, 0, 0 };
void Build() {
	int i, j, k, o;
	Net::Init();
	Net::S = 1; Net::T = P * Q * R + 2;
	for (i = 1; i <= P; i++)
		for (j = 1; j <= Q; j++) {
			for (k = 1; k <= R; k++) {
				Net::Link(b(i, j, k - 1), b(i, j, k), v[i][j][k]);
				if (k > D)
					for (o = 0; o < 4; o++) {
						int dx = i + sx[o], dy = j + sy[o];
						if (dx < 1 || dx > P || dy < 1 || dy > Q) continue;
						Net::Link(b(i, j, k), b(dx, dy, k - D), INF);
					}
			}
			Net::Link(b(i, j, R), Net::T, INF);
		}
}
int main() {
	int i, j, k;
	Read(P); Read(Q); Read(R); Read(D);
	for (i = 1; i <= R; i++)
		for (j = 1; j <= P; j++)
			for (k = 1; k <= Q; k++)
				Read(v[j][k][i]);
	Build();
	printf("%d\n", Net::dinic());
	return 0;
}
