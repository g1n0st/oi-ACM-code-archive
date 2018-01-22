#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 200010;
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
int N, M, B;
int a[V], bel[V], bL[V], bR[V];
namespace FFT {
	int n, L, R[V << 1];
	void Init(int m) {
		for (n = 1; n <= m; n <<= 1, L++); //n <<= 1; L++;
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
void Init() {
	int i, j; //B = min((int)sqrt(N) * 6, N);
	B = min(N, 2000);
	for (i = 1; i <= N; i++) {
		bel[i] = (i - 1) / B + 1;
		if (!bL[bel[i]]) bL[bel[i]] = i; bR[bel[i]] = i;
		Read(a[i]); M = max(M, a[i]);
	}
	FFT::Init(M << 1); B = bel[N];
}
E fa[V], fb[V], fc[V];
int L[V], R[V];
LL Ans;
void Solve() {
	int i, j, k, l, r, t;
	for (i = 1; i <= N; i++) R[a[i]]++;
	for (i = 1; i <= B; i++) {
		l = bL[i]; r = bR[i];
		for (j = l; j <= r; j++) R[a[j]]--;
		for (j = l; j <= r; j++) {
			for (k = j + 1; k <= r; k++) {
				if (t = (a[j] << 1) - a[k], t >= 0)
					Ans += L[t];
				if (t = (a[k] << 1) - a[j], t >= 0)
					Ans += R[t];
			}
			L[a[j]]++;
		}
	}

	for (i = 2; i < B; i++) {

		for (j = 0; j <= M; j++) L[j] = R[j] = 0;
		for (j = 0; j < FFT::n; j++) fa[j] = fb[j] = fc[j] = E(0, 0);

		l = bL[i]; r = bR[i];
		for (j = 1; j < l; j++) L[a[j]]++;
		for (j = r + 1; j <= N; j++) R[a[j]]++;
		for (j = 0; j <= M; j++) fa[j] = L[j];
		for (j = 0; j <= M; j++) fb[j] = R[j];
		FFT::fft(fa, 1); FFT::fft(fb, 1);
		for (j = 0; j <= FFT::n; j++) fc[j] = fa[j] * fb[j];
		FFT::fft(fc, -1);
		for (j = l; j <= r; j++)
			Ans += (LL)(fc[a[j] << 1].x + 0.1);
	}
	printf("%lld\n", Ans);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Init(); Solve();
	return 0;
}
