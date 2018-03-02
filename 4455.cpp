#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
void Read(int &x) {
	scanf("%d", &x);
}
const int N = 100;
int head[N], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[N * N];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int G[N][N], n, m, a[N], tot;
LL f[N][N];
void dfs(int u, int fa) {
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v ^ fa) dfs(v, u);
	}
	for (int x = 1; x <= tot; x++) {
		f[u][x] = 1;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (v == fa) continue;
			LL t = 0;
			for (int y = 1; y <= tot; y++)
				if (G[a[x]][a[y]]) t += f[v][y];
			f[u][x] *= t;
		}
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	int x, y;
	for (int i = 1; i <= m; i++) {
		Read(x); Read(y); G[x][y] = G[y][x] = 1;
	}
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	LL ans = 0;
	for (int i = 1; i < (1 << n); i++) {
		tot = 0;
		for (int j = 1; j <= n; j++)
			if (i & (1 << j - 1)) a[++tot] = j;
		dfs(1, 0);
		for (int j = 1; j <= tot; j++)
			ans += (tot & 1) == (n & 1) ? f[1][j] : -f[1][j];
	}
	cout << ans << endl;
	return 0;
}
