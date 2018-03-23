#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000100;
const int P = 998244353;
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
void Add(int &x, int y) {
	x += y; while (x < 0) x += P; while (x > P) x -= P;
}
int l[V], r[V], f[V], s[V], a[V], n, t;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) Read(a[i]);
	a[n + 1] = 1 << 30;
	for (int i = 1; i <= n + 1; i++) {
		while (t && a[s[t]] < a[i]) r[s[t--]] = i;
		l[i] = s[t]; s[++t] = i;
	}
	for (int i = 1; i <= n; i++) {
		Add(f[0], a[i]); Add(f[r[i] - i], -a[i]); Add(f[i - l[i]], -a[i]); Add(f[r[i] - l[i]], a[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) Add(f[i], f[i - 1]);
	for (int i = 1; i <= n; i++) Add(f[i], f[i - 1]);
	for (int i = 0; i < n; i++) ans ^= f[i];
	cout << ans << endl;
	return 0;
}
