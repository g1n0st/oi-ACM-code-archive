#include <bits/stdc++.h>
using namespace std;
const int V = 2500010;
typedef long long LL;
int pri[V], vis[V], phi[V], u[V], tot;
LL sp[V], su[V];
void Read(LL &x) {
	scanf("%lld", &x);
}
void Pre(int n) {
	int i, j;
	phi[1] = u[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; phi[i] = i - 1; u[i] = -1;
		}
		for (j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j]) {
				phi[i * pri[j]] = phi[i] * (pri[j] - 1);
				u[i * pri[j]] = u[i] * (-1);
			}
			else {
				phi[i * pri[j]] = phi[i] * pri[j];
				u[i * pri[j]] = 0;
				break;
			}
		}
	}
	for (i = 1; i <= n; i++) sp[i] = sp[i - 1] + phi[i];
	for (i = 1; i <= n; i++) su[i] = su[i - 1] + u[i];
}
LL N, T;
map<LL, LL> gp, gu;
LL getPhi(LL n) {
	if (n < V) return sp[n];
	if (gp.count(n)) return gp[n];
	LL x = 1LL * n * (n + 1) / 2;
	for (LL i = 2, lst; i <= n; i = lst + 1) {
		lst = n / (n / i); 
		x -= (lst - i + 1) * getPhi(n / i);
	}
	return gp[n] = x;
}
LL getMul(LL n) {
	if (n < V) return su[n];
	if (gu.count(n)) return gu[n];
	LL x = 1;
	for (LL i = 2, lst; i <= n; i = lst + 1) {
		lst = n / (n / i);
		x -= (lst - i + 1) * getMul(n / i);
	}
	return gu[n] = x;
}
int main() {
	Pre(V - 1);
	Read(T); while (T--) {
		Read(N);
		printf("%lld %lld\n", getPhi(N), getMul(N));
	}
	return 0;
}
