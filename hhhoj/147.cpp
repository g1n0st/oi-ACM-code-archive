#include <cstdio>
#include <iostream>
typedef long long LL;
using namespace std;
const LL P = 1000000007;
LL N, K, L, PN, bin[20], Ans, c[20], b[20];
void Dfs(int x, int y) {
	int i, j;
	if (x == K + 1) {
		if (y != N - 2 && L == K) return;
		int cnt = 0;
		for (i = 1; i <= N; i++)
			for (j = 1; j <= c[i]; j++) b[++cnt] = i;
		b[++cnt] = K;
		for (i = 1; i <= N - 2 - y; i++) b[++cnt] = K + 1;
		LL A = 1LL;
		for (i = 1; i <= cnt; i++) {
			LL A1 = 1LL, A2 = 1LL;
			for (j = 0; j < i; j++) if (b[j] < b[i]) {
				A1 = A1 * (L - (b[i] - b[j]) + 1) % P;
				A2 = A2 * (L - (b[i] - b[j])) % P;
			}
			if (b[i] <= K) A = A * (A1 - A2 + P) % P;
			else A = A * A1 % P;
			for (j = 0; j < i; j++) if (b[j] == b[i]) A = A * L % P;
		}
		LL D = PN;
		for (i = 1; i < x; i++) D /= bin[c[i]]; D /= bin[N - 2 - y];
		Ans = (Ans + A * D % P) % P;
		return;
	}
	for (i = 0; i <= N - 2 - y; i++) {
		c[x] = i; Dfs(x + 1, y + i);
	}
}
int main() {
	int i, j;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%lld%lld%lld", &N, &K, &L);
	bin[0] = 1; for (i = 1; i <= 12; i++) bin[i] = bin[i - 1] * i;
	if (L < K) return printf("0\n"), 0;
	if (N == 2) return printf("1\n"), 0;
	PN = 1; for (i = 2; i < N - 1; i++) PN *= i;
	Dfs(1, 0);
	printf("%lld\n", Ans);
	return 0;
}
