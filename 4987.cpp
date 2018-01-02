#include <bits/stdc++.h>
using namespace std;
const int V = 3010;
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
int head[V], sub;
struct Edge {
	int to, nxt, v;
	Edge() {}
	Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
} edge[V  * 2];
void Add(int a, int b, int v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
int N, K, f[V][V][3], siz[V];
void Min(int &x, int y) {
	x = min(x, y);
}
void Dfs(int u, int fa) {
	int i, j, k, o, p;
	siz[u] = 1; f[u][0][0] = f[u][0][1] = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue;
		Dfs(v, u);
		for (j = siz[u] - 1; ~j; j--)
			for (k = siz[v] - 1; ~k; k--)
				for (o = 2; ~o; o--)
					for (p = o; ~p; p--)
						Min(f[u][j + k + 1][o], f[u][j][o - p] + f[v][k][p] + edge[i].v * (2 - (p & 1)));
		siz[u] += siz[v];
	}
}
int main() {
	int i, j, u, v, w;
	Read(N); Read(K);
	for (i = 1; i < N; i++) {
		Read(u); Read(v); Read(w);
		Add(u, v, w); Add(v, u, w);
	}
	memset(f, 0x3f, sizeof f);
	Dfs(1, 0);
	int Ans = 1 << 30;
	for (i = 1; i <= N; i++)
		for (j = 0; j < 3; j++)
			Ans = min(Ans, f[i][K - 1][j]);
	printf("%d\n", Ans);
	return 0;
}
