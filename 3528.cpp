#include <bits/stdc++.h>
using namespace std;
typedef double db;
const int V = 200010;
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
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V * 2];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
const db eps = 1e-8;
struct Node {
	int n;
	int xi, yi, xyi, xi2, yi2;
	Node() {
		n = 0;
		xi = yi = xyi = xi2 = yi2 = 0;
	}
	Node(int x, int y) {
		xi = x; yi = y;
		xyi = x * y; xi2 = x * x; yi2 = y * y;
		n = 1;
	}
	friend Node operator + (Node a, Node b) {
		Node r;
		r.xi = a.xi + b.xi; r.yi = a.yi + b.yi; r.xyi = a.xyi + b.xyi;
		r.xi2 = a.xi2 + b.xi2; r.yi2 = a.yi2 + b.yi2;
		r.n = a.n + b.n;
		return r;
	}
	db Calc() {
		db ax = (double)xi / (double)n, ay = (double)yi / (double)n;
		db A = xi2 - 2 * ax * xi + n * ax * ax;
		db B = 2 * ay * xi + 2 * ax * yi - 2 * xyi - 2 * n * ax * ay;
		db C = yi2 - 2 * ay * yi + n * ay * ay;
		db det = B * B / 4 - A * C + (A + C) * (A + C) / 4;
		det = sqrt(det);
		db a1 = (A + C) / 2 - det, a2 = (A + C) / 2 + det;
		if (a1 > a2) swap(a1, a2);
		return a1 > -eps ? a1 : a2;
	}
} v[V << 2];

int N, M, Q, S, x[V], y[V];
int siz[V], c[V], dep[V], fa[V], top[V], pos[V], id[V], pT;
int idc[V], idcf[V], vis[V], cir[V], f[V];
void Dfs1(int u, int co) {
	siz[u] = 1; c[u] = co;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u] || cir[v]) continue;
		fa[v] = u; dep[v] = dep[u] + 1; Dfs1(v, co); siz[u] += siz[v];
	}
}
void Dfs2(int u, int path) {
	top[u] = path; id[pos[u] = ++pT] = u;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return; Dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (dep[v] > dep[u] && v != k) Dfs2(v, v);
	}
}
vector<int> ci;
int Dfs(int u) {
	vis[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == f[u]) continue;
		if (vis[v]) {
			for (int x = u; x != v; x = f[x]) {
				cir[x] = 1; ci.push_back(x);
			}
			cir[v] = 1; ci.push_back(v);
			return 1;
		}
		f[v] = u; if (Dfs(v)) return 1;
	}
	return 0;
}
void Build(int o, int l, int r) {
	if (l == r) {
		if (l <= S) v[o] = Node(x[idcf[l]], y[idcf[l]]);
		else v[o] = Node(x[id[l]], y[id[l]]);
		return;
	}
	int Mid = (l + r) >> 1;
	Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
	v[o] = v[o << 1] + v[o << 1 | 1];
}
Node Query(int o, int l, int r, int L, int R) {
	if (L > R) return Node();
	if (l == L && r == R) return v[o];
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	return Query(o << 1, l, Mid, L, Mid) + Query(o << 1 | 1, Mid + 1, r, Mid + 1, R);
}
Node Query(int x, int y) {
	Node r;
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		r = r + Query(1, 1, pT, pos[top[y]], pos[y]); y = fa[top[y]];
	}
	if (pos[x] > pos[y]) swap(x, y);
	if (pos[x] && pos[y]) r = r + Query(1, 1, pT, pos[x], pos[y]);
	return r;
}
db Tj(int x, int y) {
	if (c[x] == c[y]) return Query(x, y).Calc();
	Node px = Query(c[x], x), py = Query(c[y], y);
	if (idc[c[x]] > idc[c[y]]) swap(x, y);
	Node l1 = Query(1, 1, pT, idc[c[x]] + 1, idc[c[y]] - 1);
	Node l2 = Query(1, 1, pT, 1, idc[c[x]] - 1) + Query(1, 1, pT, idc[c[y]] + 1, S);
	db a1 = (px + py + l1).Calc(), a2 = (px + py + l2).Calc();
	return min(a1, a2);
}
void Init() {
	if (M == N - 1) {
		Dfs1(1, 1); Dfs2(1, 1);
	}
	else {
		Dfs(1);
		S = pT = ci.size();
		for (int i = 0; i < S; i++)
			idc[ci[i]] = i + 1, idcf[i + 1] = ci[i];
		for (int i = 1; i <= N; i++)
			if (cir[i]) Dfs1(i, i), Dfs2(i, i);
	}
	Build(1, 1, pT);
}
int main() {
	int i, j, x, y;
	Read(N); Read(M);
	for (i = 1; i <= N; i++) {
		Read(::x[i]); Read(::y[i]);
	}
	for (i = 1; i <= M; i++) {
		Read(x); Read(y);
		Add(x, y); Add(y, x);
	}
	Init();
	Read(Q);
	while (Q--) {
		Read(x); Read(y);
		printf("%.5lf\n", Tj(x, y));
	}
	return 0;
}
