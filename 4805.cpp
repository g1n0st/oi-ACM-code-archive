#include <bits/stdc++.h>
using namespace std;
const int V = 2500010;
typedef long long LL;
int pri[V], vis[V], phi[V], tot;
LL s[V];
void Read(int &x) {
	scanf("%d", &x);
}
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
				break;
			}
		}
	}
	for (i = 1; i <= n; i++) s[i] = s[i - 1] + phi[i];
}
int N;
map<int, LL> g;
LL f(int n) {
	if (n < V) return s[n];
	if (g.count(n)) return g[n];
	LL x = 1LL * n * (n + 1) / 2;
	for (int i = 2, lst; i <= n; i = lst + 1) {
		lst = n / (n / i); 
		x -= (lst - i + 1) * f(n / i);
	}
	return g[n] = x;
}
int main() {
	Pre(V - 1); Read(N);
	printf("%lld\n", f(N));
	return 0;
}
