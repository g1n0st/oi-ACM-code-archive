#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 1000000007;
const int V = 2500100;
int pri[V], sum[V], tot, mu[V], vis[V], low[V];
void Read(int &x) {
	scanf("%d", &x);
}
void Pre(int n) {
	int i, j;
	sum[1] = mu[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i;
			mu[i] = -1; sum[i] = i + 1; low[i] = i;
		}
		for (j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[pri[j] * i] = 1;
			if (i % pri[j]) {
				low[i * pri[j]] = pri[j];
				mu[i * pri[j]] = -mu[i];
				sum[i * pri[j]] = (LL)sum[i] * sum[pri[j]] % P;
			}
			else {
				low[i * pri[j]] = low[i] * pri[j];
				sum[i * pri[j]] = ((LL)sum[i] * pri[j] % P + sum[i / low[i]]) % P;
				mu[i * pri[j]] = 0;
				break;
			}
		}
	}
	for (i = 1; i <= n; i++) mu[i] = (mu[i] * i + P) % P;
	for (i = 1; i <= n; i++) (mu[i] += mu[i - 1]) %= P;
	for (i = 1; i <= n; i++) (sum[i] += sum[i - 1]) %= P;
}
map<int, int> g;
int G(int n) {
	if (n < V) return mu[n];
	if (g.count(n)) return g[n];
	int x = 1, y;
	for (int i = 2, lst; i <= n; i = lst + 1) {
		lst = n / (n / i);
		y = (LL)lst * (lst + 1) / 2 % P - (LL)i * (i - 1) / 2 % P;
		y = (y % P + P) % P;
		y = (LL)y * G(n / i) % P;
		x = (x - y + P) % P;
	}
	return g[n] = x;
}
int F(int n) {
	if (n < V) return sum[n];
	int x = 0, y;
	for (int i = 1; i * i <= n; i++) {
		(x += i) %= P;
		if ((n / i) > i) (x += (n / i)) %= P;
	}
	return x;
}
int N;
int main() {
	Pre(V - 1); Read(N);
	int lstMul = 0, x, y, z, Ans = 0;
	for (int i = 1, lst; i <= N; i = lst + 1) {
		lst = N / (N / i);
		x = G(lst);
		y = x - lstMul; y = (y % P + P) % P;
		lstMul = x;
		z = F(N / i); z = (LL)z * z % P;
		Ans = (Ans + (LL)y * z % P) % P;
	}
	printf("%d\n", Ans);
	return 0;
}
