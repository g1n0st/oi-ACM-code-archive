#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef complex<db> E;
const db pi = acos(-1);
const int V = 530100;
const int N = 10;
const int LIM = 400000;
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
int T, X, Y;
namespace S1 {
	namespace FFT {
		int n, L, R[V];
		void init(int m) {
			for (n = 1, L = 0; n < m; n <<= 1, L++);
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
			if (f == -1) for (int i = 0; i < n; i++) a[i] /= n;
		}
	}
	E a[V], b[V];
	db f[V];
	void Solve() {
		FFT::init(X * Y);
		for (int i = 0; i < FFT::n; i++) a[i] = b[i] = 0;
		a[0] = 1;
		for (int i = 0; i < X; i++) b[i] = 1.0 / X;
		FFT::fft(a, 1); FFT::fft(b, 1);
		while (Y) {
			if (Y & 1)
				for (int i = 0; i < FFT::n; i++) a[i] = a[i] * b[i];
			Y >>= 1; for (int i = 0; i < FFT::n; i++) b[i] = b[i] * b[i];
		}
		FFT::fft(a, -1);
		for (int i = 0; i < FFT::n; i++) f[i] = a[i].real();
		for (int i = 1; i < FFT::n; i++) f[i] += f[i - 1];
		int A, B;
		for (int i = 1; i <= N; i++) {
			Read(A); Read(B); printf("%.8lf\n", f[B] - (A ? f[A - 1] : 0));
		}
	}
}
namespace S2 {
	const db di = 1.0 / sqrt(2 * acos(-1));
	const db eps = 1e-10;
	const db EPSC = 15.0;
	bool dcmp(db x) {
		return fabs(x) <= eps;
	}
	db f(db x) {
		return di * exp(-x * x / 2.0);
	}
	db simpson(db a, db b, db fa, db fab, db fb) {
		return (b - a) * (fa + 4.0 * fab + fb) / 6.0;
	}
	db sol(db l, db r) {
		db mid = (l + r) / 2.0, lm = (l + mid) / 2.0, rm = (mid + r) / 2.0;
		db fl = f(l), fr = f(r), fmid = f(mid), flm = f(lm), frm = f(rm);
		db s = simpson(l, r, fl, fmid, fr),
			sl = simpson(l, mid, fl, flm, fmid),
			sr = simpson(mid, r, fmid, frm, fr);
		if (dcmp(s - sl - sr))
			return sl + sr + (sl + sr - s) / EPSC;
		return sol(l, mid) + sol(mid, r);
	}
	void Solve() {
		db u1 = (X - 1) / 2.0;
		db u2 = sqrt(((db)X * X - 1) / 12.0);
		int A, B;
		for (int i = 1; i <= N; i++) {
			Read(A); Read(B);
			db a = ((db)(A - 0.5) / Y - u1) * sqrt(Y) / u2;
			db b = ((db)(B + 0.5) / Y - u1) * sqrt(Y) / u2;
			printf("%.8lf\n", sol(0, b) - sol(0, a));
		}
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T);
	while (T--) {
		Read(X); Read(Y);
		if (X * Y <= LIM)
			S1::Solve();
		else
			S2::Solve();
	}
	return 0;
}
