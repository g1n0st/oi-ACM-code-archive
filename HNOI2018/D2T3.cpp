#include <cstdio>
#include <ctype.h>
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long LL;

const int V = 100000;
const int N = 20101;
const int GIVEN_VAL = 42;

char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T> void Read(T &x) {
	x = 0; static char c; int f = 0;
	for (; !isdigit(c); c = get()) if (c == '-') f ^= 1;
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
	if (f) x = -x;
}

int n;
int G[N][2];
LL a[N << 1], b[N << 1], c[N << 1], f[N << 1][GIVEN_VAL][GIVEN_VAL];

void dfs(int u, int dep) {
	if (u >= n) {
		for (int i = 0; i <= dep; i++)
			for (int j = 0; j <= dep; j++)
				f[u][i][j] = c[u] * (a[u] + i) * (b[u] + j);
		return;
	}
	dfs(G[u][0], dep + 1);
	dfs(G[u][1], dep + 1);
	for (int i = 0; i <= dep; i++)
		for (int j = 0; j <= dep; j++)
			f[u][i][j] = std::min(f[G[u][0]][i + 1][j] + f[G[u][1]][i][j],
														f[G[u][0]][i][j] + f[G[u][1]][i][j + 1]);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	Read(n);
	int x, y;
	for (int i = 1; i < n; i++) {
		Read(x); Read(y);
		if (x < 0) x = n - 1 - x;
		if (y < 0) y = n - 1 - y;
		G[i][0] = x; G[i][1] = y;
	}
	for (int i = 0; i < n; i++) {
		Read(a[i + n]); Read(b[i + n]); Read(c[i + n]);
	}

	dfs(1, 0);
	
	std::cout << f[1][0][0] << std::endl;
	return 0;
}
