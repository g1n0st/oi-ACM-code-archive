#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 2000010;
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

int n, a[V], X;
LL cnt[V], sigma[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); cnt[a[i]]++; sigma[a[i]] += a[i]; X = max(X, a[i]);
	}
	for (int i = 1; i <= 2000000; i++) {
		cnt[i] += cnt[i - 1]; sigma[i] += sigma[i - 1];
	}
	LL ans = sigma[X];
	for (int i = 1; i <= X; i++) {
		LL cur = 0;
		for (int j = 0; j <= (X / i); j++) {
			LL tot = cnt[i * (j + 1) - 1] - ((i * j - 1) == -1 ? 0 : cnt[i * j - 1]);
			LL sig = sigma[i * (j + 1) - 1] - ((i * j - 1) == -1 ? 0 : sigma[i * j - 1]);
			cur += tot * j + sig - tot * i * j;
		}
		ans = min(ans, cur);
	}
	cout << ans << endl;
	return 0;
}
