#include <bits/stdc++.h>
using namespace std;
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
const int N = 1010;
int n, p, a[N], f[N][5 * N];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(p);
	for (int i = 1; i <= n; i++) Read(a[i]);
	sort(a + 1, a + 1 + n, greater<int>());
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < a[1]; j++) f[i][j % a[i]] |= f[i - 1][j];
		f[i][p % a[i]] = 1;
	}
	int ans = 0;
	for (int i = 0; i <= a[n]; i++) if (f[n][i])
		if (p - i < p - ans) ans = i;
	cout << ans << endl;
	cout << 0 << endl;
	return 0;
}
