#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 2000010;
const int P = 1000000007;
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
int Ksm(int x, int y = P - 2, int p = P) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1;
		if (y) x = (LL)x * x % P;
	}
	return r;
}
int fi[V], g[V], vis[V], N, M;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x;
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(x); M = max(x, M);
		if (vis[x]) continue;
		for (j = 1; j * j <= x; j++)
			if (!(x % j)) vis[j] = vis[x / j] = 1;
	}
	fi[1] = 1;
	for (i = 1; i <= M; i++) g[i] = 1;
	for (i = 2; i <= M; i++) {
		fi[i] = (fi[i - 1] + fi[i - 2]) % P;
		g[i] = (LL)g[i] * fi[i] % P; int inv = Ksm(g[i]);
		for (j = i + i; j <= M; j += i) g[j] = (LL)g[j] * inv % P;
	}
	int Ans = 1;
	for (i = 1; i <= M; i++)
		if (vis[i]) Ans = (LL)Ans * g[i] % P;
	printf("%d\n", Ans);
	return 0;
}
