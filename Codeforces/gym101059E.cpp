#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 50005;
const int P = 1000000007;
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
void Read(int *s, int &len) {
	len = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); s[len++] = c - '0', c = get());
}
void Add(int &x, int y) {
	(x += y) %= P;
}

int n, Q, a[V];

const int D = 10;
int m[D][D], d1[D * D], d2[D * D], rev[D * D];
struct Node {
	int a[D], aab[D * D], abb[D * D], ab[D * D], abba[D * D], aa[D];
	Node() {
		for (int i = 0; i < D; i++) a[i] = aa[i] = 0;
		for (int i = 0; i < D * D; i++) aab[i] = abb[i] = ab[i] = abba[i] = 0;
	}
	friend Node operator + (const Node &x, const Node &y) {
		Node r;
		// upd a[]
		for (int i = 0; i < D; i++) Add(r.a[i], x.a[i] + y.a[i]);
		// upd aa[]
		for (int i = 0; i < D; i++) {
			r.aa[i] = (LL)x.a[i] * y.a[i] % P;
			Add(r.aa[i], x.aa[i]); Add(r.aa[i], y.aa[i]);
		}
		// upd ab[]
		for (int i = 0; i < D; i++)
			for (int j = 0; j < D; j++) r.ab[m[i][j]] = (LL)x.a[i] * y.a[j] % P;
		for (int i = 0; i < D * D; i++) {
			Add(r.ab[i], x.ab[i]); Add(r.ab[i], y.ab[i]);
		}
		// upd abb[] & aab[]
		for (int i = 0; i < D * D; i++) {
			r.abb[i] = (LL)x.ab[i] * y.a[d2[i]] % P;
			Add(r.abb[i], (LL)x.a[d1[i]] * y.aa[d2[i]] % P);
			Add(r.abb[i], x.abb[i]); Add(r.abb[i], y.abb[i]);
		}
		for (int i = 0; i < D * D; i++) {
			r.aab[i] = (LL)y.ab[i] * x.a[d1[i]] % P;
			Add(r.aab[i], (LL)x.aa[d1[i]] * y.a[d2[i]] % P);
			Add(r.aab[i], x.aab[i]); Add(r.aab[i], y.aab[i]);
		}
		// upd abba
		for (int i = 0; i < D * D; i++) r.abba[i] = (x.abba[i] + y.abba[i]) % P;
		for (int i = 0; i < D * D; i++) Add(r.abba[i], (LL)x.ab[i] * y.ab[rev[i]] % P);
		for (int i = 0; i < D * D; i++) Add(r.abba[i], (LL)x.abb[i] * y.a[d1[i]] % P);
		for (int i = 0; i < D * D; i++) Add(r.abba[i], (LL)y.aab[i] * x.a[d2[i]] % P);
		
		return r;
	}
} val[V << 2];
void build(int o, int l, int r) {
	if (l == r) {
		val[o].a[a[l]]++; return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	val[o] = val[o << 1] + val[o << 1 | 1];
}
void modify(int o, int l, int r, int p, int v) {
	if (l == r) {
		val[o].a[a[l]]--; a[l] = v; val[o].a[a[l]]++; return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) modify(o << 1, l, mid, p, v);
	else modify(o << 1 | 1, mid + 1, r, p, v);
	val[o] = val[o << 1] + val[o << 1 | 1];
}
Node query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return val[o];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(o << 1, l, mid, L, R);
	if (mid < L) return query(o << 1 | 1, mid + 1, r, L, R);
	return query(o << 1, l, mid, L, mid) + query(o << 1 | 1, mid + 1, r, mid + 1, R);
}
void Pre() {
	for (int i = 0; i < D; i++)
		for (int j = 0; j < D; j++) {
			m[i][j] = i * D + j; d1[m[i][j]] = i; d2[m[i][j]] = j;
			rev[m[i][j]] = j * D + i;
		}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Pre(); Read(a + 1, n); 
	Read(Q); build(1, 1, n);
	int op, a, b;
	while (Q--) {
		Read(op); Read(a); Read(b);
		if (op & 1) {
			Node t = query(1, 1, n, a, b); int ans = 0;
			for (int i = 0; i < D * D; i++) Add(ans, t.abba[i]);
			printf("%d\n", ans);
		}
		else modify(1, 1, n, a, b);
	}
	return 0;
}
