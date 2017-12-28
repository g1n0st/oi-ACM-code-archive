#include <bits/stdc++.h>
using namespace std;
const int V = 10100;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
const int INF = 0x3f3f3f3f;
int N, M, T;
int head[V], sub;
struct Edge {
	int to, nxt, v;
	Edge(int to = 0, int nxt = 0, int v = 0) : to(to), nxt(nxt), v(v) {}
} edge[V];
void Add(int a, int b, int v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
const int L = 14;
int g[1 << L][L][L], bin[L], h[1 << L][L][2], f[1 << L];
void Min(int &x, LL y) {
	if (y > INF) return;
	x = min(x, (int)y);
}
int _in(int s, int x) {
	return (s | bin[x]) == s;
}
int fac(int x) {
	int Ret = 1;
	for (x = x & (x - 1); x; x = x & (x - 1)) ++Ret;
	return Ret;
}
void Init() {
	int i, j, k, s, u, v;
	// solve g
	for (s = 0; s < (1 << N); s++)
		for (i = 0; i <= N; i++)
			for (j = 0; j <= N; j++)
				g[s][i][j] = INF;
	for (i = 1; i <= N; i++) {
		bin[i] = 1 << (i - 1);
		g[bin[i]][i][i] = 0;
	}
	for (u = 1; u <= N; u++)
		for (i = head[u]; i; i = edge[i].nxt) {
			v = edge[i].to;
			Min(g[bin[u] ^ bin[v]][u][v], edge[i].v);
		}
	for (s = 0; s < (1 << N); s++)
		for (k = 1; k <= N; k++)
			for (u = 1; u <= N; u++)
				if (_in(s, k) && _in(s, u))
					for (i = head[u], v; i; i = edge[i].nxt) {
						v = edge[i].to; if (_in(s, v)) continue;
						Min(g[s ^ bin[v]][k][v], g[s][k][u] + edge[i].v);
					}
	// solve h
	for (s = 0; s < (1 << N); s++)
		for (i = 0; i <= N; i++)
			h[s][i][0] = h[s][i][1] = INF;
	for (s = 0; s < (1 << N); s++)
		for (u = 1; u <= N; u++) if (!_in(s, u))
			for (int i = head[u]; i; i = edge[i].nxt) {
				v = edge[i].to;
				if (!_in(s, v)) continue;
				if (edge[i].v <= h[s][u][0]) {
					h[s][u][1] = h[s][u][0]; h[s][u][0] = edge[i].v;
				} else Min(h[s][u][1], edge[i].v);
			}
}
void Solve() {
	int i, j, k, s, t, s1, u, v;
	for (s = 1; s < (1 << N); s++) f[s] = INF;
	for (i = 1; i <= N; i++) f[bin[i]] = 0;
	for (s = 1; s < (1 << N); s++) if (fac(s) >= 2)
		for (s1 = s & (s - 1), t = s - s1; s1; s1 = (s1 - 1) & s, t = s - s1)
			for (u = 1; u <= N; u++) if (_in(s1, u))
				for (v = 1; v <= N; v++) if (_in(s1, v)) {
					if (u == v) Min(f[s], 0LL + f[t] + g[s1][u][u] + h[t][u][0] + h[t][u][1]);
					else Min(f[s], 0LL + f[t] + g[s1][u][v] + h[t][u][0] + h[t][v][0]);
				}
}
int main() {
	int i, j, u, v, w;
	Read(T);
	while (T--) {
		Read(N); Read(M);
		memset(head, 0, sizeof head);
		for (i = 1; i <= M; i++) {
			Read(u); Read(v); Read(w);
			Add(u, v, w); Add(v, u, w);
		}
		Init(); Solve();
		if (f[(1 << N) - 1] == INF) printf("impossible\n");
		else printf("%d\n", f[(1 << N) - 1]);
	}
	return 0;
}
