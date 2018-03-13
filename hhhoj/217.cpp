#include <bits/stdc++.h>
using namespace std;
const int V = 2048;
const int RA = 1034;
typedef pair<int, int> PI;
void Read(int &x) {
	scanf("%d", &x);
}
struct Trie {
	int c[V * V][2], pT, rt;
	void init() {
		rt = ++pT;
	}
	void insert(int x) {
		int p = rt;
		for (int i = 20; ~i; i--) {
			int v = (x >> i) & 1; if (!c[p][v]) c[p][v] = ++pT; p = c[p][v];
		}
	}
	void Wt(int x, int dep) {
		if (!~dep) return;
		for (int i = 0; i < 2; i++) {
			if (c[x][i]) putchar('1'), Wt(c[x][i], dep - 1);
			else putchar('0');
		}
	}
};
namespace E {
	Trie t;
	vector<int> G[V]; int n, m, vis[V]; vector<PI> E;
	void bfs(int S) {
		memset(vis, 0, sizeof vis);
		queue<int> qu; qu.push(S); vis[S] = 1;
		while (!qu.empty()) {
			int u = qu.front(); qu.pop();
			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i]; if (!vis[v]) {
					vis[v] = 1; qu.push(v); E.push_back(PI(u, v));
				}
			}
		}
	}
	void main() {
		Read(n); Read(m); int x, y; t.init();
		for (int i = 1; i <= m; i++) {
			Read(x); Read(y); G[x].push_back(y); G[y].push_back(x);
		}
		for (int i = 1; i <= n; i++) sort(G[i].begin(), G[i].end());
		for (int i = 1; i <= 36; i++) bfs(i);
		PI lst;
		sort(E.begin(), E.end()); for (int i = 0; i < E.size(); i++) {
			PI v = E[i];
			if (v == lst) continue; lst = v;
			int x = v.first, y = v.second; t.insert(x * RA + y);
		}
		t.Wt(t.rt, 20);
	}
}
namespace D {
	vector<int> G[V]; int vis[V], dis[V], n;
	void bfs(int S) {
		memset(vis, 0, sizeof vis);
		queue<int> qu; qu.push(S); vis[S] = 1; dis[S] = 0;
		while (!qu.empty()) {
			int u = qu.front(); qu.pop();
			if (G[u].size()) for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i];
				if (!vis[v]) {
					vis[v] = 1; dis[v] = dis[u] + 1; qu.push(v);
				}
			}
		}
	}
	void Rd(int dep, int val) {
		if (!~dep) {
			int y = val % RA, x = val / RA;
			G[x].emplace_back(y); G[y].emplace_back(x); n = max(n, x); n = max(n, y);
			return;
		}
		int v = getchar() - '0'; if (v) Rd(dep - 1, val);
		v = getchar() - '0'; if (v) Rd(dep - 1, val + (1 << dep));
	}
	void main() {
		getchar(); Rd(20, 0);
		for (int i = 1; i <= 36; i++) {
			bfs(i); for (int j = 1; j <= n; j++) printf("%d ", dis[j]);
		}
	}
}
int main() {
	//freopen("in1.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T; Read(T); if (T & 1) E::main(); else D::main();
	return 0;
}
