#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 300010;
const int G = 3;
const int P = 1004535809;
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
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int Ksm(int x, int y = P - 2, int p = P) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % p;
		y >>= 1;
		if (y) x = (LL)x * x % p;
	}
	return r;
}
int getG(int n) {
	static int s[V], t; t = 0;
	for (int i = 2; i < n - 1; i++)
		if ((n - 1) % i == 0) s[++t] = i;
	for (int g = 2, flg;; g++) {
		flg = 1;
		for (int i = 1; i <= t; i++)
			if (Ksm(g, s[i], n) == 1) {
				flg = 0; break;
			}
		if (flg) return g;
	}
}
int N, M, X, Tot, mG, ind[V], a[V], b[V];
namespace NTT {
	int w[2][V], R[V], n, L, g, INV;
	void Init(int m, int g) {
		for (L = 0, n = 1; n < m; n <<= 1, L++); n <<= 1; L++;
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
					int x = a[j + k], y = (LL)a[j + i + k] * w[f][n / (i << 1) * k] % P;
					a[j + k] = (x + y) % P; a[j + i + k] = (x - y + P) % P;
				}
		if (!f) for (int i = 0; i < n; i++) a[i] = (LL)a[i] * INV % P;
	}
}
void Init() {
	int i, j;
	Read(N); Read(M); Read(X); Read(Tot);
	mG = getG(M); NTT::Init(M, mG);
	for (i = 0, j = 1; i < M - 1; i++, j = (LL)j * mG % M)
		ind[j] = i;
	while (Tot--) {
		Read(i); 
		if (i) a[ind[i]] = 1;
	}
	M--;
	for (i = 0; i < M; i++) b[i] = a[i];
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Init();
	for (N--; N; N >>= 1) {
		NTT::ntt(a, 1);
		if (N & 1) {
			NTT::ntt(b, 1);
			for (i = 0; i < NTT::n; i++) b[i] = (LL)b[i] * a[i] % P;
			NTT::ntt(b, 0);
			for (i = M; i < NTT::n; i++) {
				b[i % M] = (b[i % M] + b[i]) % P; b[i] = 0;
			}
		}
		for (i = 0; i < NTT::n; i++) a[i] = (LL)a[i] * a[i] % P;
		NTT::ntt(a, 0);
		for (i = M; i < NTT::n; i++) {
			a[i % M] = (a[i % M] + a[i]) % P; a[i] = 0;
		}
	}
	printf("%d\n", b[ind[X]]);
	return 0;
}
