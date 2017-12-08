#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
const int V = 200010;
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
		x = x * 10 + c - '0';
		c = get();
	}
}
int N, M, Q, Now;
int fa[V], siz[V], rk[V];
int Ans[V], id[V], t1[V], t2[V], suc[V], xx[V], yy[V], rr[V];
void Init(int n) {
	int i, j;
	for (i = 1; i <= n; i++) {
		fa[i] = i; siz[i] = rk[i] = 1;
	}
}
int Getf(int x) {
	return x == fa[x] ? x : Getf(fa[x]);
}
struct Cr {
	int x, y, r;
	Cr () {}
	Cr (int x, int y, int r) : x(x), y(y), r(r) {}
} cr[V]; int t;
void Link(int x, int y) {
	x = Getf(x); y = Getf(y); bool r = 0;
	if (x == y) return ;
	if (rk[x] > rk[y]) swap(x, y);
	fa[x] = y; siz[y] += siz[x];
	if (rk[x] == rk[y]) rk[y]++, r = 1;
	cr[++t] = Cr(x, y, r);
}
void Cut(void) {
	int x = cr[t].x, y = cr[t].y;
	fa[x] = x; siz[y] -= siz[x];
	rk[y] -= cr[t].r; t--;
}
struct E {
	int x, y;
} e[V];
struct O {
	int x, y, v;
} o[V];
void Solve(int l, int r, int L, int R) {
	int i, j, x, y, tot;
	if (l > r) return;
	if (L == R) {
		for (i = l; i <= r; i++) Ans[id[i]] = L;
		return;
	}
	int Mid = (L + R) >> 1, cur = t;
	for (i = L; i <= Mid; i++) Link(e[i].x, e[i].y);
	*t1 = *t2 = 0;
	for (i = l; i <= r; i++) {
		x = Getf(o[id[i]].x); y = Getf(o[id[i]].y);
		if (x == y) tot = siz[x];
		else tot = siz[x] + siz[y];

		if (tot >= o[id[i]].v) t1[++*t1] = id[i];
		else t2[++*t2] = id[i];
	}
	int l1 = l, l2 = l + *t1 - 1;
	for (i = 1; i <= *t1; i++) id[l1++] = t1[i];
	for (i = 1; i <= *t2; i++) id[l1++] = t2[i];
	Solve(l2 + 1, r, Mid + 1, R);
	while (t > cur) Cut();
	Solve(l, l2, L, Mid);
}
int main(void) {
	int i, j;
	Read(N); Read(M); Init(N);
	for (i = 1; i <= M; i++) {
		Read(e[i].x); Read(e[i].y);
	}
	Read(Q);
	for (i = 1; i <= Q; i++) {
		Read(o[i].x); Read(o[i].y); Read(o[i].v);
	}
	for (i = 1; i <= Q; i++) id[i] = i;
	Solve(1, Q, 1, M);
	for (i = 1; i <= Q; i++) printf("%d\n", Ans[i]);
	return 0;
}
