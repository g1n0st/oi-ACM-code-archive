#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 2500010;
const int P = 1000000000 + 7;
void Read(LL &x) {
	scanf("%lld", &x);
}
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1;
		if (y) x = (LL)x * x % P;
	}
	return r;
}
int tot, pri[V], phi[V], sum[V], vis[V];
void Pre(int n) {
	int i, j;
	phi[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; phi[i] = i - 1;
		}
		for (j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[pri[j] * i] = 1;
			if (i % pri[j]) phi[pri[j] * i] = phi[i] * (pri[j] - 1);
			else {
				phi[pri[j] * i] = phi[i] * pri[j];
				break;
			}
		}
	}
	for (i = 1; i <= n; i++) sum[i] = (sum[i - 1] + (LL)phi[i] * i % P * i % P) % P;
}
int inv4, inv6, inv2;
int i3(LL n) {
	n %= P;
	int nn = (LL)n * (n + 1) % P;
	return (LL)nn * nn % P * inv4 % P;
}
int i2(LL n) {
	n %= P;
	return (LL)n * (n + 1) % P * (2LL * n % P + 1) % P * inv6 % P;
}
int i1(LL n) {
	n %= P;
	return (LL)n * (n + 1) % P * inv2 % P;
}
map<LL, int> g;
int S(LL n) {
	if (n < V) return sum[n];
	if (g.count(n)) return g[n];
	int x = i3(n), y;
	for (LL i = 2, lst; i <= n; i = lst + 1) {
		lst = n / (n / i);
		y = (LL)(i2(lst) - i2(i - 1) + P) % P * S(n / i) % P;
		x = (x - y + P) % P;
	}
	return g[n] = x;
}
LL N;
int main() {
	Pre(V - 1);
	inv4 = Ksm(4, P - 2); 
	inv6 = Ksm(6, P - 2); 
	inv2 = Ksm(2, P - 2);
	Read(N);
	int Ans = 0;
	for (LL i = 1, lst; i <= N; i = lst + 1) {
		lst = N / (N / i);
		Ans = (Ans + (LL)(i1(lst) - i1(i - 1) + P) % P * S(N / i) % P) % P;
	}
	printf("%d\n", Ans);
	return 0;
}
