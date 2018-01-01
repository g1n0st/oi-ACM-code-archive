#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
typedef pair<int, int> pl;
typedef priority_queue<pair<int, int>> pq;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}

int Mn[V << 2];
void Build(int o, int l, int r) {
	Mn[o] = 1 << 30; if (l == r) return;
	int Mid = (l + r) >> 1; Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
}
void Modify(int o, int l, int r, int p, int v) {
	if (l == r) {
		Mn[o] = v; return;
	}
	int Mid = (l + r) >> 1;
	if (p <= Mid) Modify(o << 1, l, Mid, p, v); 
	else Modify(o << 1 | 1, Mid + 1, r, p, v);
	Mn[o] = min(Mn[o << 1], Mn[o << 1 | 1]);
}
int Query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return Mn[o];
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	else if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	else return min(Query(o << 1, l, Mid, L, Mid), Query(o << 1 | 1, Mid + 1, r, Mid + 1, R));
}
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V * 2];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
pq Q;
vector<int> G[V];
int f[V][25], d[V], dep[V], pos[V], siz[V], pT, MxDep;
void Dfs(int u, int fa) {
	siz[u] = 1; pos[u] = ++pT; dep[u] = dep[fa] + 1;
	MxDep = max(MxDep, dep[u]); f[u][0] = fa;
	for (int i = 1; i <= 20; i++) f[u][i] = f[f[u][i - 1]][i - 1];
	d[u] = 1 << 30;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue;
		Dfs(v, u); siz[u] += siz[v]; d[u] = min(d[u], d[v] + 1);
	}
	if (d[u] == 1 << 30) d[u] = 0;
	G[d[u]].push_back(u);
}
int Kth(int x, int k) {
	for (int i = 20; ~i; i--)
		if (k >> i & 1) x = f[x][i];
	return x;
}
int N, T, Ans[V], lst[V];
int Che(int x, int k) {
	return Query(1, 1, N, pos[x], pos[x] + siz[x] - 1) <= dep[x] + k - 1;
}
int main() {
	int i, j, x, y;
	Read(N);
	for (i = 1; i < N; i++) {
		Read(x); Read(y);
		Add(x, y); Add(y, x);
	}
	Dfs(1, 0); Build(1, 1, N);
	int lf = 0;
	for (i = 1; i <= N; i++)
		if (!d[i]) ++lf, Modify(1, 1, N, pos[i], dep[i]);
	for (i = 1; i <= MxDep; i++) {
		Ans[i] = lf; *lst = 0;
		pq nul; Q.swap(nul);
		for (auto u : G[i]) Q.push(pl(dep[u], u));
		while (!Q.empty()) {
			auto u = Q.top().second; Q.pop();	 if (Che(u, i)) continue;
			lst[++*lst] = u; Ans[i]++; Modify(1, 1, N, pos[u], dep[u]);
			auto fa = Kth(u, i);
			if (fa) Q.push(pl(dep[fa], fa));
		}
		while (*lst) {
			Modify(1, 1, N, pos[lst[*lst]], 1 << 30); --*lst;
		}
	}
	Read(T);
	while (T--) {
		Read(x); printf("%d\n", Ans[min(x, MxDep)]);
	}
	return 0;
}
