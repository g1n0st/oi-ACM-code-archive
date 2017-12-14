#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef long long LL;
const int V = 3010;
void Read(int &x) {
	scanf("%d", &x);
}
int N, M, pos[V], a[V];
struct Node {
	LL tot, lm, rm, mx;
	Node() {}
	Node(LL tot, LL lm, LL rm, LL mx) : tot(tot), lm(lm), rm(rm), mx(mx) {}
} v[V << 2];
Node Merge(Node a, Node b) {
	Node x;
	x.tot = a.tot + b.tot;
	x.lm = max(a.lm, a.tot + b.lm);
	x.rm = max(b.rm, b.tot + a.rm);
	x.mx = max(a.mx, b.mx);
	x.mx = max(x.mx, max(x.lm, x.rm));
	x.mx = max(x.mx, a.rm + b.lm);
	return x;
}
void Modify(int o, int l, int r, int p, int val) {
	if (l == r) {
		v[o] = Node(val, val, val, val);
		return;
	}
	int Mid = (l + r) >> 1;
	if (p <= Mid) Modify(o << 1, l, Mid, p, val);
	else Modify(o << 1 | 1, Mid + 1, r, p, val);
	v[o] = Merge(v[o << 1], v[o << 1 | 1]);
}
Node Query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return v[o];
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	else if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	return Merge(Query(o << 1, l, Mid, L, Mid), Query(o << 1 | 1, Mid + 1, r, Mid + 1, R));
}
void Build(int o, int l, int r) {
	if (l == r) {
		v[o] = Node(a[l], a[l], a[l], a[l]);
		return;
	}
	int Mid = (l + r) >> 1;
	Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
	v[o] = Merge(v[o << 1], v[o << 1 | 1]);
}
struct P {
	int x, y, w;
	P() {}
	P(int x, int y, int w) : x(x), y(y), w(w) {}
	friend bool operator < (const P &a, const P &b) {
		if (a.x != b.x) return a.x < b.x;
		return a.y < b.y;
	}
} p[V];
struct E {
	int n1, n2, a, b;;
	E() {}
	E(int n1, int n2, int a, int b) : n1(n1), n2(n2), a(a), b(b) {}
	friend bool operator < (const E &a, const E &b) {
		if (1LL * a.n1 * b.n2 != 1LL * b.n1 * a.n2) {
			return 1LL * a.n1 * b.n2 > 1LL * b.n1 * a.n2;
		}
		if (a.b != b.b) return a.b < b.b;
		return a.a < b.a;
	}
	friend bool operator == (const E &a, const E &b) {
		return 1LL * a.n1 * b.n2 == 1LL * b.n1 * a.n2;
	}
} e[V * V];
void Swap(int a, int b) {
	int &x = pos[a], &y = pos[b];
	Modify(1, 1, N, x, ::a[y]); Modify(1, 1, N, y, ::a[x]);
	swap(::a[x], ::a[y]); swap(x, y);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x, y, w;
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(x); Read(y); Read(w);  p[i] = P(x, y, w);
	}
	sort(p + 1, p + 1 + N);
	for (i = 1; i <= N; i++) a[i] = p[i].w;
	for (i = 1; i <= N; i++) pos[i] = i;
	Build(1, 1, N);
	for (i = 1; i <= N; i++)
		for (j = i + 1; j <= N; j++)
			e[++M] = E(p[i].y - p[j].y, p[i].x - p[j].x, i, j);
	sort(e + 1, e + 1 + M);
	LL Ans = max(0LL, Query(1, 1, N, 1, N).mx);
	for (i = 1; i <= M; i++) {
		Swap(e[i].a, e[i].b);
		if (i < M && e[i] == e[i + 1]) continue;
		Ans = max(Ans, Query(1, 1, N, 1, N).mx);
	}
	printf("%lld\n", Ans);
	return 0;
}
