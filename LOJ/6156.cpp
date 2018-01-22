#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 600010;
const double pi = acos(-1);
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
int Ksm(int x, int y, int p) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % p;
		y >>= 1;
		if (y) x = (LL)x * x % p;
	}
	return r;
}
struct E {
	double x, y;
	E() {}
	E(double x, double y) : x(x), y(y) {}
	E(double x) : x(x), y(0) {}
	friend E operator + (E a, E b) {
		return E(a.x + b.x, a.y + b.y);
	}
	friend E operator - (E a, E b) {
		return E(a.x - b.x, a.y - b.y);
	}
	friend E operator * (E a, E b) {
		return E(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
	}
	friend E operator / (E a, double b) {
		return E(a.x / b, a.y / b);
	}
};
namespace FFT {
	int L, R[V], n;
	void Init(int m) {
		for (n = 1, L = 0; n < m; n <<= 1, L++); n <<= 1; L++;
		for (int i = 0; i < n; i++)
			R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	}
	void fft(E *a, int f) {
		int i, j, k;
		for (i = 0; i < n; i++)
			if (i < R[i]) swap(a[i], a[R[i]]);
		for (i = 1; i < n; i <<= 1) {
			E wn(cos(pi / i), f * sin(pi / i));
			for (j = 0; j < n; j += (i << 1)) {
				E w(1, 0);
				for (k = 0; k < i; k++, w = w * wn) {
					E x = a[j + k], y = w * a[j + k + i];
					a[j + k] = x + y; a[j + k + i] = x - y;
				}
			}
		}
		if (f == -1) for (int i = 0; i < n; i++) a[i] = a[i] / n;
	}
}
int getG(int m) {
	static int s[V], t; t = 0;
	for (int i = 2; i < m - 1; i++)
		if ((m - 1) % i == 0) s[++t] = i;
	for (int g = 2, flg;; g++) {
		flg = 1;
		for (int i = 1; i <= t; i++)
			if (Ksm(g, s[i], m) == 1) {
				flg = 0; break;
			}
		if (flg) return g;
	}
}
int T, N, M, G, ind[V], f[V], n0;
LL Ans[V];
E a[V];
void Solve() {
	int i, j, x;
	Read(N); Read(M); G = getG(M);
	for (i = 0, j = 1; i < M - 1; i++, j = (LL)j * G % M) {
		ind[j] = i;
	}
	for (i = 0; i < FFT::n; i++) a[i] = 0; FFT::Init(M);
	for (i = 1; i <= N; i++) {
		Read(x);
		x %= M;
		if (x) {
			f[(LL)x * x % M]++;
			a[ind[x]] = a[ind[x]] + E(1, 0);
		}
		else n0++;
	}
	FFT::fft(a, 1);
	for (i = 0; i < FFT::n; i++) a[i] = a[i] * a[i];
	FFT::fft(a, -1); M--;
	for (i = M; i < FFT::n; i++) a[i % M] = a[i % M] + a[i], a[i] = 0;
	for (i = 1; i <= M; i++) Ans[i] = ((a[ind[i]].x - f[i]) / 2 + 0.5);
	printf("%lld\n", (LL)N * (N - 1) / 2 - (LL)(N - n0) * (N - n0 - 1) / 2);
	for (i = 1; i <= M; i++) printf("%lld\n", Ans[i]);
	for (i = 0; i <= M; i++) f[i] = 0; n0 = 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Read(T); while (T--) Solve();
	return 0;
}
