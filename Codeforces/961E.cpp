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
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}

int sum[V * 50], ls[V * 50], rs[V * 50], rt[V], pT;
int n, a[V];
void Add(int y, int &x, int l, int r, int p) {
	x = ++pT; 
	ls[x] = ls[y]; rs[x] = rs[y]; sum[x] = sum[y] + 1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (p <= mid) Add(ls[y], ls[x], l, mid, p);
	else Add(rs[y], rs[x], mid + 1, r, p);
}
int Query(int x, int l, int r, int p) {
	if (!x) return 0;
	if (l == p) return sum[x];
	int mid = (l + r) >> 1;
	if (p <= mid) return Query(ls[x], l, mid, p) + sum[rs[x]];
	else return Query(rs[x], mid + 1, r, p);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	LL ans = 0;
	for (int i = 1; i <= n; i++) {
		Read(a[i]); a[i] = min(a[i], n);
		ans += Query(rt[min(i - 1, a[i])], 1, n, i);
		Add(rt[i - 1], rt[i], 1, n, a[i]);
	}
	cout << ans << endl;
	return 0;
}
