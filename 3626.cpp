#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
const int P = 201314;
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
int N, M;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}

int tag[V << 2], sum[V << 2];
void setv(int o, int l, int r, int v) {
	(tag[o] += v) %= P; (sum[o] += (r - l + 1) * v % P) %= P;
}
void pushDown(int o, int l, int r) {
	if (tag[o]) {
		int Mid = (l + r) >> 1;
		setv(o << 1, l, Mid, tag[o]); setv(o << 1 | 1, Mid + 1, r, tag[o]); tag[o] = 0;
	}
}
void Modify(int o, int l, int r, int L, int R) {
	if (l >= L && r <= R) return setv(o, l, r, 1);
	int Mid = (l + r) >> 1; pushDown(o, l, r);
	if (L <= Mid) Modify(o << 1, l, Mid, L, R);
	if (Mid < R) Modify(o << 1 | 1, Mid + 1, r, L, R);
	sum[o] = (sum[o << 1] + sum[o << 1 | 1]) % P;
}
int Query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return sum[o];
	int Mid = (l + r) >> 1; pushDown(o, l, r);
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	return Query(o << 1, l, Mid, L, Mid) + Query(o << 1 | 1, Mid + 1, r, Mid + 1, R);
}

int siz[V], dep[V], fa[V], pos[V], top[V], pT;
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; fa[v] = u; dep[v] = dep[u] + 1; Dfs1(v); siz[u] += siz[v];
	}
}
void Dfs2(int u, int path) {
	pos[u] = ++pT; top[u] = path;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (siz[v] > siz[k]) k = v;
	}
	if (!k) return; Dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v ^ k) Dfs2(v, v);
	}
}
void Modify(int x) {
	while (top[x] ^ 1) {
		Modify(1, 1, N, pos[top[x]], pos[x]); x = fa[top[x]];
	}
	Modify(1, 1, N, 1, pos[x]);
}
int Query(int x) {
	int r = 0;
	while (top[x] ^ 1) {
		(r += Query(1, 1, N, pos[top[x]], pos[x])) %= P; x = fa[top[x]];
	}
	(r += Query(1, 1, N, 1, pos[x])) %= P;
	return r;
}
struct Node {
	int id, z, f;
	Node(int id = 0, int z = 0, int f = 0) : id(id), z(z), f(f) {}
};
vector<Node> md[V]; int Ans[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(M);
	for (int i = 2, f; i <= N; i++) {
		Read(f); Add(++f, i);
	}
	Dfs1(1); 
	Dfs2(1, 1);
	int l, r, z;
	for (int i = 1; i <= M; i++) {
		Read(l); Read(r); Read(z); ++l; ++r; ++z;
		md[r].push_back(Node(i, z, 1));
		md[l - 1].push_back(Node(i, z, -1));
	}
	for (int i = 1; i <= N; i++) {
		Modify(i);
		for (int j = 0; j < md[i].size(); j++)
			(Ans[md[i][j].id] += (P + md[i][j].f * Query(md[i][j].z))) %= P;
	}
	for (int i = 1; i <= M; i++) printf("%d\n", Ans[i]);
	return 0;
}
