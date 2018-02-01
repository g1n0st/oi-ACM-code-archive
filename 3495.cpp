#include <bits/stdc++.h>
using namespace std;
const int V = 6000010;
inline int c0(int x) { return x << 1; }
inline int c1(int x) { return x << 1 | 1; }
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

int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V * 2];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int N, M, K, cnt, Tot;
int dfn[V], low[V], bel[V], pT, s[V], t, pT2;
void Tarjan(int u) {
	dfn[u] = low[u] = ++pT; s[++t] = u;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (!dfn[v]) {
			Tarjan(v); low[u] = min(low[u], low[v]);
		}
		else if (!bel[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++pT2; while (1) {
			int v = s[t--]; bel[v] = pT2;
			if (v == u) break;
		}
	}
}
bool Chk() {
	for (int i = 1; i <= (cnt << 1 | 1); i++)
		if (!dfn[i]) Tarjan(i);
	for (int i = 1; i <= cnt; i++)
		if (bel[c0(i)] == bel[c1(i)]) return 0;
	return 1;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int x, y;
	Read(N); Read(M); Read(K);
	for (int i = 1; i <= M; i++) {
		Read(x); Read(y); Add(c0(x), c1(y));  Add(c0(y), c1(x));
	}
	cnt = N;
	while (K--) {
		Read(Tot);
		for (int i = 1; i <= Tot; i++) {
			Read(x); y = cnt + i;
			if (i ^ 1) {
				Add(c0(y), c0(y - 1)); Add(c1(y - 1), c1(y)); Add(c1(x), c0(y - 1));
			} else Add(c0(x), c0(y));
			Add(c0(y), c0(x)); Add(c1(x), c1(y));
			y = cnt + i + Tot;
			if (i ^ Tot) {
				Add(c0(y), c0(y + 1)); Add(c1(y + 1), c1(y)); Add(c1(x), c0(y + 1));
			} else Add(c0(x), c0(y));
			Add(c0(y), c0(x)); Add(c1(x), c1(y));
		} cnt += Tot * 2;
	}
	if (Chk()) puts("TAK");
	else puts("NIE");
	return 0;
}
