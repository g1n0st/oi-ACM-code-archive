#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100000;
const int P = 998244353;
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
const int N = 410;
int f[N][N], n, K, w[N];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K);
	for (int i = 1; i <= n; i++) Read(w[i]);
	f[0][0] = 1;
	for (int j = 1; j <= n; j++)
		for (int i = 0; i <= n; i++)
			if (i < K) f[j][i] = Ksm(j, i);
			else {
				f[j][i] = f[j - 1][i];
				for (int p = 1; p <= i; p++)
					f[j][i] = (f[j][i] + (LL)f[j - 1][p - 1] * f[j][i - p] % P * Ksm(w[j], min(p, i - K + 1) - max(1, p - K + 1) + 1) % P) % P;
			}
	printf("%d\n", f[n][n]);
	return 0;
}
