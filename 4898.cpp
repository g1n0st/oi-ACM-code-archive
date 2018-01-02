#include <bits/stdc++.h>
using namespace std;
const int V = 110;
void Read(int &x) {
	scanf("%d", &x);
}

int head[V], sub;
struct Edge {
	int to, nxt; double v;
	Edge() {}
	Edge(int to, int nxt, double v) : to(to), nxt(nxt), v(v) {}
} edge[2 * V * V];
void Add(int a, int b, double v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
int rd[V][V], pr[V][V], N, M, K, s[V][V * 10], b[V][V * 10];
double dis[V]; int vis[V], len[V];
int check(double x) {
	sub = 0; memset(head, 0, sizeof head);
	memset(dis, 0, sizeof dis);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (i != j && pr[i][j] >= 0) Add(i, j, pr[i][j] - x * rd[i][j]);
	queue<int> qu;
	for (int i = 1; i <= N; i++) {
		qu.push(i); vis[i] = len[i] = 1;
	}
	while (!qu.empty()) {
		int u = qu.front(); qu.pop(); vis[u] = 0;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to;
			if (dis[v] < dis[u] + edge[i].v) {
				dis[v] = dis[u] + edge[i].v; len[v] = len[u] + 1;
				if (len[v] > N) return 1;
				if (!vis[v]) {
					vis[v] = 1; qu.push(v);
				}
			}
		}
	}
	return 0;
}
int main() {
	int i, j, k, u, v, w;
	Read(N); Read(M); Read(K);
	memset(rd, 0x3f, sizeof rd);
	memset(pr, 0xc0, sizeof pr);
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= K; j++) {
			Read(b[i][j]); Read(s[i][j]);
		}
		rd[i][i] = 0;
	}
	for (i = 1; i <= M; i++) {
		Read(u); Read(v); Read(w);
		rd[u][v] = min(rd[u][v], w);
	}
	for (k = 1; k <= N; k++)
		for (i = 1; i <= N; i++)
			for (j = 1; j <= N; j++)
				rd[i][j] = min(rd[i][j], rd[i][k] + rd[k][j]);
	double l = 0, r = 0, mid;
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			if (i != j && rd[i][j] < 0x3f3f3f3f) {
				pr[i][j] = 0;
				for (k = 1; k <= K; k++)
					if (b[i][k] != -1 && s[j][k] != -1 && b[i][k] < s[j][k]) {
						pr[i][j] = max(pr[i][j], s[j][k] - b[i][k]);
					}
				r = (r> pr[i][j]) ? r : pr[i][j];
			}
	for (i = 1; i <= 30; i++) {
		mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%d", int(floor(r + 1e-9)));
	return 0;
}
