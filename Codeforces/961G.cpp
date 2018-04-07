#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 200010;
const int P = 1000000007;
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
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
int fac[V], inv[V];
void Pre(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % P;
	inv[n] = Ksm(fac[n], P - 2);
	for (int i = n - 1; ~i; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % P;
}
int C(int x, int y) {
	return (LL)fac[x] * inv[y] % P * inv[x - y] % P;
}
int F(int n, int k) {
	int r = 0;
	for (int j = 0; j <= k; j++)
		if ((k + j) & 1) r = (r - (LL)C(k, j) * Ksm(j, n)) % P;
		else r = (r + (LL)C(k, j) * Ksm(j, n)) % P;
	r = (r + P) % P;
	r = (LL)r * inv[k] % P;
	return r;
}
int n, K, a[V], sum;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K); Pre(n);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); sum = (sum + a[i]) % P;
	}
	int a1 = (F(n, K) + (LL)(n - 1) * F(n - 1, K)) % P;
	a1 = (LL)a1 * sum % P;
	cout << a1 << endl;
	return 0;
}
