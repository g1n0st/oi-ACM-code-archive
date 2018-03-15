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
int n, m, a[V], b[V], sa[V], sb[V], ta, tb;
bool cmp(int *h, int a, int b, int c) {
	return (LL)(h[c] - h[a]) * (b - a) <= (LL)(h[b] - h[a]) * (c - a);
}
void pre_convex(int *h, int r, int *s, int &t) {
	for (int i = 0; i <= r; i++) {
		while (t >= 2 && cmp(h, s[t - 1], s[t], i)) --t;
		s[++t] = i;
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	for (int i = 0; i <= n; i++) Read(a[i]);
	for (int i = 0; i <= m; i++) Read(b[i]);
	pre_convex(a, n, sa, ta); pre_convex(b, m, sb, tb);
	int i = 1, j = 1; LL ans = 0;
	while (i < ta && j < tb) {
		int i1 = sa[i], i2 = sa[i + 1], j1 = sb[j], j2 = sb[j + 1];
		if ((LL)(a[i2] - a[i1]) * (j2 - j1) <= (LL)(b[j2] - b[j1]) * (i2 - i1)) {
			ans += (LL)(i2 - i1) * b[j1]; i++;
		}
		else {
			ans += (LL)(j2 - j1) * a[i1]; j++;
		}
	}
	if (i == ta) ans += (LL)a[n] * (m - sb[j]);
	else ans += (LL)b[m] * (n - sa[i]);
	cout << ans << endl;
	return 0;
}
