#include <bits/stdc++.h>
using namespace std;

const int N = 21;
const int V = 2000010;
const int P = 1e9 + 7;
const int INV2 = (P + 1) >> 1;
typedef long long LL;

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
int a[V], b[V], c[V];
int n, m;
int count(int x) {
	int r = 0;
	for (; x; x -= (x & -x)) r++;
	return r;
}
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
int main(void) {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Read(n); Read(m);
	for (i = 1; i <= n; i++, get())
		for (j = 1; j <= m; j++) {
			a[j] = a[j] << 1 | (get() - '0');
		}
	for (i = 1; i <= m; i++) c[a[i]]++;
	for (i = 0; i < (1 << n); i++) {
		b[i] = min(count(i), n - count(i));
	}
	FWT(b, 1 << n); FWT(c, 1 << n);
	for (i = 0; i < (1 << n); i++) c[i] = (LL)c[i] * b[i] % P;
	UFWT(c, 1 << n); int Ans = 1 << 30;
	for (i = 0; i < (1 << n); i++) Ans = min(Ans, c[i]);
	printf("%d\n", Ans);
	return 0;
}
