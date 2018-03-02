#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100000;
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
const int N = 2000010;
int n, v[N], p[N];
LL ans;
void solve(int l, int r)
{
	if (l == r)  return;
	int mid = (l + r) >> 1, h1 = l, h2 = mid + 1;
	solve(l, mid); solve(mid + 1, r);
	for (int i = l; i <= r; i++) {
		if (h1 <= mid && (h2 > r || v[h1] <= v[h2]))  ans += h2 - mid - 1, p[i] = v[h1++];
		else p[i] = v[h2++];
	}
	for (int i = l; i <= r; i++) v[i] = p[i];
}
int main() {
	Read(n);
	for (int i = 1; i <= n; i++) Read(v[i]);
	solve(1, n);
	printf("%lld\n", ans);
	return 0;
}
