#include <bits/stdc++.h>
using namespace std;
const int V = 1e7 + 5;
typedef long long LL;
const LL P = 20101009;
void Read(int &x) {
	scanf("%d", &x);
}
int vis[V], pri[V], cnt, mul[V], g[V], N, M;
void Init(int n) {
	mul[1] = 1;
	int i, j;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++cnt] = i; mul[i] = -1;
		}
		for (j = 1; j <= cnt && i * pri[j] <= n; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j]) mul[i * pri[j]] = -mul[i];
			else {
				mul[i * pri[j]] = 0; break;
			}
		}
	}
	for (i = 1; i <= n; i++) {
		g[i] = (g[i - 1] + 1LL * i * i * mul[i]) % P;
	}
}
int Sum(int x, int y) {
	return ((1LL * x * (x + 1) / 2 % P) * (1LL * y * (y + 1) / 2 % P)) % P;
}
int Calc(int n, int m) {
	if (n > m) swap(n, m);
	int Ret = 0;
	for (int i = 1, nxt; i <= n; i = nxt + 1) {
		nxt = min(m / (m / i), n / (n / i));
		Ret = (Ret + ((g[nxt] - g[i - 1]) % P * Sum(n / i, m / i)) % P + P) % P;
	}
	return Ret;
}
int Solve(int n, int m) {
	if (n > m) swap(n, m);
	int Ret = 0;
	for (int i = 1, nxt; i <= n; i = nxt + 1) {
		nxt = min(m / (m / i), n / (n / i));
		Ret = (Ret + 1ll * (i + nxt) * (nxt - i + 1) / 2 % P * Calc(n / i, m / i)) % P;
	}
	return Ret;
}
int main() {
	Read(N); Read(M); Init(10000000);
	printf("%d\n", Solve(N, M));
	return 0;
}
