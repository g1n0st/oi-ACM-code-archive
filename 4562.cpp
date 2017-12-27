#include <cstdio>
#include <cstring>
#include <queue>
#define N 100010
using namespace std;
queue<int> q;
int cnt, rd[N], cd[N], f[N];
int head[N], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[N * 2];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int n, m, i, x, y, ans = 0;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; i++) scanf("%d%d", &x, &y), Add(x, y), cd[x]++, rd[y]++;
	for (i = 1; i <= n; i++) {
		if (!rd[i]) {
			if (cd[i]) f[i] = 1;
			q.push(i);
		}
	}
	while (!q.empty()) {
		x = q.front(), q.pop();
		for (int i = head[x], v; i; i = edge[i].nxt) {
			v = edge[i].to;
			f[v] += f[x], rd[v]--;
			if (!rd[v]) q.push(v);
		}
	}
	for (i = 1; i <= n; i++) if (!cd[i]) ans += f[i];
	printf("%d\n", ans);
	return 0;
}
