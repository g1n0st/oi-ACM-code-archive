#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL Max(LL a, LL b) {
	return a > b ? a : b;
}
LL Min(LL a, LL b) {
	return a < b ? a : b;
}
void Read(LL &x) {
	scanf("%lld", &x);
}
LL Calc(LL N, LL S) {
	LL Ret = 0LL;
	for (int k = 1; k < N; k *= 10) {
		LL l = S * k, r = Min(l + k - 1, N), pos = l - 1;
		for (int i = l; i <= r; i = pos + 1) {
			pos = N / (N / i);
			Ret += (Min(pos, r) - i + 1) * (N / pos); 
		}
	}
	return Ret;
}
int main(void) {
	//freopen("in.txt", "r", stdin);
	LL L, R;
	Read(L), Read(R);
	for (int i = 1; i <= 9; i++)
		printf("%lld\n", Calc(R, i) - Calc(L - 1, i));
	return 0;
}
