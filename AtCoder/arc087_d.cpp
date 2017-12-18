#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int V = 5010;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
void Add(int &x, int y) {
	(x += y) %= P;
}
int N, fac[V], c[V][V], f[V], w[2];
vector<int> G[V];
void Init(int n) {
	int i, j;
	w[0] = 1; w[1] = -1;
	fac[0] = 1; for (i = 1; i <= n; i++) Add(fac[i], 1LL * fac[i - 1] * i % P);
	c[0][0] = 1;
	for (i = 1; i <= n; i++) {
		c[i][0] = 1;
		for (j = 1; j <= i; j++) Add(c[i][j], c[i - 1][j] + c[i - 1][j - 1]);
	}
}
int siz[V], mxs[V];
void Dfs(int u, int fa) {
	siz[u] = 1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs(v, u); siz[u] += siz[v];
		mxs[u] = max(mxs[u], siz[v]);
	}
	mxs[u] = max(mxs[u], N - siz[u]);
}
int main() {
	int i, j, u, v;
	Read(N); Init(N);
	for (i = 1; i < N; i++) {
		Read(u); Read(v);
		G[u].emplace_back(v); G[v].emplace_back(u);
	}
	Dfs(1, 0); int Rt = 0;
	for (i = 1; i <= N; i++)
		if (mxs[i] <= N / 2) {
			if (Rt) {
				printf("%lld\n", 1LL * fac[N / 2] * fac[N / 2] % P);
				return 0;
			}
			else Rt = i;
		}
	Dfs(Rt, 0); f[0] = 1;
	for (auto v : G[Rt]) {
		int Now = siz[v];
		for (i = N; i; i--)
			for (j = i - 1; ~j && i - j <= Now; j--)
				Add(f[i], 1LL * f[j] * c[Now][i - j] % P * c[Now][i - j] % P * fac[i - j] % P);
	}
	int Ans = 0;
	for (i = 0; i <= N; i++) {
		Add(Ans, (P + 1LL * w[i % 2] * f[i] % P * fac[N - i] % P) % P);
	}
	printf("%d\n", Ans);
	return 0;
}
