#include <bits/stdc++.h>
using namespace std;
const int V = 200010;
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
int T, n, m, K;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int vis[V], col[V], mi[V], siz;
bool dfs(int u) {
	vis[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (!vis[v]) {
			col[v] = col[u] ^ 1; if (!dfs(v)) return 0;
		}
		else if (col[v] == col[u]) return 0;
	}
	return 1;
}
void Solve() {
	for (int i = 1; i <= n; i++) head[i] = vis[i] = col[i] = 0; siz = sub = 0;
	Read(n); Read(m); Read(K);
	int u, v;
	for (int i = 1; i <= m; i++) {
		Read(u); Read(v); Add(u, v); Add(v, u);
	}
	int c1 = 0, fac = K * (K - 1) / 2 % 6, c2 = 0, fk = 0;
	if (!m) {
		c1 = 1; for (int i = 1; i <= n; i++) c1 = c1 * K % 6;
		printf("%d\n", c1); return;
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i]) {
			siz++; if (!dfs(i)) {
				fk = 1; break;
			}
		}
	c2 = mi[siz] * fac % 6;
	if (!fk) {
		c1 += c2; if (!m) c1 -= 2; c1 = (c1 + 6) % 6;
	}
	printf("%d\n", c1);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T);
	mi[0] = 1; for (int i = 1; i < V; i++) mi[i] = mi[i - 1] * 2 % 6;
	while (T--) Solve();
	return 0;
}
