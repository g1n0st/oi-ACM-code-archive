#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
void Read(int &x) {
	scanf("%d", &x);
}
int Pow(LL x, int y, int p) {
	LL R = 1;
	while (y) {
		if (y & 1) R = R * x % p;
		y >>= 1;
		if (y) x = x * x % p;
	}
	return R % p;
}
int $(int x) {
	int Ret = x, i;
	for (i = 2; i * i <= x; i++)
		if (!(x % i)) {
			Ret = Ret / i * (i - 1);
			while (!(x % i)) x /= i;
		}
	if (x > 1) Ret = Ret / x * (x - 1);
	return Ret;
}
int T, P;
int Solve(int p) {
	if (p == 1) return 0;
	int k = 0; while (~p & 1) p >>= 1, ++k;
	int phi = $(p), re = Solve(phi);
	re = (re + phi - k % phi) % phi;
	return (Pow(2, re, p) << k);
}
int main() {
	Read(T);
	while (T--) {
		Read(P);  printf("%d\n", Solve(P));
	}
	return 0;
}
