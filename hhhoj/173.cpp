#include <bits/stdc++.h>
using namespace std;
const int V = 2500000;
const int P = 1000000007;
void Read(int &x) {
	scanf("%d", &x);
}
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = 1ll * r * x % P;
		y >>= 1;
		if (y) x = 1ll * x * x % P;
	}
	return r;
}
int fac[V], inv[V];
void Init(int n) {
	int i, j;
	fac[0] = 1; for (i = 1; i <= n; i++) fac[i] = 1LL * fac[i - 1] * i % P;
	inv[n] = Ksm(fac[n], P - 2); for (i = n - 1; ~i; i--) inv[i] = 1LL * (i + 1) * inv[i + 1] % P;
}
int mu[V], pri[V], tot, vis[V], s[V];
void Pre(int n) {
	int i, j;
	mu[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; mu[i] = -1;
		}
		for (j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[pri[j] * i] = 1;
			if (i % pri[j]) mu[pri[j] * i] = (-1) * mu[i];
			else {
				mu[pri[j] * i] = 0;
				break;
			}
		}
	}
	for (i = 1; i <= n; i++) s[i] = s[i - 1] + mu[i];
}
int C(int x, int y) {
	if (y > x) return 0;
	if (x < V) return 1LL * fac[x] * inv[y] % P * inv[x - y] % P;
	int r = 1;
	for (int i = x - y + 1; i <= x; i++) r = 1LL * r * i % P;
	for (int i = 2; i <= y; i++) r = 1LL * r * Ksm(i, P - 2) % P;
	return r;
}
map<int, int> g;
int Cal(int n) {
	if (n < V) return s[n];
	if (g.count(n)) return g[n];
	int x = 1;
	for (int i = 2, lst; i <= n; i = lst + 1) {
		lst = n / (n / i);
		x -= (lst - i + 1) * Cal(n / i);
	}
	return g[n] = x;
}
int N, K, T;
void Solve() {
	Read(N); Read(K);
	int lst, lstMu = 0, x, y, z, Ans = 0;
	for (int i = 1; i <= N; i = lst + 1) {
		lst = N / (N / i);
		x = Cal(lst); 
		y = x - lstMu; 
		lstMu = x; 
		y = (y % P + P) % P;
		Ans = (Ans + 1LL * y * C(N / i + K - 1, K) % P) % P;
	}
	printf("%d\n", Ans);
}
int main() {
	Init(V - 1); Pre(V - 1);
	Read(T);
	while (T--) Solve();
	return 0;
}
