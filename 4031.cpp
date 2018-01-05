#include <bits/stdc++.h>
using namespace std;
const int V = 110;
typedef long long LL;
const int sx[] = { -1, 1, 0, 0 };
const int sy[] = { 0, 0, -1, 1 };
const LL P = 1e9;
char mp[V][V];
int N, M, A[V][V], D[V][V], id[V][V], pT;
void Add(int u, int v) {
	A[u][v] = 1; D[v][v]++;
}
LL g[V][V];
LL Gauss(int n) {
	LL Det = 1; int f = 1;
	int i, j, k;
	for (i = 1; i < n; i++)
		for (j = 1; j < n; j++)
			(g[i][j] += P) %= P;
	for (i = 1; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			LL x = g[i][i], y = g[j][i];
			while (y) {
				LL t = x / y; x %= y; swap(x, y);
				for (k = i; k < n; k++)
					g[i][k] = (g[i][k] - t * g[j][k] % P + P) % P;
				for (k = i; k < n; k++)
					swap(g[i][k], g[j][k]);
				f = -f;
			}
		}
		if (!g[i][i]) return 0;
		Det = Det * g[i][i] % P;
	}
	if (f == -1) Det = (P - Det) % P;
	return Det;
}
int main() {
	int i, j, k;
	scanf("%d%d", &N, &M);
	for (i = 1; i <= N; i++) scanf("%s", mp[i] + 1);
	for (i = 1; i <= N; i++)
		for (j = 1; j <= M; j++)
			if (mp[i][j] != '*') id[i][j] = ++pT;
	for (i = 1; i <= N; i++)
		for (j = 1; j <= M; j++)
			if (mp[i][j] != '*') {
				for (k = 0; k < 4; k++) {
					int y = i + sy[k], x = j + sx[k];
					if (!x || !y || y > N || x > M) continue;
					if (mp[y][x] == '*') continue;
					Add(id[i][j], id[y][x]);
				}
			}
	for (i = 1; i <= pT; i++)
		for (j = 1; j <= pT; j++)
			g[i][j] = D[i][j] - A[i][j];
	printf("%lld\n", Gauss(pT));
	return 0;
}
