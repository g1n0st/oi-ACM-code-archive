#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
const int P = 100003;
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
int pri[V], tot, vis[V];
int Ksm(int x, int y = P - 2) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
int n, K, a[V], C, g[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K);
	for (int i = 1; i <= n; i++) Read(a[i]);
	for (int i = n; i; i--)
		if (a[i]) {
			C++; for (int j = 1; (LL)j * j <= i; j++)
				if (i % j == 0) {
					a[j] ^= 1; if ((LL)j * j != i) a[i / j] ^= 1;
				}
		}
	for (int i = n; i > K; i--) 
		g[i] = ((LL)n * Ksm(i) % P + (LL)(n - i) * Ksm(i) % P * g[i + 1] % P) % P;
	int ans = 0;
	if (n == K || C <= K) ans = C;
	else {
		ans = K;
		for (int i = C; i > K; i--) ans = (ans + g[i]) % P;
	}
	for (int i = 1; i <= n; i++) ans = (LL)ans * i % P;
	cout << ans << endl;
	return 0;
}
