#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000010;
void Read(int &x) {
	scanf("%d", &x);
}
void Read(LL &x) {
	scanf("%lld", &x);
}
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
LL ans, tot[V], mx[V], a[V];
void dfs(int u, int fa) {
	tot[u] = a[u], mx[u] = a[u];
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue;
		dfs(v, u); tot[u] += tot[v]; mx[u] = max(mx[u], tot[v]);
	}
	ans += min(tot[u] - 1, 2 * (tot[u] - mx[u]));
}
int n, m;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	for (int i = 1; i <= n; i++) Read(a[i]);
	int x, y;
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
