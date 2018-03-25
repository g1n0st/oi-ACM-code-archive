#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 3010;
const int P = 998244353;
int n, deg[V], mi[V], b[V][V], g[V][V];
vector<int> a;
bitset<V> bit[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d", &n); getchar();
	mi[0] = 1; for (int i = 1; i <= n; i++) mi[i] = mi[i - 1] * 2 % P;
	for (int i = 1; i <= n; i++, getchar())
		for (int j = 1; j <= n; j++) b[i][j] = (getchar() - '0');
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) if (i ^ j) g[i][j] = !b[j][i];
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) if (g[j][i]) deg[i]++;
		if (!deg[i]) q.push(i), a.emplace_back(i);
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 1; v <= n; v++) if (g[u][v]) {
			if (!--deg[v]) q.push(v), a.emplace_back(v);
		}
	}
	int ans1 = 0, ans2 = 0, t = a.size();
	for (int i = a.size() - 1; ~i; i--) {
		int x = a[i]; bit[x].set(x);
		for (int v = 1; v <= n; v++) if (g[x][v]) bit[x] |= bit[v];
		int r = bit[x].count();
		ans1 = (ans1 + (LL)(mi[r] - 1) * mi[t - r] % P) % P;
		ans2 = (ans2 + mi[t - r]) % P;
	}
	cout << ans1 << ' ' << ans2 << endl;
	return 0;
}
