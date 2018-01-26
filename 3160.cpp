#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
typedef complex<DB> E;
const int V = 400010;
const DB pi = acos(-1);
const int P = 1000000007;
void get(char *s, int &len) {
	len = fread(s, 1, V, stdin);
}
namespace FFT {
	int L, n, R[V];
	void Init(int m) {
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
		if (f == -1) for (int i = 0; i < n; i++) a[i] /= n;
	}
}
int Manacher(char *str, int len) {
	static char s[V << 1];
	static int f[V << 1];
	int i, j, r = 0;
	for (s[0] = '$', s[1] = '#', i = 1; i <= len; i++) {
		s[i << 1] = str[i]; s[i << 1 | 1] = '#';
	}
	len = len << 1 | 1;
	int mx = 1, pos = 1;
	for (i = 1; i <= len; i++) {
		f[i] = min(f[pos * 2 - i], mx - i);
		while (s[i + f[i]] == s[i - f[i]]) f[i]++;
		if (f[i] + i > mx) {
			mx = f[i] + i; pos = i;
		}
		r = (r + (f[i] >> 1) % P) % P;
	}
	return r;
}
char s[V]; 
int len, bin[V];
E g[V], r[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	scanf("%s", s + 1); len = strlen(s + 1);
	//get(s + 1, len);
	bin[0] = 1; for (int i = 1; i < V; i++) bin[i] = (LL)bin[i - 1] * 2 % P;
	FFT::Init(len);
	for (i = 1; i <= len; i++) {
		g[i] = (s[i] == 'a'); r[i] = (s[i] == 'b');
	}
	FFT::fft(g, 1); FFT::fft(r, 1);
	for (i = 0; i < FFT::n; i++) {
		g[i] *= g[i]; r[i] *= r[i];
	}
	FFT::fft(g, -1); FFT::fft(r, -1);
	int Ans = 0;
	for (i = 1; i < FFT::n; i++) {
		int x = ((int)(g[i].real() + 0.5) + (int)(r[i].real() + 0.5) + 1) >> 1;
		(Ans += bin[x] - 1) %= P;
	}
	Ans = (Ans + (LL)(P - Manacher(s, len)) % P) % P;
	cout << Ans << endl;
	return 0;
}
