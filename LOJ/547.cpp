#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1010000;
const int P = 65537;
int K; LL n;
namespace S1 {
	int m[V];
	void mul(int *a, int *b) {
		static int r[V];
		for (int i = 0; i <= K + K; i++) r[i] = 0;
		for (int i = 0; i < K; i++)
			for (int j = 0; j < K; j++)
				r[i + j] = (r[i + j] + (LL)a[i] * b[j]) % P;
		for (int i = 2 * (K - 1); i >= K; i--)
			for (int j = 1; j <= K; j++)
				r[i - j] = (r[i - j] + (LL)r[i] * m[K - j]) % P;
		for (int i = 0; i < K; i++) a[i] = r[i];
	}
	int a[V], b[V], s[V];
	void main() {
		K++; n++;
		a[K - 1] = 2; a[0] = 65536; s[0] = s[1] = 1;
		for (int i = 2; i <= 2 * K - 2; i++) {
			s[i] = s[i - 1] * 2 % P;
			if (i - K >= 0) s[i] = (s[i] + P - s[i - K]) % P;
		}
		if (n <= 2 * K - 2) return printf("%d\n", s[n]), (void)0;
		for (int i = 0; i < K; i++) m[i] = a[i];
		b[1] = 1;
		for (LL i = n - 2 * K + 1; i; i >>= 1, mul(b, b))
			if (i & 1) mul(a, b);
		int ans = 0;
		for (int i = K - 1; i < K + K - 1; i++)
			ans = (ans + (LL)s[i] * a[i - K + 1]) % P;
		cout << ans << endl;
	}
}
namespace S2 {
	int Ksm(int x, LL y = P - 2, int p = P) {
		int r = 1;
		while (y) {
			if (y & 1) r = (LL)r * x % p;
			y >>= 1; if (y) x = (LL)x * x % p;
		}
		return r;
	}
	int fac[V], inv[V];
	void Pre(int n) {
		fac[0] = 1; for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % P;
		inv[n] = Ksm(n); for (int i = n - 1; ~i; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % P;
	}
	int C(LL n, LL m) {
		if (m > n) return 0;
		if (n < P && m < P) return (LL)fac[n] * inv[m] * inv[n - m] % P;
		return (LL)C(n % P, m % P) * C(n / P, m / P) % P;
	}
	int calc(LL n) {
		LL lim = n / (K + 1), r = 0, w, base = Ksm(2, n % (P - 1)), inv2 = Ksm(inv[2], K + 1);
		for (LL i = 0; i <= lim; i++) {
			w = base * C(n - i * K, i) % P; base = base * inv2 % P;
			if (i & 1) r = (r + P - w) % P;
			else r = (r + w) % P;
		}
		return r;
	}
	void main() {
		Pre(P - 1);
		printf("%d\n", (calc(n + 1) - calc(n) + P) % P);
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> n >> K;
	if (K <= 2500) S1::main();
	else S2::main();
	return 0;
}
