#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
const int P = 1000000007;
const int INV2 = (P + 1) / 2;
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1;
		if (y) x = (LL)x * x % P;
	}
	return r;
}
int tot, pri[V], vis[V];
void Pre(int n) {
	int i, j;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) pri[++tot] = i;
		for (j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[pri[j] * i] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}
void FWT(int a[], int n) {
	for (int d = 1; d < n; d <<= 1)
		for (int m = d << 1, i = 0; i < n; i += m)
			for (int j = 0; j < d; j++) {
				int x = a[i + j], y = a[i + j + d];
				a[i + j] = (x + y) % P; a[i + j + d] = (x - y + P) % P;
			}
}
void UFWT(int a[], int n) {
	for (int d = 1; d < n; d <<= 1)
		for (int m = d << 1, i = 0; i < n; i += m)
			for (int j = 0; j < d; j++) {
				int x = a[i + j], y = a[i + j + d];
				a[i + j] = (LL)(x + y) * INV2 % P;
				a[i + j + d] = ((LL)(x - y) * INV2 % P + P) % P;
			}
}
int N, M, S, a[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Pre(V - 1);
	while (~scanf("%d%d", &N, &M)) {
		S = 1; while (S <= M) S <<= 1;
		for (i = 0; i < S; i++) a[i] = 0;
		for (i = 1; i <= tot && pri[i] <= M; i++) a[pri[i]] = 1;
		FWT(a, S);
		for (i = 0; i < S; i++) a[i] = Ksm(a[i], N);
		UFWT(a, S);
		printf("%d\n", a[0]);
	}
	return 0;
}
