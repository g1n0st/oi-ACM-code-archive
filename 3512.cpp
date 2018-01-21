#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const int P = 1000000007;
const int INV2 = (P + 1) / 2;
const int V = 2000010;
void Read(int &x) {
	scanf("%d", &x);
}
int phi[V], pri[V], tot, mx[V], vis[V], sum[V];
void Pre(int n) {
	int i, j;
	phi[1] = mx[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; phi[i] = i - 1; mx[i] = i;
		}
		for (j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[pri[j] * i] = 1;
			if (i % pri[j]) {
				phi[pri[j] * i] = phi[i] * (pri[j] - 1);
				mx[pri[j] * i] = pri[j] * mx[i];
			}
			else {
				phi[pri[j] * i] = phi[i] * pri[j];
				mx[pri[j] * i] = mx[i];
			}
		}
	}
	for (i = 1; i <= n; i++) sum[i] = (sum[i - 1] + phi[i]) % P;
}
map<int, int> g1;
map<PI, int> g;
int S(int n, int m) {
	if (m <= 1) return phi[n * m];
	if (n == 1) {
		if (m < V) return sum[m];
		if (g1.count(m)) return g1[m];
		int r = (LL)m * (m + 1) % P * INV2 % P;
		for (int i = 2, lst; i <= m; i = lst + 1) {
			lst = m / (m / i);
			r = (r - (LL)(lst - i + 1) * S(1, m / i) % P + P) % P;
		}
		return g1[m] = r;
	}
	else {
		if (g.count(PI(n, m))) return g[PI(n, m)];
		int r = 0;
		for (int d = 1, d1; d * d <= n; d++)
			if (!(n % d)) {
				r = ((LL)r + (LL)phi[n / d] * S(d, m / d) % P) % P;
				if (d1 = n / d, d1 > d) r = ((LL)r + (LL)phi[n / d1] * S(d1, m / d1) % P) % P;
			}
		return g[PI(n, m)] = r;
	}
}
int N, M;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Pre(V - 1); Read(N); Read(M);
	if (N > M) swap(N, M);
	int Ans = 0;
	for (int i = 1; i <= N; i++)
		Ans = (Ans + (LL)(i / mx[i]) * S(mx[i], M) % P) % P;
	printf("%d\n", Ans);
	return 0;
}
