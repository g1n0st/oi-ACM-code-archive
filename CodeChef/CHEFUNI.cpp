#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
LL Min(LL a, LL b) {
	return a < b ? a : b;
}
LL Max(LL a, LL b) {
	return a > b ? a : b;
}
void Swap(LL &x, LL &y) {
	if (x > y) swap(x, y);
}
void P(LL x) {
	printf("%I64d\n", x);
}
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
		x = x * 10 + c - '0';
		c = get();
	}
}
LL T, X, Y, Z, A, B, C;
LL SolveSame(LL x) {
	LL t = Min(3 * B, 2 * C);
	return (t * (x / 2) + (x & 1) * C);
}
void Solve2(LL p) {
	P(p + Y * B + (Z - Y) * A);
}
void Solve1(LL p) {
	if (X == Y && Y == Z) return P(p + SolveSame(X));
	LL c2 = Min(X / 2, Y / 3);
	p += c2 * Min(2 * C + B, 4 * B);
	X -= c2 * 2; Y -= c2 * 3; Z -= c2 * 3;
	if (X) {
		p += SolveSame(X); Y -= X; Z -= X;
	}
	p += Y * B + (Z - Y) * A;
	P(p);
}
void Solve() {
	Read(X); Read(Y); Read(Z); Read(A); Read(B); Read(C);
	Swap(X, Y); Swap(Y, Z); Swap(X, Y);
	B = Min(B, 2 * A); C = Min(C, A + B);
	if (X == Y && Y == Z) return P(SolveSame(X));
	LL c1 = (Z - Y);
	if (c1 < X) {
		X -= c1; Y -= c1; Z -= c1 * 2;
		return Solve1(c1 * Min(C + A, 2 * B));
	} else {
		Y -= X; Z -= X * 2;
		return Solve2(X * Min(C + A, 2 * B));
	}
}
int main(void) {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T); while (T--) Solve();
	return 0;
}
