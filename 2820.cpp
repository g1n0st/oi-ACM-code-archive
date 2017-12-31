#include <bits/stdc++.h>
using namespace std;
const int V = 1e7 + 5;
typedef long long LL;
void Read(int &x) {
	scanf("%d", &x);
}
int vis[V], pri[V], cnt, mul[V], g[V], T, N, M;
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
	for (i = 1; i <= cnt; i++)
		for (j = pri[i]; j <= n; j += pri[i])
			g[j] += mul[j / pri[i]];
	for (i = 1; i <= n; i++) g[i] += g[i - 1];
}
LL Solve(int n, int m) {
	if (n > m) swap(n, m);
	LL Ret = 0;
	for (int i = 1, nxt; i <= n; i = nxt + 1) {
		nxt = min(n / (n / i), m / (m / i));
		Ret += (LL)(n / i) * (m / i) * (g[nxt] - g[i - 1]);
	}
	return Ret;
}
int main() {
	Init(10000000);
	Read(T);
	while (T--) {
		Read(N); Read(M);
		printf("%lld\n", Solve(N, M));
	}
	return 0;
}
