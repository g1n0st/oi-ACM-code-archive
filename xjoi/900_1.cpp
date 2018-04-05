#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 200010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T>
void Read(T &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}

int n, b[V], v[V], tot[V];
LL r[V], ans, f[V], g[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) Read(b[i]);
	for (int i = 1; i <= n; i++) Read(r[i]);
	for (int i = 1; i <= n; i++) {
		Read(v[i]); ans += v[i];
	}
	cout << ans << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) f[j] += g[i];
		g[i] = 0;
		if (f[i] == r[i]) {
			putchar('1');
			for (int j = i; j <= n; j += i) g[j] += b[i];
			for (int j = i; j <= n; j += i) f[j] += g[i];
		}
		else putchar('0');
		putchar(' ');
	}
	return 0;
}
