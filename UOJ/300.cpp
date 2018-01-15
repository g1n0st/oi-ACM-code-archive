#include <bits/stdc++.h>
using namespace std;
const int V = 500000;
const int P = 1000000007;
typedef long long LL;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(LL &x) {
	x = 0; static char c;
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
LL N, a[V], f[V], g[V], Ans;
void Add(LL &x, LL y) {
	(x += y) %= P;
}
int main() {
	int i, j;
	Read(N);
	for (i = 1; i <= N; i++) Read(a[i]);
	reverse(a + 1, a + 1 + N);
	for (i = 1; i <= N; i++) {
		int S = a[i];
		for (int T = S; T; T = (T - 1) & S) Add(f[i], g[T]);
		Add(f[i], g[0]); Add(Ans, f[i]); Add(g[S], f[i] + 1);
	}
	printf("%lld\n", Ans);
	return 0;
}
