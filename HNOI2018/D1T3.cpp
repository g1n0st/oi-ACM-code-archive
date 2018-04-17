#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PI;

const int V = 101010;
const int P = 998244353;
const int GIVEN_SUB = 20;

template<class t1, class t2> inline void $(t1 &x, const t2 y) {
	(x += y) %= P;
}
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
int n, m;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1]; int del[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}

int w[V], dfn[V], pT;
vector<PI> G, ad[V], f[V];
int pos[V][GIVEN_SUB];

void dfs(int u, int fa) {
	dfn[u] = ++pT;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue;
		if (!dfn[v]) dfs(v, u);
		else {
			del[i] = 1;
			if (dfn[v] < dfn[u]) {
				ad[u].emplace_back(PI(u, v)); ++w[u]; --w[v];
			}
		}
	}
}
void dp(int u, int fa) {
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa || del[i]) continue;
		dp(v, u); w[u] += w[v];
		for (int j = 0; j < ad[v].size(); j++)
			if (ad[v][j].second != u) {
				ad[u].emplace_back(ad[v][j]);
				pos[v][j] = ad[u].size() - 1;
			}
	}
	f[u].resize(1 << w[u]);
	for (int S = 0; S < (1 << w[u]); S++)
		for (int x = 0; x < 2; x++) {
			int flg = 1; LL ans = 1;
			for (int i = 0; i < ad[u].size(); i++)
				if (ad[u][i].first == u && ((S >> i) & 1) != x) {
					flg = 0; break;
				}
			if (!flg) continue;
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to; if (v == fa || del[i]) continue;
				int st(0), T(0);

				for (int j = 0; j < ad[v].size(); j++)
					if (ad[v][j].second != u) st |= ((S >> pos[v][j]) & 1) << j;
					else T |= 1 << j;

				if (x) ans = ans * f[v][st].second % P;
				else {
					LL res = (f[v][st].first + f[v][st].second) % P;
					for (int s = T; s; s = (s - 1) & T)
						$(res, (f[v][st | s].first + f[v][st | s].second) % P);
					ans = ans * res % P;
				}
			}
			if (x) $(f[u][S].first, ans);
			else $(f[u][S].second, ans);
		}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	srand(19260817);
	Read(n); Read(m);
	int x, y;
	for (int i = 1; i <= m; i++) {
		Read(x); Read(y); G.emplace_back(PI(x, y));
	}
	random_shuffle(G.begin(), G.end());
	for (int i = 0; i < m; i++) {
		Add(G[i].first, G[i].second); Add(G[i].second, G[i].first);
	}
	dfs(1, 0);
	dp(1, 0);

	int ans = 0;
	for (auto v : f[1]) $(ans, (v.first + v.second) % P);

	cout << ans << endl;

	return 0;
}
