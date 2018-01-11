#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 500;
const LL P = 1234567891;
void Read(LL &x) {
	scanf("%lld", &x);
}
void Add(LL &x, LL y) {
	y = (y % P + P) % P;
	(x += y) %= P;
}
void Mul(LL &x, LL y) {
	y = (y % P + P) % P;
	(x *= y) %= P;
}
LL Ksm(LL x, int y) {
	LL r = 1;
	while (y) {
		if (y & 1) Mul(r, x);
		y >>= 1;
		if (y) Mul(x, x);
	}
	return r;
}
LL fac[V], inv[V];
void Init(int n) {
	fac[0] = 1; inv[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % P;
	inv[n] = Ksm(fac[n], P - 2);
	for (int i = n - 1; i; i--) inv[i] = inv[i + 1] * (i + 1) % P;
}
LL v(int k, int i) {
	if ((k - i) & 1) return -1;
	return 1;
}
LL Lagrange(LL g[], LL n, LL r) {
	static LL pre[V], suf[V];
	pre[0] = 1; suf[0] = 1;
	for (int i = 1; i <= n; i++) {
		pre[i] = pre[i - 1]; Mul(pre[i], r - i);
	}
	for (int i = 1; i <= n; i++) {
		suf[i] = suf[i - 1]; Mul(suf[i], r - n + i - 1);
	}
	LL re = 0;
	for (int i = 1; i <= n; i++) {
		LL u = pre[i - 1] * suf[n - i] % P * g[i] % P;
		LL d = inv[i - 1] * inv[n - i] % P;
		Add(re, u * d * v(n, i) % P);
	}
	return re;
}
LL T;
LL K, A, N, D, g[V], f[V];
void Solve() {
	Read(K); Read(A); Read(N); Read(D);
	for (int i = 1; i <= K + 3; i++) g[i] = Ksm(i, K);
	for (int i = 1; i <= K + 3; i++) Add(g[i], g[i - 1]);
	for (int i = 1; i <= K + 3; i++) Add(g[i], g[i - 1]);
	f[0] = Lagrange(g, K + 3, A);
	for (int i = 1; i <= K + 5; i++) {
		f[i] = f[i - 1];
		Add(f[i], Lagrange(g, K + 3, (A + i * D % P) % P));
	}
	LL Ans = Lagrange(f, K + 5, N);
	cout << Ans << endl;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Init(300);
	Read(T);
	while (T--) Solve();
	return 0;
}
