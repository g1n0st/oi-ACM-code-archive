#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
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

int T, n, K;
inline int SG(int x, int y) {
	if (x == n || y == n) {
		if ((n & 3) == 0) return (x != n || y != n);
		if ((n & 3) == 1) return x == n - 1 || y == n - 1;
	}
	x = (x + 1) >> 1; y = (y + 1) >> 1;
	return !((x & 1) && (y & 1));
}
inline int Dis(int x, int y) {
	if (x < y) swap(x, y);
	int x2 = (x - 1) >> 1, y2 = (y - 1) >> 1;
	if ((n & 3) == 0) {
		if (x == n && y == n) return n - 2;
		if (x == n) --x;
		if (y == n) --y;
	}
	if ((n & 3) == 1) {
		if (x == n && y == n) return n - 1;
		if (x == n) {
			if (y == n - 1) return n - 2;
			return ((y2 >> 1) << 1) + (n >> 1);
		}
	}
	if (x % 4 == 1 || x % 4 == 2) return x2 + y2;
	if (x % 4 == 0) ++y;
	return x2 + ((y >> 2) << 1);
}
void Max(int &x, int y) {
	x = max(x, y);
}
void Solve() {
	Read(K); Read(n);
	int x, y, f[2] = { 0, 0 };
	while (K--) {
		Read(x); Read(y);
		Max(f[SG(x, y)], Dis(x, y));
	}
	puts(f[1] > f[0] ? "Yes" : "No");
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T);
	while (T--) Solve();
	return 0;
}
