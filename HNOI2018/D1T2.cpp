#include <bits/stdc++.h>
using namespace std;

const int V = 200010;
const int oo = 0x7fffffff;

inline char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
inline void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}

char pbuf[V], *pp = pbuf;
inline void push(const char c) {
	if (pp == pbuf + V) fwrite(pbuf, 1, V, stdout), pp = pbuf;
	*pp++ = c;
}
inline void Write(int x) {
	static char sta[20];
	int top = 0;
	if (!x) push('0');
	while (x) sta[++top] = x % 10 ^ '0', x /= 10;
	while (top) push(sta[top--]);
	push('\n');
}
inline void flush() {
	fwrite(pbuf, 1, pp - pbuf, stdout);
}

int n, n2, Q, type, a[V], lstAns;
int mx[V << 2], tr[V << 2];
int L[V << 2], R[V << 2], pos[V], fa[V << 2], ls[V << 2], rs[V << 2];

inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}
int query(int o, int l, int r, int rm) {
	if (l == r) {
		if (l > n) return oo;
		if (rm == -oo) return mx[o] + l;
		return (mx[o] > rm) ? min(l + mx[o], l + 1 + rm) : l + rm;
	}
	int mid = (l + r) >> 1;
	if (mx[o << 1 | 1] <= rm) return query(o << 1, l, mid, rm);
	else return min(tr[o], query(o << 1 | 1, mid + 1, r, rm));
}
int query(int o, int rm) {
	int res = oo, mid;
	while (L[o] < R[o]) {
		if (mx[ls[o]] <= rm) o = ls[o];
		else {
			res = min(res, tr[o]); o = rs[o];
		}
	}
	if (rm == -oo) res = min(res, mx[o] + L[o]);
	else res = min(res, (mx[o] > rm) ? min(L[o] + mx[o], L[o] + 1 + rm) : L[o] + rm);
	return res;
}
void build(int o, int l, int r) {
	L[o] = l; R[o] = r; if (l == r) {
		pos[l] = o; mx[o] = a[l]; return;
	}
	int mid = (l + r) >> 1;
	fa[ls[o] = o << 1] = fa[rs[o] = o << 1 | 1] = o;
	build(ls[o], l, mid); build(rs[o], mid + 1, r);
	mx[o] = max(mx[ls[o]], mx[rs[o]]);
	tr[o] = query(ls[o], L[ls[o]], R[ls[o]], mx[rs[o]]);
}
void modify(int l) {
	int o = pos[l]; mx[o] = a[l];
	while (fa[o]) {
		o = fa[o];
		mx[o] = max(mx[ls[o]], mx[rs[o]]);
		tr[o] = query(ls[o], L[ls[o]], R[ls[o]], mx[rs[o]]);
	}
}
int main() {

	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	Read(n); Read(Q); Read(type);

	n2 = n << 1;
	int x, y;

	for (int i = 1; i <= n; i++) {
		Read(a[i]); a[i + n] = a[i];
	}
	for (int i = 1; i <= n2; i++) a[i] -= i;
	
	build(1, 1, n2);

	Write(lstAns = query(1, 1, n2, -oo) + n - 1);
	while (Q--) {
		Read(x); Read(y); x ^= (lstAns * type); y ^= (lstAns * type);
		a[x] = y - x; a[x + n] = y - x - n;
		modify(x); modify(x + n);
		Write(lstAns = query(1, 1, n2, -oo) + n - 1);
	}
	flush();
	return 0;
}
