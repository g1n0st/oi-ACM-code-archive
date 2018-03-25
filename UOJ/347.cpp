#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
const int SMALL_RANGE = 3000;
const double TIME_LIMIT = 3200.;
double BG_T;
inline double clk() {
	return (double)clock() / (double)CLOCKS_PER_SEC * 1000.0;
}
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T> void Read(T &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
struct Edge {
	int to, nxt; LL v;
	Edge() {}
	Edge(int to, int nxt, LL v) : to(to), nxt(nxt), v(v) {}
};
struct G {
	int head[V], sub; 
	Edge edge[V << 1];
	void Add(int a, int b, LL v) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void Init(int n) {
		int u, v; LL w;
		for (int i = 1; i < n; i++) {
			Read(u); Read(v); Read(w); Add(u, v, w); Add(v, u, w);
		}
	}
	LL val[V];
	void dfs(int u, int fa) {
		if (!fa) val[u] = 0;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (v == fa) continue;
			val[v] = val[u] + edge[i].v; dfs(v, u);
		}
	}
} t[3];
LL ans;
int n, vis[V];
void Solve1() {
	for (int i = 1; i <= n; i++) {
		t[0].dfs(i, 0); t[1].dfs(i, 0); t[2].dfs(i, 0);
		for (int j = 1; j <= n; j++) ans = max(ans, t[0].val[j] + t[1].val[j] + t[2].val[j]);
	}
	cout << ans << endl;
	exit(0);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	BG_T = clk();
	Read(n); t[0].Init(n); t[1].Init(n); t[2].Init(n);

	if (n <= SMALL_RANGE) Solve1();
	
	while (clk() - BG_T <= TIME_LIMIT) {
		int rt = rand() % n + 1; while (vis[rt]) rt = rand() % n + 1;
		for (int i = 1; i <= 8; i++) {
			if (vis[rt]) break; vis[rt] = 1;
			t[0].dfs(rt, 0); t[1].dfs(rt, 0); t[2].dfs(rt, 0);
			LL mx = 0;
			for (int j = 1; j <= n; j++) {
				LL cur = t[0].val[j] + t[1].val[j] + t[2].val[j];
				ans = max(cur, ans);
				if (!vis[j] && cur > mx) {
					rt = j; mx = cur;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
