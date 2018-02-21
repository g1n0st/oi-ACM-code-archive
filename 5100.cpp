#include <bits/stdc++.h>
using namespace std;
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
void NIE() {
	puts("NIE"); exit(0);
}
void Add(int a, int b, int c) {
	static int f; if (!f) puts("TAK"), f = 1;
	printf("%d %d %d\n", a, b, c);
}
int n, a[V], b[V], q[V], v[V << 1];
int f[V], g[V];
void chk(int v) {
	if (!v) return;
	for (int i = 2; i < n; i++)
		if (abs(a[i] - b[i]) ^ v) return;
	Add(1, n, v);
	for (int i = 2; i < n; i++) Add(a[i] < b[i] ? 1 : n, i, min(a[i], b[i]));
	exit(0);
}
bool cmp(int x, int y) {
	return a[x] + b[x] == a[y] + b[y] ? a[x] < a[y] : a[x] + b[x] < a[y] + b[y];
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 2; i < n; i++) Read(a[i]);
	for (int i = 2; i < n; i++) Read(b[i]);
	if (n == 2) return Add(1, 2, 1), 0;
	chk(abs(a[2] - b[2]));
	for (int i = 1; i < n; i++) q[i] = i;
	sort(q + 2, q + n, cmp);
	int o, w = a[q[2]] + b[q[2]];
	for (o = 2; o < n; o++) if (a[q[o]] + b[q[o]] != w) break;
	for (int i = 2; i < o - 1; i++) if (a[q[i]] == a[q[i + 1]]) NIE();
	v[w] = n; for (int i = 1; i < o; i++) v[a[q[i]]] = q[i];
	for (int i = o; i < n; i++) {
		int t = a[q[i]] + b[q[i]] - w;
		if (t & 1) NIE(); t >>= 1;
		f[i] = v[a[q[i]] - t]; g[i] = t;
		if (!f[i]) NIE();
	}
	for (int i = 2; i < o; i++) Add(q[i - 1], q[i], a[q[i]] - a[q[i - 1]]);
	Add(q[o - 1], n, b[q[o - 1]]);
	for (int i = o; i < n; i++) Add(q[i], f[i], g[i]);
	return 0;
}
