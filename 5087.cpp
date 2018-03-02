#include <bits/stdc++.h>
using namespace std;
typedef bitset<8096> bit;
void Read(int &x) {
	scanf("%d", &x);
}
void Read(int &n, bit &x) {
	Read(n);
	for (int i = 0, v; i <= n; i++) {
		Read(v); if (v) x.set(i);
	}
}
int nf, ng, nh, upper[1025];
bit f, g, h, gx[11], S[1024];
void Mul(bit &r, bit a, bit b) {
	r = 0;
	for (int i = 0; i <= nh; i++)
		if (a[i]) r ^= (b << i);
	for (int i = (nh << 1); i >= nh; i--)
		if (r[i]) r ^= (h << (i - nh)), r[i] = 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(nf, f); Read(ng, g); Read(nh, h);
	for (int i = ng; i >= nh; i--)
		if (g[i]) g ^= (h << (i - nh)), g[i] = 0;
	gx[0].set(0);
	for (int i = 1; i <= 10; i++) Mul(gx[i], gx[i - 1], g);
	S[1].set(0);
	for (int i = 2; i < 1024; i++) {
		upper[i] = upper[i >> 1] + 1;
		S[i] = S[i - (1 << upper[i])] ^ gx[upper[i]];
	}
	bit tmp, base, ans; base.set(0);
	for (int i = 0; i <= nf; i += 10) {
		int s = 0;
		for (int j = i; j < i + 10; j++) s |= (f[j] << (j - i));
		Mul(tmp, base, S[s]); ans ^= tmp; Mul(base, base, gx[10]);
	}
	int n = nh;
	while (!ans[n] && ~n) n--;
	if (!~n) n++;
	printf("%d ", n);
	for (int i = 0; i <= n; i++) {
		putchar('0' + ans[i]); if (i ^ n)  putchar(' ');
	}
	return 0;
}
