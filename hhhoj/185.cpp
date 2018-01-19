#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 593119681;
const int V = 262144 + 10;
const int INV2 = (P + 1) >> 1;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0', c = get();
	}
}
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = 1ll * r * x % P;
		y >>= 1;
		if (y) x = 1ll * x * x % P;
	}
	return r;
}
int n, t, a[V], b[V], bt[V], c[V];
int S;
void FWT(int *a, int n) {
	for (int d = 1; d < n; d <<= 1)
		for (int m = d << 1, i = 0; i < n; i += m)
			for (int j = 0; j < d; j++) {
				int x = a[i + j], y = a[i + j + d];
				a[i + j] = (x + y) % P, a[i + j + d] = (x - y + P) % P;
			}
}
void UFWT(int *a, int n) {
	for (int d = 1; d < n; d <<= 1)
		for (int m = d << 1, i = 0; i < n; i += m)
			for (int j = 0; j<d; j++) {
				int x = a[i + j], y = a[i + j + d];
				a[i + j] = (LL)(x + y)* INV2 % P, a[i + j + d] = ((LL)(x - y) * INV2 % P + P) % P;
			}
}
void Solve(int a[], int b[], int n) {
	FWT(a, n); FWT(b, n);
	for (int i = 0; i < n; i++) b[i] = Ksm(b[i], t);
	for (int i = 0; i < n; i++) a[i] = (LL)a[i] * b[i] % P;
	UFWT(a, n);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Read(n); Read(t); S = 1 << n;
	for (i = 0; i < S; i++) Read(a[i]);
	for (i = 0; i < n; i++) b[1 << i] = 1; b[0] = 1;
	Solve(a, b, S);
	for (i = 0; i < S; i++) printf("%d ", a[i]);
	return 0;
}
