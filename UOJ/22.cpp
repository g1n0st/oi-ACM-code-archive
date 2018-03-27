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
const int N = 5050;
int fac[N], inv[N];
void Pre(int n) {
	fac[0] = 1; for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % P;
	inv[n] = Ksm(fac[n], P - 2); for (int i = n - 1; ~i; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % P;
}
int f[N], g[N], n, p, a[N], cnt[N];
inline int ca(int x, int y) {
	return (LL)fac[x] * inv[y] % P;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Pre(N - 1); Read(n); Read(p);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); cnt[a[i]]++;
	}
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= max(a[n], p); i++) cnt[i] += cnt[i - 1];
	g[p] = 1; f[p] = ca(cnt[a[n]], cnt[p]);
	for (int i = p; i; i--) if (g[i])
		for (int j = 1; a[j] <= i && j <= n; j++) {
			g[i % a[j]] |= g[i];
			f[i % a[j]] = (f[i % a[j]] + (LL)f[i] * ca(cnt[i] - 1, cnt[i % a[j]]) % P) % P;
		}
	int ans;
	for (ans = a[1] - 1; ~ans; ans--)
		if (g[ans]) break;
	cout << ans << endl << f[ans] << endl;
	return 0;
}
