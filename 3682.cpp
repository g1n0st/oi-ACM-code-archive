#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 500010;
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
void Read(char *s, int len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get()); s[len] = 0;
}
void Read(char &x) {
	x = get(); while (!isupper(x)) x = get();
}
int n, m, len, type, lstAns;
namespace SufT {
	int ch[V][2], h[V], c[V], pT, rt;
	LL rk[V];
	void rebuild(int &x, LL l, LL r) {
		if (!x) return; rk[x] = l + r;
		LL Mid = (l + r) >> 1;
		rebuild(ch[x][0], l, Mid); rebuild(ch[x][1], Mid + 1, r);
	}
	void rotate(int &x, int d, LL l, LL r) {
		int k = ch[x][d ^ 1];
		ch[x][d ^ 1] = ch[k][d]; ch[k][d] = x; x = k; rebuild(x, l, r);
	}
	int cmp(int x, int y) {
		return c[x] ^ c[y] ? c[x] < c[y] : rk[x - 1] < rk[y - 1];
	}
	void Insert(int &x, LL l, LL r) {
		if (!x) {
			x = pT; rk[x] = l + r; return;
		}
		LL Mid = (l + r) >> 1;
		int d = cmp(pT, x);
		d ? Insert(ch[x][0], l, Mid) : Insert(ch[x][1], Mid + 1, r);
		if (h[ch[x][d ^ 1]] > h[x]) rotate(x, d, l, r);
	}
	void Insert(int v) {
		c[++pT] = v; h[pT] = rand() * rand(); Insert(rt, 1, 1LL << 61);
	}
}
using SufT::Insert; using SufT::rk;
int mv[V << 2], p[V << 2];
void pushUp(int o) {
	int l = o << 1, r = o << 1 | 1;
	mv[o] = rk[p[mv[l]]] <= rk[p[mv[r]]] ? mv[l] : mv[r];
}
void build(int o, int l, int r) {
	if (l == r) {
		Read(p[l]); mv[o] = l; return;
	}
	int Mid = (l + r) >> 1;
	build(o << 1, l, Mid); build(o << 1 | 1, Mid + 1, r); pushUp(o);
}
void modify(int o, int l, int r, int d, int v) {
	if (l == r) {
		p[l] = v; return;
	}
	int Mid = (l + r) >> 1;
	if (d <= Mid) modify(o << 1, l, Mid, d, v);
	else modify(o << 1 | 1, Mid + 1, r, d, v);
	pushUp(o);
}
int Query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return mv[o];
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	int v1 = Query(o << 1, l, Mid, L, Mid), v2 = Query(o << 1 | 1, Mid + 1, r, Mid + 1, R);
	return rk[p[v1]] <= rk[p[v2]] ? v1 : v2;
}
char s[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Read(len); Read(type);
	Read(s + 1, len);
	for (int i = len; i; i--) Insert(s[i] - 'a');
	build(1, 1, n);
	char op; int x, y;
	while (m--) {
		Read(op); if (!type) lstAns = 0;
		switch (op) {
		case 'I': Read(x); Insert(x ^ lstAns); break;
		case 'C': Read(x); Read(y); modify(1, 1, n, x, y); break;
		default: Read(x); Read(y); printf("%d\n", lstAns = Query(1, 1, n, x, y));
		}
	}
	return 0;
}
