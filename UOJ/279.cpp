#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
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
const int N = 510;
int d[N][N], n, K, cnt[N][N];
int fac[N], inv[N], f[N], g[N];
int C(int a, int b) {
	return (LL)fac[a] * inv[b] % P * inv[a - b] % P;
}
void Pre(int n) {
	fac[0] = 1; for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % P;
	inv[n] = Ksm(fac[n], P - 2); for (int i = n - 1; ~i; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % P;
	for (int i = 1; i <= n; i++) {
		f[i] = g[i] = Ksm(K + 1, i * (i - 1) / 2);
		for (int j = 1; j < i; j++)
			f[i] = (f[i] + P - (LL)f[j] * g[i - j] % P * C(i - 1, j - 1) % P * Ksm(K, j * (i - j)) % P) % P;
	}
}
bool judge() {
	for (int i = 1; i <= n; i++) if (d[i][i]) return 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) if (d[i][j] > K || d[i][j] != d[j][i]) return 0;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (d[i][j] > d[i][k] + d[k][j]) return 0;
	return 1;
}
int fa[N], siz[N];
int getf(int x) {
	return fa[x] == x ? x : getf(fa[x]);
}
void merge(int x, int y) {
	x = getf(x); y = getf(y);
	if (x == y) return; fa[x] = y; siz[y] += siz[x]; siz[x] = 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K); Pre(N - 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			Read(d[i][j]);
	if (!judge()) return puts("0"), 0;
	
	for (int i = 1; i <= n; i++) {
		fa[i] = i; siz[i] = 1;
	}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (!d[i][j]) merge(i, j);
	int ans = 1;
	for (int i = 1; i <= n; i++)
		if (siz[i]) ans = (LL)ans * f[siz[i]] % P;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			int x = getf(i), y = getf(j); if (x ^ y) ++cnt[x][y], ++cnt[y][x];
		}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			int a = cnt[i][j], flg = 0; if (!a) continue;
			for (int k = 1; k <= n; k++)
				if (cnt[i][k] && cnt[k][j] && d[i][j] == d[i][k] + d[k][j]) {
					flg = 1; break;
				}
			if (flg) ans = (LL)ans * Ksm(K - d[i][j] + 1, a) % P;
			else ans = (LL)ans * (Ksm(K - d[i][j] + 1, a) + P - Ksm(K - d[i][j], a)) % P;
		}
	printf("%d\n", ans);
	return 0;
}
