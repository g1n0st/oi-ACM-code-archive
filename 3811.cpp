#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long UL;
const int V = 100010;
const int K = 110;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T> void Read(T &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
int clz(UL x) {
	int r = 0;
	for (; x; x >>= 1) r++;
	return r - 1;
}
int n, m, k, t[K];
UL a[V], ans1, ans2, p[K];
bitset<100> S[V], E[K];
int Gauss() {
	int i, j, k;
	for (i = 1; i <= ::k; i++) E[i] = S[t[i]];
	for (i = 1, j = 1; i <= ::k && j <= n; j++) {
		int p = -1;
		for (k = i; k <= ::k; k++) if (E[k][j]) {
			p = k; break;
		}
		if (!~p) continue;
		swap(E[i], E[p]);
		for (k = p + 1; k <= ::k; k++)
			if (E[k][j]) E[k] ^= E[i];
		i++;
	}
	for (k = i, i--; k <= ::k; k++) if (E[k][0]) return -1;
	return i;
}
void dfs(int now) {
	if (now > k) {
		int x = 0, y = Gauss();
		if (!~y) return;
		for (int i = 1; i <= k; i++) x += t[i];
		x - y >= 0 ? ans1 += (1ULL << (x - y)) : ans2 ++;
		return;
	}
	for (int i = 0; i <= m; i++) {
		t[now] = i; dfs(now + 1);
	}
}
int main() {
	Read(n); Read(k);
	for (int i = 1; i <= n; i++) Read(a[i]);
	for (int i = 1; i <= n; i++) m = max(m, clz(a[i]));
	for (int i = 1; i <= n; i++)
		for (int j = 63; ~j; j--) {
			if (!(a[i] >> j)) continue;
			if (!p[j]) {
				p[j] = a[i]; break;
			}
			a[i] ^= p[j];
		}
	for (int i = 1; i <= (n = 64); i++) a[i] = p[i - 1];
	for (int i = 0; i <= m; i++) {
		S[i][0] = 1;
		for (int j = 1; j <= n; j++) S[i][j] = (a[j] >> i) & 1;
	}
	dfs(1);
	cout << ans1 + ans2 / 2; if (ans2 & 1) cout << ".5"; putchar('\n');
	return 0;
}
