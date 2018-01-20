#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
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
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int N, M;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int siz[V], dep[V], fa[V], pos[V], top[V], id[V], pT;
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
int LCA(int x, int y) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}
namespace SGT {
	int mx[V << 2], tag[V << 2];
	void setv(int o, int v) {
		mx[o] += v; tag[o] += v;
	}
	void pushDown(int o) {
		if (tag[o]) {
			setv(o << 1, tag[o]); setv(o << 1 | 1, tag[o]); tag[o] = 0;
		}
	}
	void pushUp(int o) {
		mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
	}
	void Build(int o, int l, int r) {
		if (l == r) {
			mx[o] = dep[id[l]]; return;
		}
		int Mid = (l + r) >> 1;
		Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
		pushUp(o);
	}
	void Modify(int o, int l, int r, int L, int R, int v) {
		if (l >= L && r <= R) return setv(o, v);
		int Mid = (l + r) >> 1; pushDown(o);
		if (L <= Mid) Modify(o << 1, l, Mid, L, R, v);
		if (Mid < R) Modify(o << 1 | 1, Mid + 1, r, L, R, v);
		pushUp(o);
	}
	int Query(int o, int l, int r, int L, int R) {
		if (l == L && r == R) return mx[o];
		int Mid = (l + r) >> 1; pushDown(o);
		if (R <= Mid) return Query(o << 1, l, Mid, L, R);
		if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
		return max(Query(o << 1, l, Mid, L, Mid), Query(o << 1 | 1, Mid + 1, r, Mid + 1, R));
	}
}
namespace LCT {
	int c[V][2], fa[V];
	bool Rt(int x) {
		return c[fa[x]][0] != x && c[fa[x]][1] != x;
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
		if (!Rt(y)) {
			if (c[z][0] == y) c[z][0] = x;
			else c[z][1] = x;
		}
		fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
		c[y][l] = c[x][r]; c[x][r] = y;
	}
	void splay(int x) {
		while (!Rt(x)) {
			int y = fa[x], z = fa[y];
			if (!Rt(y)) {
				if ((c[y][0] == x) ^ (c[z][0] == y)) rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
	}
	void Work(int x, int v) {
		if (!x) return;
		while (c[x][0]) x = c[x][0];
		SGT::Modify(1, 1, N, pos[x], pos[x] + siz[x] - 1, v);
	}
	void Access(int x) {
		for (int t = 0; x; t = x, x = fa[x]) {
			splay(x); Work(c[x][1], 1); Work(t, -1); c[x][1] = t;
		}
	}
}
int Ask(int x, int y) {
	int l = LCA(x, y);
	x = SGT::Query(1, 1, N, pos[x], pos[x]);
	y = SGT::Query(1, 1, N, pos[y], pos[y]);
	l = SGT::Query(1, 1, N, pos[l], pos[l]);
	return x + y - l * 2 + 1;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x, y;
	Read(N); Read(M);
	for (i = 1; i < N; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	Dfs1(dep[1] = 1); Dfs2(1, 1); SGT::Build(1, 1, N);
	for (i = 1; i <= N; i++) LCT::fa[i] = fa[i];
	int op;
	while (M--) {
		Read(op);
		switch (op) {
		case 1: Read(x); LCT::Access(x); break;
		case 2: Read(x); Read(y); printf("%d\n", Ask(x, y)); break;
		default: Read(x); 
			printf("%d\n", SGT::Query(1, 1, N, pos[x], pos[x] + siz[x] - 1)); break;
		}
	}
	return 0;
}
