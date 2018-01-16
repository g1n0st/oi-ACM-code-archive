#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
int head[V], sub;
struct Edge {
	int to, nxt, v;
	Edge() {}
	Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
} edge[V << 1];
void Add(int a, int b, int v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
LL len[V];
int dep[V], fa[V], siz[V], pos[V], top[V], pT;
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; dep[v] = dep[u] + 1; len[v] = len[u] + edge[i].v;
		Dfs1(v); siz[u] += siz[v];
	}
}
void Dfs2(int u, int path) {
	pos[u] = ++pT; top[u] = path;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return; Dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (dep[v] > dep[u] && (v ^ k)) Dfs2(v, v);
	}
}
int lca(int x, int y) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}
LL dis(int x, int y) {
	return len[x] + len[y] - 2 * len[lca(x, y)];
}
LL Ans;
int N, M, vis[V];
struct cmp {
	bool operator () (const int a, const int b) const {
		return pos[a] < pos[b];
	}
};
set<int, cmp> S;
void Join(int x) {
	S.insert(x);
	set<int, cmp>::iterator it = S.find(x);
	int l = 0, r = 0;
	if (it != S.begin()) {
		--it; l = *it; ++it;
	}
	if (++it, it != S.end()) {
		r = *it;
	}
	if (l) Ans += dis(l, x);
	if (r) Ans += dis(x, r);
	if (l && r) Ans -= dis(l, r);
}
void Del(int x) {
	set<int, cmp>::iterator it = S.find(x);
	int l = 0, r = 0;
	if (it != S.begin()) {
		--it; l = *it; ++it;
	}
	if (++it, it != S.end()) {
		r = *it;
	}
	if (l) Ans -= dis(l, x);
	if (r) Ans -= dis(x, r);
	if (l && r) Ans += dis(l, r);
	S.erase(x);
}
int main() {
	int i, j, u, v, w;
	Read(N); Read(M);
	for (i = 1; i < N; i++) {
		Read(u); Read(v); Read(w);
		Add(u, v, w); Add(v, u, w);
	}
	Dfs1(1); Dfs2(1, 1);
	while (M--) {
		Read(u);
		if (vis[u]) Del(u);
		else Join(u);
		vis[u] ^= 1;
		printf("%lld\n", Ans + dis(*S.begin(), *S.rbegin()));
	}
	return 0;
}
