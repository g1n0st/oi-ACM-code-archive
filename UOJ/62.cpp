#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
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
int Ksm(int x, int y = P - 2) {
	if (y < 0) y += P - 1;
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
int n, c, d, Q;
int b[V], f_z[V], f_r[V], hx[V];
int Solve() {
	for (int i = 1; i <= n; i++) Read(b[i]);
	for (int i = 1; i <= n; i++) f_r[i] = Ksm(i, c - d);
	for (int i = 1; i <= n; i++)
		for (int j = i + i; j <= n; j += i) f_r[j] = (f_r[j] + P - f_r[i]) % P;
	for (int i = 1; i <= n; i++) f_z[i] = (LL)b[i] * Ksm(i, -d) % P;
	for (int i = 1; i <= n; i++)
		for (int j = i + i; j <= n; j += i) f_z[j] = (f_z[j] + P - f_z[i]) % P;
	for (int i = 1; i <= n; i++) {
		if (!f_r[i]) {
			if (f_z[i]) return 0; else hx[i] = 0;
		}
		else
			hx[i] = (LL)f_z[i] * Ksm(f_r[i]) % P;
	}
	for (int i = n; i; i--)
		for (int j = i + i; j <= n; j += i)
			hx[i] = (hx[i] + P - hx[j]) % P;
	for (int i = 1; i <= n; i++) hx[i] = (LL)hx[i] * Ksm(i, -d) % P;
	for (int i = 1; i <= n; i++) printf("%d ", hx[i]); putchar('\n');
	return 1;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(c); Read(d); Read(Q);
	c %= (P - 1); d %= (P - 1);
	while (Q--) if (!Solve()) puts("-1");
	return 0;
}
