#include <bits/stdc++.h>
using namespace std;
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
int tot, val[V * 100], L[V * 100], R[V * 100];
int sum[V << 2], tag[V << 2];
int merge(int x, int y) {
	if (!x || !y) return x + y;
	++tot; L[tot] = x; R[tot] = y; val[tot] = val[x]; return tot;
}
int erase(int &x) {
	int y = x; x = ++tot; L[x] = L[y]; R[x] = R[y];
	if (!L[x]) return x = 0, 1;
	if (erase(L[x])) x = R[x]; else val[x] = val[L[x]];
	return 0;
}
void pushDown(int o, int len) {
	if (!tag[o]) return;
	tag[o << 1] = merge(tag[o], tag[o << 1]);
	tag[o << 1 | 1] = merge(tag[o], tag[o << 1 | 1]);
	sum[o << 1] = val[tag[o]] * (len - (len >> 1));
	sum[o << 1 | 1] = val[tag[o]] * (len >> 1);
	tag[o] = 0;
}
void modi(int o, int l, int r, int L, int R, int v) {
	if (l >= L && r <= R) {
		tag[o] = merge(v, tag[o]); sum[o] = val[v] * (r - l + 1); return;
	}
	int mid = (l + r) >> 1; pushDown(o, r - l + 1);
	if (L <= mid) modi(o << 1, l, mid, L, R, v);
	if (mid < R) modi(o << 1 | 1, mid + 1, r, L, R, v);
	sum[o] = sum[o << 1] + sum[o << 1 | 1];
}
int query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return sum[o];
	int mid = (l + r) >> 1; pushDown(o, r - l + 1);
	if (R <= mid) return query(o << 1, l, mid, L, R);
	if (mid < L) return query(o << 1 | 1, mid + 1, r, L, R);
	return query(o << 1, l, mid, L, mid) + query(o << 1 | 1, mid + 1, r, mid + 1, R);
}
void del(int o, int l, int r, int p) {
	if (l == r) {
		if (!tag[o]) return; erase(tag[o]); sum[o] = val[tag[o]]; return;
	}
	int mid = (l + r) >> 1; pushDown(o, r - l + 1);
	if (p <= mid) del(o << 1, l, mid, p);
	else del(o << 1 | 1, mid + 1, r, p);
	sum[o] = sum[o << 1] + sum[o << 1 | 1];
}
int n, Q, ty, lstAns;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(Q); Read(ty);
	int op, u, v, l, r, x;
	while (Q--) {
		Read(op);
		switch (op) {
		case 1: 
			Read(l); Read(r); 
			l = (l + lstAns * ty) % n + 1; r = (r + lstAns * ty) % n + 1; if (l > r) swap(l, r);
			printf("%d\n", lstAns = query(1, 1, n, l, r)); break;
		case 2:
			Read(l); l = (l + lstAns * ty) % n + 1; del(1, 1, n, l); break;
		default:
			Read(l); Read(r);
			l = (l + lstAns * ty) % n + 1; r = (r + lstAns * ty) % n + 1; if (l > r) swap(l, r);
			Read(x); val[++tot] = x; modi(1, 1, n, l, r, tot);
		}
	}
	return 0;
}
