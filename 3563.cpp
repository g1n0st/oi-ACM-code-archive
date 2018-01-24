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
	x = 0; static char c; int f = 0;
	for (; !(c >= '0' && c <= '9'); c = get()) f ^= (c == '-');
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get()); if (f) x = -x;
}
struct Xor {
	LL p[64];
	Xor() {
		memset(p, 0, sizeof p);
	}
	int Add(LL x) {
		for (int i = 63; ~i; i--) {
			if (!(x >> i)) continue;
			if (!p[i]) {
				p[i] = x; return 0;
			}
			x ^= p[i];
		}
		return 1;
	}
};
LL Rd() {
	return ((LL)rand() << 30) | rand();
}
int head[V], sub;
struct Edge {
	int to, nxt; LL v;
	Edge() {}
	Edge(int to, int nxt, LL v = 0) : to(to), nxt(nxt), v(v) {}
} edge[V * 10];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int N, M, Q, rke[V * 10], v1[V], v2[V]; LL val[V];
void Dfs1(int u, int fa) {
	v1[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (v == fa) continue;
		else if (!v1[v]) {
			Dfs1(v, u); continue;
		}
		else if (edge[i].v) continue;
		int x = Rd();
		edge[i].v = edge[i ^ 1].v = x;
		val[u] ^= x; val[v] ^= x;
	}
}
int Dfs2(int u) {
	v2[u] = 1; LL y = val[u];
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v2[v]) continue;
		int x = Dfs2(v);
		edge[i].v = edge[i ^ 1].v = x;
		y ^= x;
	}
	return y;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	srand(23333);
	int i, j, x, y, k;
	Read(N); Read(M); sub = 1;
	for (i = 1; i <= M; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
		rke[i] = sub;
	}
	Dfs1(1, 0);
	Dfs2(1);
	Read(Q);
	int lstAns = 0;
	while (Q--) {
		Read(k); k ^= lstAns; Xor s; int flg = 0;
		for (j = 1; j <= k; j++) {
			Read(x); x ^= lstAns;
			if (flg) continue;
			flg |= s.Add(edge[rke[x]].v);
		}
		if (flg) puts("Disconnected");
		else {
			lstAns++; puts("Connected");
		}
	}
	return 0;
}
