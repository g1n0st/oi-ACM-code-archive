#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 50000;
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
int pri[V], tot, vis[V];
void Pre(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) pri[++tot] = i;
		for (int j = 1; j <= tot && i * pri[j] <= n; j++) {
			vis[i * pri[j]] = 1;
			if (!(i % pri[j])) break;
		}
	}
}
int Phi(int x) {
	int r = x;
	for (int i = 1; i <= tot && pri[i] * pri[i] <= x; i++) 
		if (x % pri[i] == 0) {
			r = r - r / pri[i]; while (x % pri[i] == 0) x /= pri[i];
	}
	if (x > 1) r = r - r / x;
	return r;
}
int Ksm(int x, int y, int p, int &f) {
	f = 0; int r = 1, b = 0;
	while (y) {
		if (y & 1) {
			f |= b | ((LL)r * x >= p); r = (LL)r * x % p;
		}
		y >>= 1; b |= ((LL)x * x >= p); x = (LL)x * x % p;
	}
	return r;
}
int n, m, p, c, K, a[V], t[V];
int opt[V << 2], val[V << 2];
void pushUp(int o) {
	val[o] = (val[o << 1] + val[o << 1 | 1]) % p;
	opt[o] = min(opt[o << 1], opt[o << 1 | 1]);
}
void build(int o, int l, int r) {
	if (l == r) {
		opt[o] = 0; Read(a[l]); val[o] = a[l] % p;
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	pushUp(o);
}
int calc(int d, int x) {
	int r = x; 
	if (x >= t[d]) r = r % t[d] + t[d];
	while (d) {
		--d;
		int flg = 0; r = Ksm(c, r, t[d], flg);
		if (flg) r += t[d];
	}
	return r % t[0];
}
void modify(int o, int l, int r, int L, int R) {
	if (opt[o] >= K) return;
	if (l == r) {
		val[o] = calc(++opt[o], a[l]); return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid) modify(o << 1, l, mid, L, R);
	if (mid < R) modify(o << 1 | 1, mid + 1, r, L, R);
	pushUp(o);
}
int query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return val[o];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(o << 1, l, mid, L, R);
	if (mid < L) return	query(o << 1 | 1, mid + 1, r, L, R);
	return (query(o << 1, l, mid, L, mid) + query(o << 1 | 1, mid + 1, r, mid + 1, R)) % p;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Read(p); Read(c); Pre(V - 1);
	int tmp = p; t[0] = tmp;
	while (tmp ^ 1) {
		tmp = Phi(tmp); t[++K] = tmp;
	} t[++K] = 1;
	build(1, 1, n);
	int op, l, r;
	while (m--) {
		Read(op); Read(l); Read(r);
		if (op & 1) printf("%d\n", query(1, 1, n, l, r));
		else modify(1, 1, n, l, r);
	}
	return 0;
}
