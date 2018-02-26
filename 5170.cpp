#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PI;
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
PI p[V];
int n, K, a[V], cnt[V], b[V], tot;
int t[V], ans[V];
void add(int x) {
	for (; x <= n; x += x & -x) t[x]++;
}
int query(int x) {
	int r = 0;
	for (; x; x -= x & -x) r += t[x];
	return r;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K);
	for (int i = 1; i <= n; i++) Read(a[i]);
	for (int i = 1; i <= n; i++) p[i] = PI(a[i], i);
	sort(p + 1, p + 1 + n);
	for (int i = n; i; i--) {
		cnt[i] = query(p[i].second);
		add(p[i].second);
	}
	for (int i = 1; i <= n; i++) {
		if (cnt[i] >= K) ans[p[i].second - K] = p[i].first;
		else b[++tot] = p[i].first;
	}
	sort(b + 1, b + tot); tot = 0;
	for (int i = 1; i <= n; i++) if (!ans[i]) ans[i] = b[++tot];
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
