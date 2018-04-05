#include <bits/stdc++.h>
using namespace std;
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
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}

struct Qr {
	int u, v, lim, id;
	Qr() {}
	Qr(int u, int v, int lim, int id) : u(u), v(v), lim(lim), id(id) {}
	friend bool operator < (const Qr &a, const Qr &b) {
		return a.lim == b.lim ? a.id > b.id : a.lim > b.lim;
	}
} q[V];

int head[V], sub;
struct Edge {
	int to, nxt, v;
	Edge() {}
	Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
} edge[V << 1];
void Add(int a, int b, int v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
int n, Q, M, a[V];

int dep[V], fa[V], siz[V], top[V], pos[V], id[V], pT;
void dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; dep[v] = dep[u] + 1;
		q[++M] = Qr(u, v, edge[i].v, 0);
		dfs1(v); siz[u] += siz[v];
	}
}
void dfs2(int u, int path) {
	id[pos[u] = ++pT] = u; top[u] = path;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return; dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && v != k) dfs2(v, v);
	}
}
int lca(int x, int y) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}

struct Ab {
	int ful, l, r, val;
	Ab() {
		ful = l = r = val = 0;
	}
	Ab(int ful, int l, int r, int val) :
		ful(ful), l(l), r(r), val(val) {}
	friend Ab operator + (const Ab &a, const Ab &b) {
		if (a.ful && b.ful) return Ab(1, a.l + b.l, a.r + b.r, 0);
		if (a.ful) return Ab(0, a.l + b.l, b.r, b.val);
		if (b.ful) return Ab(0, a.l, a.r + b.r, a.val);
		return Ab(0, a.l, b.r, a.val + b.val + ::a[a.r + b.l]);
	}
	int getVal() {
		return ful ? a[l] : val + a[l] + a[r];
	}
} jd[V << 2];

void modify(int o, int l, int r, int p) {
	if (l == r) {
		jd[o] = Ab(1, 1, 1, 0); return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) modify(o << 1, l, mid, p);
	else modify(o << 1 | 1, mid + 1, r, p);
	jd[o] = jd[o << 1] + jd[o << 1 | 1];
}
Ab query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return jd[o];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(o << 1, l, mid, L, R);
	if (mid < L) return query(o << 1 | 1, mid + 1, r, L, R);
	return query(o << 1, l, mid, L, mid) + query(o << 1 | 1, mid + 1, r, mid + 1, R);
}

int query(int x, int y) {
	Ab r1(1, 0, 0, 0), r2(1, 0, 0, 0);
	int l = lca(x, y);
	while (top[x] ^ top[l]) {
		r1 = query(1, 1, n, pos[top[x]], pos[x]) + r1; x = fa[top[x]];
	}
	if (x != l) r1 = query(1, 1, n, pos[l] + 1, pos[x]) + r1;
	while (top[y] ^ top[l]) {
		r2 = query(1, 1, n, pos[top[y]], pos[y]) + r2; y = fa[top[y]];
	}
	if (y != l) r2 = query(1, 1, n, pos[l] + 1, pos[y]) + r2;
	swap(r1.l, r1.r); return (r1 + r2).getVal();
}
int ans[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i < n; i++) Read(a[i]);
	int x, y, w;
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Read(w); ++x; ++y;
		Add(x, y, w); Add(y, x, w);
	}
	Read(Q); M = Q;
	for (int i = 1; i <= Q; i++) {
		Read(x); Read(y); Read(w); ++x; ++y;
		q[i] = Qr(x, y, w, i);
	}
	dfs1(1); dfs2(1, 1);
	sort(q + 1, q + 1 + M);
	for (int i = 1; i <= M; i++) {
		if (!q[i].id) modify(1, 1, n, pos[q[i].v]);
		else ans[q[i].id] = query(q[i].u, q[i].v);
	}
	for (int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
	return 0;
}
