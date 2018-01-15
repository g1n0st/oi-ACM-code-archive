#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
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

int head[V], sub, deg[V];
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub; deg[b]++;
}
int n, C, co[V], lst;
namespace SAM {
	int c[V << 1][11], fa[V << 1], len[V << 1], pT, rt;
	void Init() {
		rt = ++pT;
	}
	void Extend(int x) {
		int p = lst, q = c[p][x];
		if (q) {
			if (len[q] == len[p] + 1) lst = q;
			else {
				++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[q] = pT;
				lst = pT;
			}
		}
		else {
			int cur = ++pT; len[cur] = len[lst] + 1;
			while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
			if (!p) fa[cur] = rt;
			else {
				q = c[p][x];
				if (len[q] == len[p] + 1) fa[cur] = q;
				else {
					++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
					memcpy(c[pT], c[q], sizeof c[q]);
					while (c[p][x] == q) c[p][x] = pT, p = fa[p];
					fa[q] = fa[cur] = pT;
				}
			}
			lst = cur;
		}
	}
	void Work() {
		LL x = 0;
		for (int i = 1; i <= pT; i++)
			x += len[i] - len[fa[i]];
		printf("%lld\n", x);
	}
}
void Dfs(int u, int fa, int p) {
	SAM::Extend(co[u]);
	int t = lst;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue;
		Dfs(v, u, lst); lst = t;
	}
}
int main() {
	int i, j, x, y;
	Read(n); Read(C); SAM::Init();
	for (i = 1; i <= n; i++) Read(co[i]);
	for (i = 1; i < n; i++) {
		Read(x); Read(y);
		Add(x, y); Add(y, x);
	}
	for (i = 1; i <= n; i++) {
		if (deg[i] ^ 1) continue;
		Dfs(i, 0, lst = SAM::rt);
	}
	SAM::Work();
	return 0;
}
