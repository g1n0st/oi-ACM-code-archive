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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
int N, Q, pn[V], nn[V], rpos[V], rt[V];
struct Node {
	int a, pre, nxt, pos;
	Node() {}
	Node(int a, int pre, int nxt) : a(a), pre(pre), nxt(nxt) {}
	friend bool operator < (const Node &a, const Node &b) {
		return a.pre < b.pre;
	}
} v[V];
namespace S1 {
	int ls[V * 400], rs[V * 400], mx[V * 400], pT;
	void Modify(int lst, int &x, int l, int r, int p, int v) {
		x = ++pT; mx[x] = max(v, mx[lst]); ls[x] = ls[lst]; rs[x] = rs[lst];
		if (l == r) return;
		int Mid = (l + r) >> 1;
		if (p <= Mid) return Modify(ls[lst], ls[x], l, Mid, p, v); return Modify(rs[lst], rs[x], Mid + 1, r, p, v);
	}
	int Query(int x, int l, int r, int L, int R) {
		if (!x) return 0;
		if (L == l && r == R) return mx[x];
		int Mid = (l + r) >> 1;
		if (R <= Mid) return Query(ls[x], l, Mid, L, R); if (Mid < L) return Query(rs[x], Mid + 1, r, L, R);
		return max(Query(ls[x], l, Mid, L, Mid), Query(rs[x], Mid + 1, r, Mid + 1, R));
	}
}
namespace S2 {
	int ls[V * 100], rs[V * 100], rt[V * 100], pT;
	void Modify(int lst, int &x, int l, int r, int p, int v1, int v2) {
		x = ++pT; S1::Modify(rt[lst], rt[x], 1, N, v1, v2);
		ls[x] = ls[lst]; rs[x] = rs[lst];
		if (l == r) return;
		int Mid = (l + r) >> 1;
		if (p <= Mid) return Modify(ls[lst], ls[x], l, Mid, p, v1, v2); else return Modify(rs[lst], rs[x], Mid + 1, r, p, v1, v2);
	}
	int Query(int x, int l, int r, int L, int R, int l1, int r1) {
		if (!x) return 0;
		if (L == l && r == R) return S1::Query(rt[x], 1, N, l1, r1);
		int Mid = (l + r) >> 1;
		if (R <= Mid) return Query(ls[x], l, Mid, L, R, l1, r1); if (Mid < L) return Query(rs[x], Mid + 1, r, L, R, l1, r1);
		return max(Query(ls[x], l, Mid, L, Mid, l1, r1), Query(rs[x], Mid + 1, r, Mid + 1, R, l1, r1));
	}
}
int main() {
	int i, j;
	Read(N); Read(Q);
	for (i = 1; i <= N; i++) {
		Read(v[i].a); v[i].pos = i;
	}
	for (i = 1; i <= N; i++) {
		v[i].pre = pn[v[i].a]; pn[v[i].a] = i; nn[i] = N + 1;
	}
	for (i = N; i; i--) {
		v[i].nxt = nn[v[i].a]; nn[v[i].a] = i;
	}
	sort(v + 1, v + 1 + N);
	for (i = 1; i <= N; i++) {
		rpos[v[i].pre] = i;
		S2::Modify(rt[i - 1], rt[i], 1, N + 1, v[i].nxt, v[i].pos, v[i].a);
	}
	for (i = 1; i <= N; i++)
		if (!rpos[i]) rpos[i] = rpos[i - 1];
	int L, R, x, y, lastAns = 0;
	while (Q--) {
		Read(x); Read(y);
		L = min((x + lastAns) % N + 1, (y + lastAns) % N + 1);
		R = max((x + lastAns) % N + 1, (y + lastAns) % N + 1);
		lastAns = S2::Query(rt[rpos[L - 1]], 1, N + 1, R + 1, N + 1, L, R);
		printf("%d\n", lastAns);
	}
	return 0;
}
