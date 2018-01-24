#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 20010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T>
void Read(T &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int N, M; LL a[V];
struct Xor {
	LL p[65];
	Xor() {
		memset(p, 0, sizeof p);
	}
	void Add(LL x) {
		for (int j = 63; ~j; j--) {
			if (!(x >> j)) continue;
			if (!p[j]) {
				p[j] = x; break;
			}
			x ^= p[j];
		}
	}
	LL Query() {
		LL r = 0;
		for (int j = 63; ~j; j--)
			if ((r ^ p[j]) > r)  r ^= p[j];
		return r;
	}
	friend Xor operator + (Xor a, Xor b) {
		Xor r = a;
		for (int j = 63; ~j; j--)
			if (b.p[j]) r.Add(b.p[j]);
		return r;
	}
} bs[V << 2];
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int dep[V], siz[V], fa[V], top[V], id[V], pos[V], pT;
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; dep[v] = dep[u] + 1; Dfs1(v); siz[u] += siz[v];
	}
}
void Dfs2(int u, int path) {
	id[pos[u] = ++pT] = u; top[u] = path;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return; Dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && v ^ k) Dfs2(v, v);
	}
}
void Build(int o, int l, int r) {
	if (l == r) return bs[o].Add(a[id[l]]);
	int Mid = (l + r) >> 1;
	Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
	bs[o] = bs[o << 1] + bs[o << 1 | 1];
}
Xor Query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return bs[o];
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	return Query(o << 1, l, Mid, L, Mid) + Query(o << 1 | 1, Mid + 1, r, Mid + 1, R);
}
LL Query(int x, int y) {
	Xor jd;
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		jd = jd + Query(1, 1, N, pos[top[y]], pos[y]);
		y = fa[top[y]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	jd = jd + Query(1, 1, N, pos[x], pos[y]);
	return jd.Query();
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x, y; Read(N); Read(M);
	for (i = 1; i <= N; i++) Read(a[i]);
	for (i = 1; i < N; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	Dfs1(1); Dfs2(1, 1); Build(1, 1, N);
	while (M--) {
		Read(x); Read(y); printf("%lld\n", Query(x, y));
	}
	return 0;
}
