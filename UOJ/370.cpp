#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 262145;
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
int S, all, n, a[V], f[V], v[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	S = (1 << 18) - 1;
	Read(n);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); S &= a[i]; all |= a[i];
	}
	for (int i = 1; i <= n; i++) v[all ^ a[i]] = 1;
	int bS = S ^ all;
	for (int s = all; ; s = (s - 1) & all) {
		for (int i = 0; i <= 18; i++) v[s] |= v[s | (1 << i)];
		if (!s) break;
	}
	for (int i = 1; i <= bS; i++) {
		if ((i & bS) ^ i) continue; f[i] = 1 << 30;
		for (int j = i; ; j = (j - 1) & i) {
			if (j >= f[i]) break;
			if (v[i ^ j]) f[i] = min(f[i], f[j] + j);
			if (!j) break;
		}
	}
	cout << (LL)S * n + f[bS] << endl;
	return 0;
}
