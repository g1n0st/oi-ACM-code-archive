#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 998244353;
const int INV2 = (P + 1) / 2;
const int V = 100;
void Read(int &x) {
	scanf("%d", &x);
}
vector<int> G[V];
int u[V], v[V], w[V], n, m;
int scc[V], id[V], cnt, pT;
int g[V][V], f[V][V];
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
void dfs(int u) {
	scc[u] = cnt; id[u] = pT++;
	for (auto v : G[u])
		if (!scc[v]) dfs(v);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); int inv = Ksm(10000, P - 2);
	for (int i = 1; i <= m; i++) {
		Read(u[i]); Read(v[i]); Read(w[i]);
		w[i] = (LL)w[i] * inv % P;
		G[u[i]].emplace_back(v[i]);
		G[v[i]].emplace_back(u[i]);
	}
	for (int i = 1; i <= n; i++) if (!scc[i]) {
		++cnt; pT = 0; dfs(i);
		for (int s = 0; s < (1 << pT); s++) {
			int res = 1, tot = 0;
			for (int i = 1; i <= n; i++)
				if (scc[i] == cnt && ((s >> id[i]) & 1)) tot++;
			for (int i = 1; i <= m; i++) {
				int u = ::u[i], v = ::v[i], w = ::w[i];
				if ((scc[u] ^ cnt) || (scc[v] ^ cnt)) continue;
				if (((s >> id[u]) & 1) == ((s >> id[v]) & 1)) continue;
				if ((s >> id[u]) & 1) res = (LL)res * 2 * w % P;
				else res = (LL)res * 2 * (P + 1 - w) % P;
			}
			(g[cnt][tot] += res) %= P;
		}
	}
	f[0][0] = 1;
	for (int i = 1; i <= cnt; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k <= j; k++)
				f[i][j] = (f[i][j] + (LL)f[i - 1][k] * g[i][j - k] % P) % P;
	int ans = 0;
	for (int i = 0; i <= n; i++) ans = (ans + (LL)f[cnt][i] * Ksm(INV2, i * (n - i)) % P) % P;
	ans = (LL)ans * Ksm(10000, n * (n - 1)) % P;
	cout << ans << endl;
	return 0;
}
