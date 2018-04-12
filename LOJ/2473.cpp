#include <bits/stdc++.h>
using namespace std;

typedef unsigned LL;

const int V = 100010;
const int P = 64123;

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

const int N = 2070;

int head[N], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[N << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}

int n, K, W, curw, a[N], siz[N], lst[N];
LL f[N][N];

inline void add(LL &x, LL y) {
	x += y; if (x > P) x -= P;
}
void dfs(int u, int fa) {
	for (int i = lst[u]; i <= siz[u]; i++) f[u][i] = 0;
	siz[u] = lst[u] = (a[u] >= curw);
	f[u][siz[u]] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue;
		dfs(v, u);
		for (int j = siz[u]; j >= lst[u]; j--)
			for (int k = siz[v]; k >= lst[v]; k--)
				f[u][j + k] = (f[u][j + k] + f[u][j] * f[v][k]) % P;
		siz[u] += siz[v];
	}
	for (int i = lst[u]; i <= siz[u]; i++) add(f[0][i], f[u][i]);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K); Read(W);
	for (int i = 1; i <= n; i++) Read(a[i]);
	int x, y;
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}

	LL ans = 0;

	for (curw = 1; curw <= W; curw++) {
		for (int i = 1; i <= n; i++) f[0][i] = 0;
		dfs(1, 0);
		for (int k = K; k <= n; k++) add(ans, f[0][k]);
	}

	cout << ans << endl;

	return 0;
}
