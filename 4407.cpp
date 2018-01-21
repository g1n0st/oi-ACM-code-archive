#include <bits/stdc++.h>
typedef long long LL;
const int V = 5000010;
const int P = 1000000007;
using namespace std;
int g[V], f[V], pri[V], tot, vis[V];
void Read(int &x) {
	scanf("%d", &x);
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
int T, N, M, K;
void Pre(int n) {
	f[1] = 1;
	int i, j;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; g[i] = Ksm(i, K); f[i] = (g[i] - 1LL + P) % P;
		}
		for (j = 1; j <= tot && i * pri[j] <= n; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j]) f[i * pri[j]] = (LL)f[i] * f[pri[j]] % P;
			else {
				f[i * pri[j]] = (LL)f[i] * g[pri[j]] % P; break;
			}
		}
	}
	for (i = 1; i <= n; i++) f[i] = ((LL)f[i - 1] + f[i]) % P;
}
void Solve() {
	Read(N); Read(M);
	if (M > N) swap(N, M);
	int Ans = 0, h;
	for (int i = 1, lst; i <= M; i = lst + 1) {
		lst = min(N / (N / i), M / (M / i));
		h = (LL)(M / i) * (N / i) % P;
		Ans = (Ans + (LL)h * ((LL)f[lst] - f[i - 1] + P) % P) % P;
	}
	printf("%d\n", Ans);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T); Read(K); Pre(V - 1);
	while (T--) Solve();
	return 0;
}
