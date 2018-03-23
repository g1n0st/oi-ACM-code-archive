#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const 
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
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
LL gcd(LL x, LL y) {
	return !y ? x : gcd(y, x % y);
}
LL Solve(LL L, LL m, LL K) {
	LL d = gcd(m, K);
	if (d == 1 || L <= K / d) return L;
	if (K / m - (K - L) >= 0) return Solve(K / d - m / d * (K - L), m, K / d) + m / d * (K - L);
	return K / d;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	LL T, m, K;
	Read(T);
	while (T--) {
		Read(m); Read(K); printf("%lld\n", Solve(K - 1, m, K) + 1);
	}
	return 0;
}
