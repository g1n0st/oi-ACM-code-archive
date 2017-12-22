#include <bits/stdc++.h>
using namespace std;
const int V = 2000010;
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
int T, N, M;
int Tag[V], s[V][2], rt[V], vis[V], sg[V], siz[V], pT;
int NewNode() {
	++pT;
	Tag[pT] = s[pT][0] = s[pT][1] = 0;
	siz[pT] = 1;
	return pT;
}
void pushDown(int u, int k) {
	if ((Tag[u] >> k) & 1) swap(s[u][0], s[u][1]);
	int o = Tag[u] & ((1 << k) - 1); Tag[u] = 0;
	Tag[s[u][0]] ^= o; Tag[s[u][1]] ^= o;
}
int Merge(int u, int v, int d) {
	if (!u || !v) return u + v;
	pushDown(u, d); pushDown(v, d);
	s[u][1] = Merge(s[u][1], s[v][1], d - 1);
	s[u][0] = Merge(s[u][0], s[v][0], d - 1);
	return u;
}
void Insert(int &u, int val, int d) {
	if (!u) u = NewNode();
	if (~d) {
		pushDown(u, d);
		Insert(s[u][(val >> d) & 1], val, d - 1);
		siz[u] = siz[s[u][0]] + siz[s[u][1]];
	}
}
int GetAns(int u) {
	int Ret = 0;
	for (int i = 16; ~i; i--) {
		Ret <<= 1;
		if (siz[s[u][0]] < (1 << i)) u = s[u][0];
		else Ret |= 1, u = s[u][1];
	}
	return Ret;
}
void Clear() {
	int i, j;
	for (i = 1; i <= N; i++) head[i] = rt[i] = vis[i] = sg[i] = 0;
	sub = pT = 0;
}
void Dfs(int u, int fa) {
	int tsg = 0; vis[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (v == fa) continue;
		Dfs(v, u); tsg ^= sg[v];
	}
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (v == fa) continue;
		Tag[rt[v]] ^= (tsg ^ sg[v]);
		rt[u] = Merge(rt[u], rt[v], 16);
	}
	Insert(rt[u], tsg, 16); sg[u] = GetAns(rt[u]);
}
void Solve() {
	Clear();
	int i, j, a, b;
	Read(N); Read(M);
	for (i = 1; i <= M; i++) {
		Read(a); Read(b);
		Add(a, b); Add(b, a);
	}
	int Ans = 0;
	for (i = 1; i <= N; i++) {
		if (vis[i]) continue;
		Dfs(i, 0); Ans ^= sg[i];
	}
	puts(Ans ? "Alice" : "Bob");
}
int main() {
	Read(T);
	while (T--) Solve();
	return 0;
}
