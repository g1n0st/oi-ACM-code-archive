#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000010;
const int P = 1000000007;
void Read(int &x) {
	scanf("%d", &x);
}
int pri[V], tot, vis[V], mu[V], fi[V], h[V], invfi[V], mulh[V], invh[V];
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1;
		if (y) x = (LL)x * x % P;
	}
	return r;
}
void Pre(int n) {
	int i, j, d, T;
	for (fi[1] = 1, i = 2; i <= n; i++) {
		fi[i] = (fi[i - 1] + fi[i - 2]) % P;
	}
	for (mu[1] = 1, i = 2; i <= n; i++) {
		if (!vis[i]) {
			mu[i] = -1; pri[++tot] = i;
		}
		for (j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[pri[j] * i] = 1;
			if (i % pri[j]) mu[pri[j] * i] = -mu[i];
			else {
				mu[pri[j] * i] = 0; break;
			}
		}
	}
	for (i = 1; i <= n; i++) invfi[i] = Ksm(fi[i], P - 2);
	for (i = 1; i <= n; i++) h[i] = 1;
	for (d = 1; d <= n; d++)
		for (T = d; T <= n; T += d) {
			if (mu[T / d] == 1) h[T] = (LL)h[T] * fi[d] % P;
			else if (mu[T / d] == -1) h[T] = (LL)h[T] * invfi[d] % P;
		}
	mulh[0] = 1; for (i = 1; i <= n; i++) mulh[i] = (LL)mulh[i - 1] * h[i] % P;
	invh[n] = Ksm(mulh[n], P - 2); for (i = n - 1; ~i; i--) invh[i] = (LL)invh[i + 1] * h[i + 1] % P;
}
int T, N, M;
void Solve() {
	Read(N); Read(M);
	int Ans = 1;
	if (N > M) swap(N, M);
	for (int i = 1, lst; i <= N; i = lst + 1) {
		lst = min(N / (N / i), M / (M / i));
		Ans = ((LL)Ans * Ksm((LL)mulh[lst] * invh[i - 1] % P, (LL)(N / i) * (M / i) % (P - 1))) % P;
	}
	printf("%d\n", Ans);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Pre(V - 1);
	Read(T); while (T--) Solve();
	return 0;
}
