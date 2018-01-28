#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
const int K = 12;
typedef pair<int, int> PI;
typedef vector<PI>::iterator ddq;
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
struct Node {
	int w, id;
	Node(int w = 0, int id = 0) : w(w), id(id) {}
	friend bool operator < (const Node &a, const Node &b) {
		return a.w < b.w;
	}
} e[V << 1];
int N, M, L, B;
int a[V], bel[V], tag[V], bl[V], br[V];
int head[V], sub;
struct Edge {
	int to, nxt, v;
	Edge(int to = 0, int nxt = 0, int v = 0) : to(to), nxt(nxt), v(v) {}
} edge[V << 1];
void Add(int a, int b, int v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
int st[V], ed[V], pT, lim;
void Dfs(int u, int w) {
	st[u] = ++pT; e[pT] = Node(w, pT);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; Dfs(v, w + edge[i].v);
	}
	ed[u] = pT;
}
Node p1[V], p2[V];
void Modify(int x, int l, int r, int w) {
	int t1 = 0, t2 = 0, tot = bl[x], i, j;
	for (i = bl[x]; i <= br[x]; i++)
		if (e[i].id >= l && e[i].id <= r) p1[t1++] = Node(e[i].w + w, e[i].id);
		else p2[t2++] = e[i];
		i = j = 0;
		while ((i ^ t1) || (j ^ t2)) {
			if (j == t2) e[tot++] = p1[i++];
			else if (i == t1) e[tot++] = p2[j++];
			else if (p1[i] < p2[j]) e[tot++] = p1[i++];
			else e[tot++] = p2[j++];
		}
}
void Modify(int x, int w) {
	int X = bel[st[x]], Y = bel[ed[x]];
	for (int i = X + 1; i < Y; i++) tag[i] += w;
	Modify(X, st[x], ed[x], w);
	if (X < Y) Modify(Y, st[x], ed[x], w);
}
int Check(int x, int w) {
	int l = bl[x], r = br[x], Mid, Ans = bl[x] - 1;
	while (l <= r) {
		if (e[Mid = (l + r) >> 1].w <= w) l = (Ans = Mid) + 1;
		else r = Mid - 1;
	}
	return Ans - bl[x] + 1;
}
int Kth(int x, int y, int k) {
	if (y - x + 1 < k) return -1;
	int X = bel[x], Y = bel[y];

	bl[B + 1] = N + 1; br[B + 1] = N;
	for (int i = bl[X]; i <= br[X]; i++)
		if (e[i].id >= x && e[i].id <= y) e[++br[B + 1]] = e[i];
	if (X < Y) {
		bl[B + 2] = br[B + 1] + 1; br[B + 2] = br[B + 1];
		for (int i = bl[Y]; i <= br[Y]; i++)
			if (e[i].id >= x && e[i].id <= y) e[++br[B + 2]] = e[i];
	}
	int L = 0, R = lim, Mid, Ans = 0, ck;
	while (L <= R) {
		Mid = (L + R) >> 1; ck = 0;
		for (int i = X + 1; i < Y; i++) ck += Check(i, Mid - tag[i]);
		ck += Check(B + 1, Mid - tag[X]); if (X < Y) ck += Check(B + 2, Mid - tag[Y]);
		if (ck >= k) R = (Ans = Mid) - 1;
		else L = Mid + 1;
	}
	return Ans;
}
int main() {
	Read(N); Read(M); Read(L);
	for (int i = 2, f, w; i <= N; i++) {
		Read(f); Read(w); Add(f, i, w); lim += w;
	}
	B = (N >> K); Dfs(1, 0);
	for (int i = 1; i <= N; i++) bel[i] = (i >> K);
	for (int i = 1; i <= N; i++) br[bel[i]] = i;
	for (int i = N; i; i--) bl[bel[i]] = i;
	for (int i = 0; i <= B; i++) sort(e + bl[i], e + br[i] + 1);
	int op, x, y;
	while (M--) {
		Read(op); Read(x); Read(y);
		if (op & 1) printf("%d\n", Kth(st[x], ed[x], y));
		else Modify(x, y), lim += y;
	}
	return 0;
}
