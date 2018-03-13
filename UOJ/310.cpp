#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 2048577;
const int P = 998244353;
const int INV2 = (P + 1) / 2;

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
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
void fwt(int *a, int n, int f) {
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += (i << 1))
			for (int k = 0; k < i; k++) {
				int x = a[j + k], y = a[i + j + k];
				a[j + k] = x + y; a[i + j + k] = x - y;
				if (f == -1) a[j + k] = (LL)a[j + k] * INV2 % P, a[i + j + k] = (LL)a[i + j + k] * INV2 % P;
			}
}
int n, M, mx, a[V], f[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); mx = max(mx, a[i]);
	}
	for (M = 1; M <= mx; M <<= 1);
	for (int i = 1; i <= n; i++) {
		f[0]++; f[a[i]] += 2;
	}
	fwt(f, M, 1);
	for (int i = 0; i < M; i++) {
		int x = (f[i] + n) / 4;
		f[i] = Ksm(3, x); if ((n - x) & 1) f[i] = P - f[i];
	}
	fwt(f, M, -1);
	int ans = f[0] - 1; if (ans < 0) ans += P;
	printf("%d\n", ans);
	return 0;
}
