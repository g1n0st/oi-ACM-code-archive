#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 1000000007;
const int V = 350;
int a[V][V];
int Gauss(int n) {
	int Det = 1, f = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			(a[i][j] += P) %= P;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			int x = a[i][i], y = a[j][i];
			while (y) {
				int t = x / y; x %= y; swap(x, y);
				for (int k = i; k <= n; k++) a[i][k] = (a[i][k] + (P - (LL)a[j][k] * t % P) % P) % P;
				for (int k = i; k <= n; k++) swap(a[i][k], a[j][k]);
				f = -f;
			}
		}
		if (!a[i][i]) return 0;
		Det = (LL)Det * a[i][i] % P;
	}
	if (f == -1) Det = (P - Det) % P;
	return Det;
}
char s[V];
int T, N, M, id[V][V], f[V * V], cir, tot;
int nul[V * V], x[V], y[V];
int getf(int x) {
	return f[x] == x ? x : f[x] = getf(f[x]);
}
void Merge(int x, int y) {
	x = getf(x); y = getf(y);
	if (x == y) cir = 1;
	f[x] = y;
}
void Init() {
	int pT = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			id[i][j] = ++pT;
	for (int i = 0; i <= pT; i++) f[i] = i;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		memset(nul, 0, sizeof nul);
		memset(id, 0, sizeof id);
		scanf("%d%d", &N, &M);
		Init(); cir = tot = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%s", s + 1);
			for (int j = 1; j <= M; j++) {
				switch (s[j]) {
				case 'L': Merge(id[i][j], id[i][j - 1]); break;
				case 'R': Merge(id[i][j], id[i][j + 1]); break;
				case 'U': Merge(id[i][j], id[i - 1][j]); break;
				case 'D': Merge(id[i][j], id[i + 1][j]); break;
				default: nul[id[i][j]] = ++tot; x[tot] = i; y[tot] = j;
				}
			}
		}
		if (cir) {
			printf("0\n"); continue;
		}
		memset(a, 0, sizeof a);
		for (int i = 1; i <= tot; i++) {
			a[i][nul[getf(id[x[i]][y[i] - 1])]]--; a[i][nul[getf(id[x[i]][y[i] + 1])]]--;
			a[i][nul[getf(id[x[i] - 1][y[i]])]]--; a[i][nul[getf(id[x[i] + 1][y[i]])]]--;
			a[i][i] += 4;
		}
		printf("%d\n", Gauss(tot));
	}
	return 0;
}
