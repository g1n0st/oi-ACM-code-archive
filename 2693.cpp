#include <bits/stdc++.h>
using namespace std;
const int V = 10000010;
const int P = 100000009;
void Read(int &x) {
	scanf("%d", &x);
}
int vis[V], pri[V], g[V], cnt;
void Add(int &x, int y) {
	(x += y) %= P;
}
void Init(int n) {
	int i, j;
	g[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++cnt] = i; g[i] = (i -1LL * i * i % P) % P;
		}
		for (j = 1; j <= cnt && pri[j] * i <= n; j++) {
			vis[pri[j] * i] = 1;
			if (i % pri[j]) g[i * pri[j]] = 1LL * g[i] * g[pri[j]] % P;
			else {
				g[i * pri[j]] = 1LL * g[i] * pri[j] % P; break;
			}
		}
	}
	for (i = 1; i <= n; i++) (g[i] += g[i - 1]) %= P;
}
int Sum(int x, int y) {
	return (1LL * x * (x + 1) / 2 % P) * (1LL * y * (y + 1) / 2 % P) % P;
}
int Solve(int n, int m) {
	if (n > m) swap(n, m);
	int Ret = 0;
	for (int i = 1, nxt; i <= n; i = nxt + 1) {
		nxt = min(n / (n / i), m / (m / i));
		Add(Ret, 1LL * (g[nxt] - g[i - 1] + P + P) % P * Sum(n / i, m / i) % P);
	}
	return Ret;
}
int T, N, M;
int main() {
	Read(T); Init(10000000);
	while (T--) {
		Read(N); Read(M);
		printf("%d\n", Solve(N, M));
	}
	return 0;
}
