#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(LL &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
LL n, m, M, Q;
struct Dat {
	LL v, l;
	Dat(LL v = 0, LL l = 0) : v(v), l(l) {}
	friend bool operator < (const Dat &a, const Dat &b) {
		return a.v < b.v;
	}
	friend Dat operator + (const Dat &a, const Dat &b) {
		Dat r(a.v + b.v, a.l | b.l);
		for (int i = M; ~i; i--) if (a.l & b.l &(1 << i)) {
			r.l |= ((1 << i + 1) - 1); break;
		}
		return r;
	}
} a[V], s[V << 2], t[V << 2], t1[V << 2], tmp;
int s_, t_, t1_;
LL Qur(LL x) {
	for (int i = 1; i <= s_; i++)
		if (s[i].l >= x) return s[i].v;
	return -1;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	LL v, l;
	for (int i = 1; i <= n; i++) {
		Read(v); Read(l); a[i] = Dat(v, l);
	}
	for (M = 31; M && (1 << M - 1) > m; M--);
	s[++s_] = Dat(0, 0);
	for (int i = 1; i <= n; i++) {
		t_ = s_; for (int k = 1; k <= t_; k++) t[k] = s[k] + a[i];
		t1_ = 0; int j = 0, k = 0, l;
		while (j < s_ || k < t_) {
			tmp = j >= s_ ? t[++k] : (k >= t_ ? s[++j] : (s[j + 1] < t[k + 1] ? s[++j] : t[++k]));
			for (l = 1; l <= t1_; l++)
				if (t1[l].l >= tmp.l) break;
			if (l == t1_ + 1) t1[++t1_] = tmp;
		}
		s_ = t1_;
		for (int i = 1; i <= s_; i++) s[i] = t1[i];
	}
	Read(Q); LL x;
	while (Q--) {
		Read(x); printf("%lld\n", Qur(x));
	}
	return 0;
}
