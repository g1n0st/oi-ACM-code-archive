#include <bits/stdc++.h>
using namespace std;
typedef complex<double> E;
typedef long long LL;
const int V = 500010;
const double pi = acos(-1);
void Read(int &x) {
	scanf("%d", &x);
}
int n, m, p, o, s, u;
void Mo(E &x) {
	x = (LL)(x.real() + 0.1) % p;
}
namespace FFT{
	int L, n, R[V];
	void init(int m) {
		for (L = 0, n = 1; n <= m; n <<= 1, L++); n <<= 1; L++;
		for (int i = 0; i < n; i++)
			R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	}
	void fft(E *a, int f) {
		for (int i = 0; i < n; i++)
			if (i < R[i]) swap(a[i], a[R[i]]);
		for (int i = 1; i < n; i <<= 1) {
			E wn(cos(pi / i), f * sin(pi / i));
			for (int j = 0; j < n; j += (i << 1)) {
				E w(1, 0);
				for (int k = 0; k < i; k++, w *= wn) {
					E x = a[j + k], y = w * a[i + j + k];
					a[j + k] = x + y; a[i + j + k] = x - y;
				}
			}
		}
		if (f == -1) for (int i = 0; i < n; i++) Mo(a[i] /= n);
	}
}
E tmp[V], c[V], f[V], g[V];
void Solve(E *f, E *g, int n) {
	if (!n) {
		g[0] = 1; return;
	}
	if (n & 1) {
		Solve(f, g, n - 1);
		FFT::fft(g, 1);
		for (int i = 0; i < FFT::n; i++) g[i] *= c[i];
		FFT::fft(g, -1);
		for (int i = 0; i <= m; i++) Mo(f[i] += g[i]);
	}
	else {
		Solve(f, g, n >> 1);
		for (int i = 0; i < FFT::n; i++) tmp[i] = f[i];
		FFT::fft(tmp, 1); FFT::fft(g, 1);
		for (int i = 0; i < FFT::n; i++) tmp[i] *= g[i];
		for (int i = 0; i < FFT::n; i++) g[i] *= g[i];
		FFT::fft(tmp, -1); FFT::fft(g, -1);
		for (int i = 0; i <= m; i++) Mo(f[i] += tmp[i]);
	}
	for (int i = m + 1; i < FFT::n; i++) g[i] = 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> m >> p >> n >> o >> s >> u;
	FFT::init(m);
	for (int i = 1; i <= m; i++) c[i] = (o * i * i + s * i + u) % p;
	FFT::fft(c, 1);
	Solve(f, g, n);
	cout << int(f[m].real() + 0.1) << endl;
	return 0;
}
