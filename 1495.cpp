#include <cstdio>
#include <cstring>
using namespace std;
const int V = 2048;
const int L = 5000;
const int INF = 1000000000;
int f[V][L];
int Min(int a, int b) {
	return a < b ? a : b;
}
void Read(int &x) {
	scanf("%d", &x);
}
int N, M, s[V], c[V], val[V][V];
int Dfs(int u, int p, int S, int h) {
	int i, j;
	int k = (S << (h + 1)) | p;
	if (f[u][k] >= 0) return f[u][k];
	if (u >= M) {
		int x = u - M + 1;
		int &mf = f[u][k]; mf = 0;
		if (p ^ s[x]) {
			for (i = 0; i < N; i++)
				if (((S >> i) & 1) != s[x]) mf += val[x][u >> (i + 1)];
		}
		else {
			mf += c[x];
			for (i = 0; i < N; i++)
				if (((S >> i) & 1) == s[x]) mf += val[x][u >> (i + 1)];
		}
		return mf;
	}
	int &mf = f[u][k];  mf = INF;
	int S1 = (S << 1) | (p < ((1 << h) - p));
	int tot = Min(p, 1 << (h - 1));
	for (i = p - tot; i <= tot; i++) {
		mf = Min(mf, Dfs(u << 1, i, S1, h - 1) + Dfs(u << 1 | 1, p - i, S1, h - 1));
	}
	return mf;
}
int main() {
	int i, j;
	//freopen("1495.in", "r", stdin);
	//freopen("1495.out", "w", stdout);
	Read(N); M = 1 << N;
	for (i = 1; i <= M; i++) Read(s[i]);
	for (i = 1; i <= M; i++) Read(c[i]);
	for (i = 1; i <= M; i++)
		for (j = 1; j <= M - i; j++) {
			int x, i1 = i + M - 1, j1 = i + j + M - 1;
			Read(x);
			for (; i1 != j1; i1 >>= 1, j1 >>= 1);
			val[i][i1] += x; val[i + j][i1] += x;
		}
	int Ans = INF;
	memset(f, -1, sizeof f);
	for (i = 0; i <= M; i++)
		Ans = Min(Ans, Dfs(1, i, 0, N));
	printf("%d\n", Ans);
	return 0;
}
