#include <bits/stdc++.h>
using namespace std;
const int V = 1000010;
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
		x = x * 10 + c - '0'; c = get();
	}
}
const int L = 510;
int N, M, Q, a[L][L], f[L][L];
int Calc(int y, int x) {
	return !(a[y][x] + a[y + 1][x + 1] == a[y + 1][x] + a[y][x + 1]);
}
int main() {
	int i, j;
	Read(N); Read(M); Read(Q);
	for (i = 1; i <= N; i++)
		for (j = 1; j <= M; j++) Read(a[i][j]);
	for (i = 1; i < N; i++)
		for (j = 1; j < M; j++)
			f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + Calc(i, j);
	int x, y, k;
	while (Q--) {
		Read(y); Read(x); Read(k);
		if (k == 1) puts("Y");
		else {
			int tmp = f[y + k - 2][x + k - 2] - f[y + k - 2][x - 1] - f[y - 1][x + k - 2] + f[y - 1][x - 1];
			if (!tmp) puts("Y");
			else puts("N");
		}
	}
	return 0;
}
