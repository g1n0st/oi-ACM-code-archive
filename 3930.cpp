#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
const LL P = 1000000007;
void Read(LL &x) {
	scanf("%lld", &x);
}
LL Pow(LL x, int y) {
	LL R = 1;
	while (y) {
		if (y & 1) R = R * x % P;
		y >>= 1;
		if (y) x = x * x % P;
	}
	return R;
}
void Add(LL &x, LL y) {
	(x += y) %= P;
}
LL Val(LL x, LL y, LL k) {
	return (y / k) - ((x - 1) / k);
}
LL N, K, L, R, L1, f[V];
int main() {
	int i, j;
	Read(N); Read(K); Read(L); Read(R);
	L1 = max(L / K + ((L % K) & 1), 100001LL);
	for (i = 100000; i; i--) {
		Add(f[i], Pow(Val(L, R, i * K), N));
		Add(f[i], P - Val(L1, R / K, i));
		for (j = i * 2; j <= 100000; j += i) Add(f[i], P - f[j]);
	}
	cout << f[1] << endl;
	return 0;
}
