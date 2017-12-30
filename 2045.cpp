#include <bits/stdc++.h>
using namespace std;
const int V = 1000100;
typedef long long LL;
void Read(int &x) {
	scanf("%d", &x);
}
int A, B, K;
int pri[V], tot, vis[V], mul[V], sum[V];
void Init(int n) {
	int i, j;
	mul[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; mul[i] = -1;
		}
		for (j = 1; j <= tot && i * pri[j] <= n; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j]) mul[i * pri[j]] = -mul[i];
			else {
				mul[i * pri[j]] = 0; break;
			}
		}
	}
	for (i = 1; i <= n; i++) sum[i] = sum[i - 1] + mul[i];
}
LL Solve(int n, int m) {
	n /= K; m /= K;
	if (n > m) swap(n, m); if (n == 0) return 0;
	LL Ret = 0;
	for (int i = 1, nxt; i <= n; i = nxt + 1) {
		nxt = min(n / (n / i), m / (m / i));
		Ret += 1LL * (n / i) * (m / i) * (sum[nxt] - sum[i - 1]);
	}
	return Ret;
}
int main() {
	Init(1000000);
	Read(A); Read(B); Read(K);
	printf("%lld\n", Solve(A, B));
	return 0;
}
