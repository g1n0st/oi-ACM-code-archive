#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 200010;
const int P = 1000000007;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
int lowbit(int x) {
	return x & (-x);
}
namespace BIT1 {
	int c[V], N;
	void Add(int x, int v) {
		while (x <= N) {
			c[x] += v; x += lowbit(x);
		}
	}
	void Add(int l, int r, int v) {
		Add(l, v); Add(r + 1, -v);
	}
	int Val(int x) {
		int Ret = 0;
		while (x) {
			Ret += c[x]; x -= lowbit(x);
		}
		return Ret;
	}
}
namespace BIT2 {
	int c[V], N;
	void Add(int x, int v) {
		while (x <= N) {
			c[x] += v; x += lowbit(x);
		}
	}
	int Sum(int x) {
		int Ret = 0;
		while (x) {
			Ret += c[x]; x -= lowbit(x);
		}
		return Ret;
	}
}
int N, Q, a[V];
LL pw[V], inv[V], fac[V];
void Pre(int n) {
	int i, j;
	fac[0] = 1; for (i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % P;
	inv[1] = 1; for (i = 2; i <= n; i++) inv[i] = (LL)(P - P / i) * inv[P % i] % P;
	inv[0] = 1; for (i = 1; i <= n; i++) inv[i] = inv[i] * inv[i - 1] % P;
	pw[0] = 1;  for (i = 1; i <= n; i++) pw[i] = pw[i - 1] * ((P + 1) >> 1) % P;
}
LL C(int n, int m) {
	return fac[n] * inv[m] % P * inv[n - m] % P;
}
void Add(int i, int r) {
	int a = ::a[i], b = ::a[i + 1];
	if (a > b) swap(a, b);
	BIT1::Add(a, b + 1, r);
	BIT2::Add(b, r); BIT2::Add(max(a, b + 1), r);
}
int Query(int x, int y) {
	int c = BIT2::Sum(x), d = BIT1::Val(x);
	if (c > y || d < y - c) return 0;
	return C(d, y - c) * pw[d] % P;
}
int main() {
	int i, j;
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]); a[i] = a[i] * 2 - 1;
	}
	BIT1::N = BIT2::N = (N << 1); Pre(N);
	for (i = 1; i <= N; i += 2) Add(i, 1);
	Read(Q); int op, x, y;
	while (Q--) {
		Read(op); Read(x); Read(y);
		if (op & 1) {
			Add(x - (~x & 1), -1); Add(y - (~y & 1), -1);
			swap(a[x], a[y]);
			Add(x - (~x & 1), 1), Add(y - (~y & 1), 1);
		}
		else {
			int a = ::a[x], b = ::a[((x - 1) ^ 1) + 1];
			if (a > b) printf("%d\n", Query(a, y));
			else {
				LL Ans = 0;
				Add(x - (~x & 1), -1);
				BIT2::Add(b, 1);
				Ans += (LL)Query(b + 1, y - 1) * ((P + 1) >> 1) % P;
				Ans += (LL)Query(a, y - 1) * ((P + 1) >> 1) % P;
				BIT2::Add(b, -1);
				Add(x - (~x & 1), 1);
				printf("%lld\n", Ans % P);
			}
		}
	}
	return 0;
}
