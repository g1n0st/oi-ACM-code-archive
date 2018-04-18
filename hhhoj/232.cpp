#include <cstdio>
#include <iostream>

namespace __g1n0st_workspace__ {
	
	typedef long long LL;

	const int V = 2000010;
	const int P = 998244353;
	
	inline int Ksm(int x, int y) {
		int r = 1;
		while (y) {
			if (y & 1) r = (LL)r * x % P;
			y >>= 1; if (y) x = (LL)x * x % P;
		}
		return r;
	}
	int n;
	int fac[V], inv[V];
	void Pre(int n) {
		fac[0] = 1;
		for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % P;
		inv[n] = Ksm(fac[n], P - 2);
		for (int i = n - 1; ~i; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % P;
	}

	int pri[V], tot, phi[V];
	void Euler(int n) {
		int i, j;
		phi[1] = 1;
		for (i = 2; i <= n; i++) {
			if (!phi[i]) {
				phi[i] = i - 1; pri[++tot] = i;
			}
			for (j = 1; j <= tot && i * pri[j] <= n; j++) {
				if (i % pri[j])
					phi[i * pri[j]] = phi[i] * (pri[j] - 1);
				else {
					phi[i * pri[j]] = phi[i] * pri[j];
					break;
				}
			}
		}
	}
	inline int C(int n, int k) {
		return (LL)fac[n] * inv[k] % P * inv[n - k] % P;
	}
	void __main__() {
		
		std::cin >> n;

		Pre(n << 1); Euler(n << 1);

		int ans = 0;

		for (int d = 1; d <= n; d++)
			if (n % d == 0) {
				ans = (ans + (LL)phi[n / d] * C(2 * d, d) % P) % P;
			}
		
		ans = (LL)ans * Ksm(2 * n, P - 2) % P;

		std::cout << ans << std::endl;
	}
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	__g1n0st_workspace__::__main__();

	return 0;
}
