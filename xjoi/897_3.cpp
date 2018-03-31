#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100000;
LL T, f, n;
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
const int N = 10000010;
int pri[N], vis[N], tot;
void Pre(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) pri[++tot] = i;
		for (int j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[i * pri[j]] = 1; if (i % pri[j] == 0) break;
		}
	}
}
bool ChkPri(LL x) {
	for (int i = 1; i <= tot && (LL)pri[i] * pri[i] <= x; i++)
		if (x % pri[i] == 0) return 0;
	return 1;
}
bool ChkSqr(LL x) {
	for (int i = 1; i <= tot && (LL)pri[i] * pri[i] <= x; i++)
		if (x % ((LL)pri[i] * pri[i]) == 0) return 0;
	return 1;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T); Pre(N - 1);
	while (T--) {
		Read(f); Read(n);
		if (f == 1) {
			puts((n & 1) ? "YES" : "NO");
		} else if (f == 2) {
			puts((n <= 2) ? "YES" : "NO");
		} else if (f == 3) {
			if (n == 2 || n == 3) puts("YES");
			else if (n % 2 == 0 && ChkPri(n / 2) && ChkSqr(n / 2 - 1)) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
