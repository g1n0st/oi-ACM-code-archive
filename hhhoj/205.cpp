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
const int N = 410;
int n, p[N], sym[N];
void Work(int x, int now) {
	if (now > n + 1 - x) return;
	if (x == n + 1) {
		if (now > 0) return;
		for (int i = 1; i <= n; i++)
			putchar(~sym[i] ? '(' : ')');
		exit(0);
	}
	if (sym[x]) {
		now += sym[x]; if (now < 0) return; return Work(x + 1, now);
	}
	for (int k = 1; k >= -1; k--) {
		if (!k) continue;
		if (now + k < 0) continue;
		sym[x] = k; int t = x, ts = 0;
		for (;;) {
			t = p[t]; if (t == x) break;
			++ts; if (ts & 1) sym[t] = -sym[x]; else sym[t] = sym[x];
		}
		Work(x + 1, now + sym[x]);
		if (ts == 1) break;
	}
	sym[x] = 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) Read(p[i]);
	Work(1, 0);
	return 0;
}
