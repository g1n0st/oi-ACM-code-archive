#include <bits/stdc++.h>
using namespace std;
const int V = 100000;
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
const int N = 55;
int n, a[N], b[N], c[N];
double f[N][N][N][N], A[N], B[N], C[N];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) Read(a[i]);
	for (int i = 1; i <= n; i++) Read(b[i]);
	for (int i = 1; i <= n; i++) Read(c[i]);
	for (int i = 1; i <= n; i++) {
		A[i] = a[i] / 300.0; B[i] = b[i] / 300.0; C[i] = c[i] / 300.0;
	}
	for (int i = 1; i <= n; i++) {
		f[i][0][0][0] = 1.0;
		for (int t = 1; t <= n; t++)
			for (int m = t; ~m; m--)
				for (int a = 0; a <= m; a++)
					for (int b = 0; a + b <= m; b++) {
						int c = m - a - b;
						double cho = 1.0 * m / t;
						double s = 0.0;
						if (a) s += f[i][a - 1][b][c] * A[t];
						if (b) s += f[i][a][b - 1][c] * B[t];
						if (c) s += f[i][a][b][c - 1] * C[t];
						f[i][a][b][c] *= (1 - cho);
						if (i ^ t) f[i][a][b][c] += s * cho;
					}
	}
	double ans = 0;
	for (int a = 0; a <= n; a++)
		for (int b = 0; b <= n - a; b++)
			for (int c = 0; c <= n - a - b; c++) {
				int lst = n - a - b - c;
				if (!lst) continue;
				double SA = 0.0, SB = 0.0, SC = 0.0;
				for (int i = 1; i <= n; i++) {
					double T = f[i][a][b][c] / lst;
					SA += T * A[i]; SB += T * B[i]; SC += T * C[i];
				}
				ans += max(SA * 3 + SB, max(SB * 3 + SC, SC * 3 + SA));
			}
	printf("%.3lf\n", ans);
	return 0;
}
