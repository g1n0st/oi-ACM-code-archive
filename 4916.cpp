#include <bits/stdc++.h>
using namespace std;
const int P = 1000000007;
const int V = 2500000;
void Read(int &x) {
	scanf("%d", &x);
}
int Ksm(int x, int y, int p) {
	int r = 1;
	while (y) {
		if (y & 1) r = 1ll * r * x % p;
		y >>= 1;
		if (y) x = 1ll * x * x % p;
	}
	return r;
}
int tot, pri[V], phi[V], vis[V], s[V];
void Pre(int n) {
	int i, j;
	phi[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; phi[i] = i - 1;
		}
		for (j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j]) phi[i * pri[j]] = phi[i] * (pri[j] - 1);
			else {
				phi[i * pri[j]] = phi[i] * pri[j];
			}
		}
	}
	for (i = 1; i <= n; i++) s[i] = (s[i - 1] + 1LL * i * phi[i] % P) % P;
}
int N, inv6;
map<int, int> g;
int f(int n) {
	if (n < V) return s[n];
	if (g.count(n)) return g[n];
	int x = 1LL * n * (n + 1) % P * (2 * n + 1) % P * inv6 % P, y, z;
	for (int i = 2, lst; i <= n; i = lst + 1) {
		lst = n / (n / i);
		y = lst - i + 1;
		z = 1LL * y * i % P;
		z = (z + 1LL * y * (y - 1) / 2 % P) % P;
		z = 1LL * z * f(n / i) % P;
		x = (x + P - z) % P;
	}
	return g[n] = x;
}
int main() {
	Pre(V - 1); Read(N);
	inv6 = Ksm(6, P - 2, P);
	printf("1\n");
	printf("%d\n", f(N));
	return 0;
}
