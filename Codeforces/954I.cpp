#include <bits/stdc++.h>
using namespace std;
const int N = 262145;
const double pi = acos(-1);
char get() {
	static char buf[N], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, N, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get());
}

struct E {
	double x, y;
	E() {}
	E(double x, double y = 0) : x(x), y(y) {}
	friend E operator + (const E &a, const E &b) {
		return E(a.x + b.x, a.y + b.y);
	}
	friend E operator - (const E &a, const E &b) {
		return E(a.x - b.x, a.y - b.y);
	}
	friend E operator * (const E &a, const E &b) {
		return E(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
	}
	void operator /= (double f) {
		x /= f; y /= f;
	}
} a[N] ,b[N];
namespace FFT {
	int L, n, R[N];
	void init(int m) {
		for (n = 1; n <= m; n <<= 1, L++);
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
				for (int k = 0; k < i; k++, w = w * wn) {
					E x = a[j + k], y = w * a[i + j + k];
					a[j + k] = x + y; a[i + j + k] = x - y;
				}
			}
		}
		if (f == -1) for (int i = 0; i < n; i++) a[i] /= n;
	}
}

char s[N], t[N];
int n, m, f[N][6][6];

int Ans, fa[6];
void init() {
	for (int i = 0; i < 6; i++) fa[i] = i;
}
int getf(int x) {
	return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
void merge(int x, int y) {
	x = getf(x); y = getf(y);
	if (x == y) return;
	Ans++; fa[x] = y;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	Read(s, n); Read(t, m);
	FFT::init(n + m);
	for (int u = 0; u < 6; u++)
		for (int v = 0; v < 6; v++) {
			for (int i = 0; i < n; i++) a[i] = ((s[i] - 'a') == u);
			for (int i = n; i < FFT::n; i++) a[i] = 0;
			for (int i = 0; i < m; i++) b[m - 1 - i] = ((t[i] - 'a') == v);
			for (int i = m; i < FFT::n; i++) b[i] = 0;
			FFT::fft(a, 1); FFT::fft(b, 1);
			for (int i = 0; i < FFT::n; i++) a[i] = a[i] * b[i];
			FFT::fft(a, -1);
			for (int i = m - 1; i < n; i++) f[i][u][v] = (a[i].x > 0.5 ? 1 : 0);
		}
	for (int i = m - 1; i < n; i++) {
		init(); Ans = 0;
		for (int u = 0; u < 6; u++)
			for (int v = 0; v < 6; v++)
				if (f[i][u][v]) merge(u, v);
		printf("%d ", Ans);
	}
	return 0;
}
