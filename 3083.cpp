#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
const int INF = 1 << 30;
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
int N, M, Rt, a[V];
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int dep[V], siz[V], fa[V], pos[V], top[V], id[V], pT;
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (fa[u] == v) continue;
		dep[v] = dep[u] + 1; fa[v] = u; Dfs1(v); siz[u] += siz[v];
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

int tag[V << 2], mn[V << 2];
void Build(int o, int l, int r) {
	if (l == r) {
		mn[o] = a[id[l]]; return;
	}
	int Mid = (l + r) >> 1;
	Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
	mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
}
void setv(int o, int v) {
	tag[o] = mn[o] = v;
}
void pushDown(int o) {
	if (tag[o]) {
		setv(o << 1, tag[o]); setv(o << 1 | 1, tag[o]); tag[o] = 0;
	}
}
void Modify(int o, int l, int r, int L, int R, int v) {
	if (l == L && r == R)  return setv(o, v);
	int Mid = (l + r) >> 1; pushDown(o);
	if (R <= Mid) Modify(o << 1, l, Mid, L, R, v);
	else if (Mid < L) Modify(o << 1 | 1, Mid + 1, r, L, R, v);
	else Modify(o << 1, l, Mid, L, Mid, v), Modify(o << 1 | 1, Mid + 1, r, Mid + 1, R, v);
	mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
}
int Query(int o, int l, int r, int L, int R) {
	if (L > R) return INF;
	if (l == L && r == R) return mn[o];
	int Mid = (l + r) >> 1; pushDown(o);
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	return min(Query(o << 1, l, Mid, L, Mid), Query(o << 1 | 1, Mid + 1, r, Mid + 1, R));
}
void Modify(int x, int y, int v) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		Modify(1, 1, N, pos[top[y]], pos[y], v); y = fa[top[y]];
	}
	if (pos[x] > pos[y]) swap(x, y);
	Modify(1, 1, N, pos[x], pos[y], v);
}
int find(int x, int y) {
	while (top[x] ^ top[y]) {
		if (fa[top[x]] == y) return top[x];
		x = fa[top[x]];
	}
	return id[pos[y] + 1];
}
int Query(int x) {
	if (Rt == x) return Query(1, 1, N, 1, N);
	if (pos[x] >= pos[Rt] && pos[x] <= pos[Rt] + siz[Rt] - 1) return Query(1, 1, N, pos[x], pos[x] + siz[x] - 1);
	if (pos[Rt] < pos[x] || pos[Rt] > pos[x] + siz[x] - 1) return Query(1, 1, N, pos[x], pos[x] + siz[x] - 1);
	int f = find(Rt, x);
	return min(Query(1, 1, N, 1, pos[f] - 1), Query(1, 1, N, pos[f] + siz[f], N));
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(M);
	int op, x, y, v;
	for (int i = 1; i < N; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	for (int i = 1; i <= N; i++) Read(a[i]);
	Read(Rt);
	Dfs1(Rt); Dfs2(Rt, Rt); Build(1, 1, N);
	while (M--) {
		Read(op); Read(x);
		if (op == 1) Rt = x;
		else if (op == 2) {
			Read(y); Read(v); 
			Modify(x, y, v);
		}
		else printf("%d\n", Query(x));
	}
	return 0;
}
