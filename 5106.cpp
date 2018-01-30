#include <bits/stdc++.h>
typedef long long LL;
const int V = 200010;
using namespace std;
LL S, L, h[V], a[V], mx, n;
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
bool check(LL x) {
	LL s = 0;
	for (int i = 1; i <= n; i++)
		if (a[i] * x + h[i] >= L) {
			s += a[i] * x + h[i];
			if (s >= S) return 1;
		}
	return 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(S); Read(L);
	for (int i = 1; i <= n; i++) Read(h[i]);
	for (int i = 1; i <= n; i++) Read(a[i]), mx = max(mx, a[i]);
	LL l = 0, r = 1 + max(S, L) / mx + 1, Mid, Ans = 0;
	while (l <= r) {
		Mid = (l + r) / 2;
		if (check(Mid)) r = (Ans = Mid) - 1; else l = Mid + 1;
	}
	printf("%lld\n", Ans);
	return 0;
}
