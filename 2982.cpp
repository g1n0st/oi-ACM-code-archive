#include <bits/stdc++.h>
typedef long long LL;
const int P = 10007;
using namespace std;
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = r * x % P;
		y >>= 1; if (y) x = x * x % P;
	}
	return r;
}
int inv[P], fac[P];
void Pre(int n) {
	fac[0] = 1; for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % P;
	inv[n] = Ksm(fac[n], P - 2); for (int i = n - 1; ~i; i--) inv[i] = inv[i + 1] * (i + 1) % P;
}
int C(int n, int m) {
	if (m > n) return 0;
	if (n < P && m < P) return fac[n] * inv[n - m] % P * inv[m] % P;
	return C(n % P, m % P) * C(n / P, m / P) % P;
}
int T, N, M;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Pre(P - 1);
	cin >> T;
	while (T--) {
		cin >> N >> M;
		cout << C(N, M) << endl;
	}
	return 0;
}
