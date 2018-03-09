#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x, bool &X) {
	x = 0; static char c; int f = 0; X = 0;
	for (; !isdigit(c); c = get()) if (c == 'X') {
		c = get(); X = 1; return;
	}
	else if (c == '-') f = 1;
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
	if (f) x = -x;
}
int n, cnt, a[V], p[V];
LL Ans;
void solve(int l, int r)
{
	if (l == r)  return;
	int mid = (l + r) >> 1, h1 = l, h2 = mid + 1;
	solve(l, mid); solve(mid + 1, r);
	for (int i = l; i <= r; i++) {
		if (h1 <= mid && (h2 > r || a[h1] <= a[h2]))  Ans += h2 - mid - 1, p[i] = a[h1++];
		else p[i] = a[h2++];
	}
	for (int i = l; i <= r; i++) a[i] = p[i];
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	bool X;
	Read(n, X);
	if (n == 1) return puts("L"), 0;
	for (int i = 1; i <= n; i++) {
		Read(a[i], X); if (X) cnt++;
	}
	if (cnt) return puts(cnt & 1 ? "W" : "L"), 0;
	solve(1, n);
	return puts(Ans & 1 ? "W" : "L"), 0;
}
