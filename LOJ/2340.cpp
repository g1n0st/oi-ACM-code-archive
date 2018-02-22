#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 30000;
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
int Ksm(int x, int y = P - 2, int p = P) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % p;
		y >>= 1; if (y) x = (LL)x * x % p;
	}
	return r;
}
const int N = 23;
const int bN = 1 << N | 1;
int S, n, m, p;
int g[N], w[bN];
void fmt(int *a) {
	for (int i = 1; i < S; i <<= 1)
		for (int j = 0; j < S; j++) {
			if (j & i) a[j] += a[j ^ i];
			if (a[j] >= P) a[j] -= P;
		}
}
void ifmt(int *a) {
	for (int i = 1; i < S; i <<= 1)
		for (int j = 0; j < S; j++) {
			if (j & i) a[j] -= a[j ^ i];
			if (a[j] < 0) a[j] += P;
		}
}
int inv[V], cnt[bN];
bool can[bN];
int fa[N];
int f[N][bN], h[N][bN];
int getf(int x) {
	return fa[x] = x == fa[x] ? x : getf(fa[x]);
}
void Pre(int m) {
	for (int i = 1; i <= m; i++) inv[i] = Ksm(i);
	for (int i = 1; i < S; i++) cnt[i] = cnt[i >> 1] + (i & 1);
	for (int i = 1; i < S; i++) {
		bool &val = can[i];
		for (int j = 0; j < n; j++) fa[j] = j;
		for (int j = 0; j < n; j++) if ((i >> j) & 1)
			for (int k = 0; k < n; k++) if ((i >> k) & 1)
				if ((g[j] >> k) & 1) {
					int x = getf(j), y = getf(k);
					if (x ^ y) fa[x] = y;
				}
		for (int j = 0, k = -1; j < n; j++) if ((i >> j) & 1) {
			if (!~k) k = getf(j); else if (k ^ getf(j)) {
				val = 1; break;
			}
			if (cnt[g[j] & i] & 1) {
				val = 1; break;
			}
		}
	}
	for (int i = 0; i < S; i++) if (can[i]) h[cnt[i]][i] = Ksm(w[i], p);
	for (int i = 1; i <= n; i++) fmt(h[i]);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	Read(n); Read(m); Read(p); S = 1 << n;
	int u, v;
	for (int i = 1; i <= m; i++) {
		Read(u); Read(v); --u; --v; g[u] |= 1 << v; g[v] |= 1 << u;
	}
	for (int i = 0; i < n; i++) Read(w[1 << i]); fmt(w);
	Pre(3000);
	f[0][0] = 1; fmt(f[0]);
	for (int i = 1; i <= n; i++) {
		int *cur = f[i];
		for (int j = 0; j < i; j++) {
			int *a = f[j], *b = h[i - j];
			for (int s = 0; s < S; s++)
				cur[s] = (cur[s] + (LL)a[s] * b[s] % P) % P;
		}
		ifmt(cur);
		for (int s = 0; s < S; s++) {
			if (i ^ cnt[s]) cur[s] = 0;
			else cur[s] = (LL)cur[s] * Ksm(inv[w[s]], p) % P;
		}
		if (i ^ n) fmt(cur);
	}
	printf("%d\n", f[n][S - 1]);
	return 0;
}
