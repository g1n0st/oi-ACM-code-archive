#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 2500000;
int pri[V], tot, vis[V], mu[V], s[V];
const int P = 1000000007;
void Read(int &x) {
	scanf("%d", &x);
}
void Pre(int n) {
	int i, j;
	mu[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; mu[i] = -1;
		}
		for (j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[pri[j] * i] = 1;
			if (i % pri[j]) mu[i * pri[j]] = -mu[i];
			else {
				mu[i * pri[j]] = 0;
				break;
			}
		}
	}
	for (i = 1; i <= n; i++) s[i] = s[i - 1] + mu[i];
}
map<int, int>g;
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
int f(int n) {
	int r = 0;
	for (int i = 1, lst; i <= n; i = lst + 1) {
		lst = n / (n / i);
		r = (r + (LL)(lst - i + 1) * (n / i) % P) % P;
	}
	return r;
}
int N;
int main() {
	Pre(V - 1); Read(N);
	int lstMul = 0, lst, x, y, z, Ans = 0;
	for (int i = 1; i <= N; i = lst + 1) {
		lst = N / (N / i);
		x = Cal(lst);
		y = x - lstMul; y = (y % P + P) % P;
		lstMul = x;
		z = f(N / i);
		Ans = (Ans + (LL)y * z % P * z % P) % P;
	}
	printf("%d\n", Ans);
	return 0;
}
