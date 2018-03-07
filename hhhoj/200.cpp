#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
const int INF = 0x3f3f3f3f;
void Read(int &x) {
	scanf("%d", &x);
}
const int N = 260;
int n, m, K, id[N][N], f[1 << 8][N];
int Val[N], C[N], pT;
vector<int> G[N];
void spfa(int *dis) {
	static int vis[N];
	deque<int> qu;
	for (int i = 1; i <= pT; i++)
		if (dis[i] != INF) {
			vis[i] = 1; qu.push_back(i);
		}
		else vis[i] = 0;
		while (!qu.empty()) {
			int u = qu.front(); qu.pop_front(); vis[u] = 0;
			for (auto v : G[u]) {
				if (!v) continue; if (C[v] == -1) continue;
				if (dis[v] > dis[u] + Val[v]) {
					dis[v] = dis[u] + Val[v];
					if (!vis[v]) {
						vis[v] = 1;
						if (!qu.empty() && dis[v] <= dis[qu.front()])
							qu.push_front(v);
						else
							qu.push_back(v);
					}
				}
			}
		}
}
int vis[N], cnt, Cid[N], idC[N], s[N], newId[N];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Read(K); int va;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			Read(va), id[i][j] = ++pT, C[pT] = va;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) Read(va), Val[id[i][j]] = va;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			G[id[i][j]].push_back(id[i + 1][j]);
			G[id[i][j]].push_back(id[i - 1][j]);
			G[id[i][j]].push_back(id[i][j + 1]);
			G[id[i][j]].push_back(id[i][j - 1]);
		}
	for (int i = 1; i <= pT; i++)
		if (C[i] >= 0 && !vis[C[i]]) {
			vis[C[i]] = ++cnt; Cid[C[i]] = cnt; idC[cnt] = C[i];
		}
	for (int i = 1; i <= cnt; i++) s[i] = i;
	int ans = INF, oo = 200;
	while (oo--) {
		random_shuffle(s + 1, s + 1 + cnt);
		
		for (int i = 1; i <= cnt; i++) newId[idC[s[i]]] = (i - 1) % K;
		if (oo <= 100 && oo >= 50) continue;
		if (oo <= 35) break;
		for (int S = 0; S < (1 << K); S++)
			for (int i = 1; i <= pT; i++) f[S][i] = INF;

		for (int i = 1; i <= pT; i++) if (C[i] > 0) f[1 << newId[C[i]]][i] = Val[i];

		for (int S = 1; S < (1 << K); S++) {
			for (int i = 1; i <= pT; i++)
				for (int s = (S - 1) & S; s; s = (s - 1) & S)
					f[S][i] = min(f[S][i], f[s][i] + f[s ^ S][i] - Val[i]);
			spfa(f[S]);
		}
		int fk = INF;
		for (int i = 1; i <= pT; i++) fk = min(fk, f[(1 << K) - 1][i]);
		ans = min(ans, fk);
	}
	if (ans == INF) puts("-1");
	else cout << ans << endl;
	return 0;
}
