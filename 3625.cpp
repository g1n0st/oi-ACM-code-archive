#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 400010;
const int P = 998244353;
const int G = 3;
const int INV2 = (P + 1) / 2;
void Read(int &x) {
	scanf("%d", &x);
}
int Ksm(int x, int y = P - 2, int p = P) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % p;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
namespace NTT {
	int n, L, R[V], w[2][V], INV;
	void Init(int m) {
		for (n = 1, L = 0; n < m; n <<= 1, L++); n <<= 1; L++;
		for (int i = 0; i < n; i++)
			R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
		int t = Ksm(G, (P - 1) / n); w[0][0] = w[0][n] = 1;
		for (int i = 1; i < n; i++) w[0][i] = (LL)w[0][i - 1] * t % P;
		for (int i = 0; i <= n; i++) w[1][i] = w[0][n - i];
		INV = Ksm(n);
	}
	void ntt(int *a, int f) {
		for (int i = 0; i < n; i++)
			if (i < R[i]) swap(a[i], a[R[i]]);
		for (int i = 1; i < n; i <<= 1)
			for (int j = 0; j < n; j += (i << 1))
				for (int k = 0; k < i; k++) {
					int x = a[j + k], y = (LL)w[f][n / (i << 1) * k] * a[i + j + k] % P;
					a[j + k] = (x + y) % P; a[i + j + k] = (x - y + P) % P;
				}
		if (f) for (int i = 0; i < n; i++) a[i] = (LL)a[i] * INV % P;
	}
}
int tmp[V];
void GetInv(int *a, int *b, int n) {
	if (n == 1) {
		a[0] = Ksm(b[0]); return;
	}
	GetInv(a, b, n >> 1);
	for (int i = 0; i < n; i++) tmp[i] = b[i];
	for (int i = n; i < (n << 1); i++) tmp[i] = 0;
	NTT::Init(n); NTT::ntt(tmp, 0); NTT::ntt(a, 0);
	for (int i = 0; i < (n << 1); i++)
		a[i] = (LL)a[i] * (2 - (LL)tmp[i] * a[i] % P + P) % P;
	NTT::ntt(a, 1);
	for (int i = n; i < (n << 1); i++) a[i] = 0;
}
int ra[V];
void GetSrt(int *a, int *b, int n) {
	if (n == 1) {
		a[0] = 1; return;
	}
	GetSrt(a, b, n >> 1);
	for (int i = 0; i < n; i++) ra[i] = 0;
	GetInv(ra, a, n);
	for (int i = 0; i < n; i++) tmp[i] = b[i];
	for (int i = n; i < (n << 1); i++) tmp[i] = 0;
	NTT::Init(n); NTT::ntt(a, 0); NTT::ntt(ra, 0); NTT::ntt(tmp, 0);
	for (int i = 0; i < (n << 1); i++) a[i] = (LL)INV2 * (a[i] + (LL)tmp[i] * ra[i] % P) % P;
	NTT::ntt(a, 1);
	for (int i = n; i < (n << 1); i++) a[i] = 0;
}
int N, M, h[V], invh[V], ans[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(M);
	h[0] = 1;
	for (int i = 1, x; i <= N; i++) {
		Read(x); h[x] -= 4; if (h[x] < 0) h[x] += P;
	}
	int L = 1; for (; L <= M; L <<= 1);
	GetSrt(invh, h, L); (++invh[0]) %= P;
	GetInv(ans, invh, L);
	for (int i = 1; i <= M; i++) printf("%d\n", (LL)ans[i] * 2 % P);
	return 0;
}
