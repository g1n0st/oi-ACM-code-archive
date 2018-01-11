#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 110;
const LL P = 1000000007;
void Read(LL &x) {
	scanf("%lld", &x);
}
void Add(LL &x, LL y) {
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
LL N, M, K, U[V], R[V];
LL Lagrange(LL u, LL r) {
	static LL g[V], inv[V];
	for (int x = 1; x <= N + 1; x++) {
		g[x] = 0;
		for (int i = 1; i <= x; i++)
			Add(g[x], Ksm(x - i, r - 1) * Ksm(i, N - r) % P);
		if (u == x) return g[x];
	}
	for (int x = 1; x <= N + 1; x++) {
		inv[x] = 1;
		for (int i = 1; i <= N + 1; i++)
			if (x ^ i) Mul(inv[x], (x - i));
		inv[x] = Ksm(inv[x], P - 2);
	}
	LL re = 0;
	for (int x = 1; x <= N + 1; x++) {
		LL t = g[x] * inv[x] % P;
		for (int i = 1; i <= N + 1; i++)
			if (x ^ i) Mul(t, (u - i));
		Add(re, t);
	}
	return re;
}
LL C[V][V], f[V][V];
void Init(int n) {
	memset(C, 0, sizeof C);
	C[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) 
			Add(C[i][j], C[i - 1][j] + C[i - 1][j - 1]);
	}
}
LL Cc(int i, int j) {
	if (i < 0 || j < 0 || j > i) return 0;
	return C[i][j];
}
int main() {
	Read(N); Read(M); Read(K);
	for (int i = 1; i <= M; i++) Read(U[i]);
	for (int i = 1; i <= M; i++) Read(R[i]);
	Init(N);
	f[0][0] = 1;
	Lagrange(U[1], R[1]);
	for (int i = 1; i <= M; i++) {
		LL c = Lagrange(U[i], R[i]);
		for (int j = 0; j <= N; j++) {
			for (int w = 0; w <= j; w++)
				Add(f[i][j], c * f[i - 1][w] % P * Cc(N - 1 - w, j - w) % P * Cc(w, R[i] - 1 - (j - w)) % P);
		}
	}
	cout << f[M][N - 1 - K] << endl;
	return 0;
}
