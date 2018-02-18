#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
const int P = 19961993;
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
int Ksm(int x, int y = P - 2, int p = P) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
int pri[V], vis[V], tot, inv[V];
void Pre(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) pri[++tot] = i;
		for (int j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[i * pri[j]] = 1; if (!(i % pri[j])) break;
		}
	}
	for (int i = 1; i <= 60; i++) inv[i] = Ksm(pri[i]);
}
struct Node {
	int val; LL ext;
	Node(int val = 0, LL ext = 0) : val(val), ext(ext) {}
	friend Node operator + (Node a, Node b) {
		Node r;
		r.val = (LL)a.val * b.val % P;
		r.ext = a.ext | b.ext;
		return r;
	}
} v[V << 2];
void pushUp(int o) {
	v[o] = v[o << 1] + v[o << 1 | 1];
}
void build(int o, int l, int r) {
	if (l == r) {
		v[o] = Node(3, (LL)4); return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	pushUp(o);
}
void modify(int o, int l, int r, int p, int v1, LL v2) {
	if (l == r) {
		v[o] = Node(v1, v2); return;
	}
	int mid = (l + r) >> 1;
	p <= mid ? modify(o << 1, l, mid, p, v1, v2) : modify(o << 1 | 1, mid + 1, r, p, v1, v2);
	pushUp(o);
}
Node query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return v[o];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(o << 1, l, mid, L, R);
	if (mid < L) return query(o << 1 | 1, mid + 1, r, L, R);
	return query(o << 1, l, mid, L, mid) + query(o << 1 | 1, mid + 1, r, mid + 1, R);
}
int n, m;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Pre(281); Read(n); build(1, 1, m = 100000);
	int a, b, c;
	while (n--) {
		Read(a); Read(b); Read(c);
		if (a & 1) {
			LL ext = 0; int val = c;
			for (int i = 1; i <= tot && pri[i] <= c; i++)
				if (!(c % pri[i])) {
					ext |= (1LL << i); while (!(c % pri[i])) c /= pri[i];
				}
			modify(1, 1, m, b, val, ext);
		}
		else {
			Node r = query(1, 1, m, b, c);
			int val = r.val;
			for (int i = 1; i <= 60; i++)
				if ((r.ext >> i) & 1) {
					val = (LL)val * inv[i] % P;
					val = (LL)val * (pri[i] - 1) % P;
				}
			printf("%d\n", val);
		}
	}
	return 0;
}
