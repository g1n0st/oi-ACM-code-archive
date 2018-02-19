#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 500010;
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
LL Ans;
int n, Type, a[V], cnt[V << 1], pos[V], num[V];
void Solve(int l, int r) {
	if (l == r) {
		Ans++; return;
	}
	int Mid = (l + r) >> 1;
	Solve(l, Mid); Solve(Mid + 1, r);
	for (int i = Mid; i >= l; i--)
		if (++cnt[a[i]] > (Mid - i + 1) / 2) if (!pos[a[i]])
			num[pos[a[i]] = ++*num] = a[i];
	for (int i = Mid + 1; i <= r; i++)
		if (++cnt[a[i]] > (i - Mid) / 2) if (!pos[a[i]])
			num[pos[a[i]] = ++*num] = a[i];
	for (int i = l; i <= r; i++) pos[a[i]] = cnt[a[i]] = 0;
	for (int i = 1; i <= *num; i++) {
		int s = r - l + 1, mx = s, mn = s; cnt[s] = 1;
		for (int j = l; j < Mid; j++) {
			a[j] == num[i] ? ++s : --s; cnt[s]++;
			mx = max(mx, s); mn = min(mn, s);
		}
		a[Mid] == num[i] ? ++s : --s;
		for (int i = mn; i <= mx; i++) cnt[i] += cnt[i - 1];
		for (int j = Mid + 1; j <= r; j++) {
			a[j] == num[i] ? ++s : --s;
			Ans += cnt[min(mx, s - 1)];
		}
		for (int i = mn; i <= mx; i++) cnt[i] = 0;
	}
	*num = 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(Type);
	for (int i = 1; i <= n; i++) Read(a[i]);
	Solve(1, n);
	cout << Ans << endl;
	return 0;
}
