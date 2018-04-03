#include <bits/stdc++.h>

typedef long long LL;

const LL INF = 1LL << 60;

using namespace std;

namespace Net {
	const int N = 2010;
	const int M = 50010;
	int head[N], cur[N], sub;
	struct Edge {
		int to, nxt; LL v;
		Edge(int to = 0, int nxt = 0, LL v = 0) : to(to), nxt(nxt), v(v) {}
	} edge[M];
	void Add(int a, int b, LL v) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void Link(int a, int b, LL v) {
		Add(a, b, v); Add(b, a, 0);
	}
	void init() {
		sub = 1;
	}
	int h[N];
	bool bfs(int S, int T) {
		memset(h, -1, sizeof h);
		h[S] = 0; queue<int> q; q.push(S);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to; if (~h[v] || !edge[i].v) continue;
				h[v] = h[u] + 1; q.push(v);
			}
		}
		return ~h[T];
	}
	LL dfs(int u, int T, LL flow) {
		if (u == T) return flow;
		LL used = 0, w = 0;
		for (int &i = cur[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (h[v] != h[u] + 1) continue;
			w = dfs(v, T, min(edge[i].v, flow - used));
			used += w; edge[i].v -= w; edge[i ^ 1].v += w;
			if (used == flow) return used;
		}
		if (!used) h[u] = -1;
		return used;
	}
	LL dinic(int S, int T) {
		LL r = 0;
		while (bfs(S, T)) {
			for (int i = 1; i <= T; i++) cur[i] = head[i];
			r += dfs(S, T, INF);
		}
		return r;
	}
}


const int N = 1010;

int n, m, K;

char s[N][10];

LL ba[10], ans, v[N];
int Ans[N];

void Output(LL x) {
	for (int i = K; i; i--) {
		Ans[i] = x % 2001; x /= 2001LL;
	}
	for (int i = 1; i <= K; i++) printf("%d ", Ans[i]);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	
	scanf("%d%d%d", &n, &m, &K);
	
	Net::init();
	
	ba[0] = 1;
	for (int i = 1; i <= 4; i++) ba[i] = ba[i - 1] * 2001LL;
	
	int S = n + 2, T = n + 3;
	
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1); 
		v[i] = 0;
		for (int j = 1; j <= K; j++) {
			int op = 0;
			if (s[i][j] == '+') op = 1;
			if (s[i][j] == '-') op = -1;
			v[i] += op * ba[K - j];
		}
		if (v[i] >= 0) {
			ans += v[i]; Net::Link(S, i, v[i]);
		} else {
			Net::Link(i, T, -v[i]);
		}
	}
	
	v[n + 1] = 0;
  for (int j = 1; j <= K; j++) v[n + 1] += ba[K - j] * 1000;
  ans += v[n + 1], Net::Link(S, n + 1, v[n + 1]);
  
	int x, y;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d",&x, &y);
		Net::Link(x, y, INF);
	}
	
	ans -= Net::dinic(S, T);
	
	Output(ans);
	return 0;
}
