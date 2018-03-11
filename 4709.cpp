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
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
LL f[V];
int n, a[V], cnt[V], s[V];
vector<int> st[V];
LL F(int x, int y) {
	return f[x - 1] + (LL)a[x] * y * y;
}
int cal(int x, int y) {
	int l = 1, r = n, mid, res = n + 1;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (F(x, mid - s[x] + 1) >= F(y, mid - s[y] + 1)) r = (res = mid) - 1;
		else l = mid + 1;
	}
	return res;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); int x;
	for (int i = 1; i <= n; i++) {
		Read(x); s[i] = ++cnt[a[i] = x];
		vector<int> &t = st[x];
		while (t.size() >= 2 &&
			cal(t[t.size() - 2], t[t.size() - 1]) <= cal(t[t.size() - 1], i)) t.pop_back();
		t.push_back(i);
		while (t.size() >= 2 && cal(t[t.size() - 2], t[t.size() - 1]) <= s[i]) t.pop_back();
		f[i] = F(t[t.size() - 1], s[i] - s[t[t.size() - 1]] + 1);
	}
	printf("%lld\n", f[n]);
	return 0;
}
