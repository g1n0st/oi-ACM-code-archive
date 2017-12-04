#include <bits/stdc++.h>
using namespace std;
const int V = 110010;
int Max(int a, int b) {
	return a > b ? a : b;
}
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0;
	static char c;
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = get();
	}
}
int ch[V * 220][2], Val[V * 220], tot, Rt[V];
void Insert(int x, int v, int y) {
	int now = Rt[x], i, j;
	for (i = 20; ~i; i--) {
		j = v & 1;
		if (!ch[now][j]) ch[now][j] = ++tot;
		now = ch[now][j];
		v >>= 1;
	}
	Val[now] += y;
}
int Query(int x, int v) {
	int now = Rt[x], i, j;
	for (i = 20; ~i; i--) {
		j = v & 1;
		if (!ch[now][j]) return 0;
		now = ch[now][j];
		v >>= 1;
	}
	return Val[now];
}
int N, M, a[V], p[V], l[V], r[V], bel[V], B, Xor[V];
int main(void) {
	int i, j;
	//freopen("in.txt", "r", stdin);
	Read(N);
	Read(M);
	B = (sqrt(N) / 4 + 1) * 3;
	for (i = 1; i <= N; i++) Rt[i] = i;
	tot = N + 1;
	for (i = 1; i <= N; i++) Read(a[i]);
	for (i = 1; i <= N; i++) p[i] = p[i - 1] ^ a[i];
	for (i = 1; i <= N; i++) {
		bel[i] = (i - 1) / B + 1;
		if (!l[bel[i]]) l[bel[i]] = i;
		r[bel[i]] = i;
	}
	B = bel[N];
	for (i = 1; i <= B; i++) {
		for (j = l[i]; j <= r[i]; j++)
			Insert(i, p[j], 1);
	}
	int op, x, y;
	while (M--) {
		Read(op);
		Read(x);
		Read(y);
		if (op & 1) {
			y = y ^ a[x];
			a[x] ^= y;
			for (i = x; i <= r[bel[x]]; i++) {
				Insert(bel[x], p[i], -1);
				p[i] ^= y;
				Insert(bel[x], p[i], 1);
			}
			for (i = bel[x] + 1; i <= B; i++) Xor[i] ^= y;
		} else {
			int Ans = 0;
			for (i = 1; i <= bel[x] - 1; i++)
				Ans += Query(i, y ^ Xor[i]);
			for (i = l[bel[x]]; i <= x; i++)
				if ((p[i] ^ Xor[bel[x]]) == y) Ans++;
			printf("%d\n", Ans);
		}
	}
	return 0;
} 
