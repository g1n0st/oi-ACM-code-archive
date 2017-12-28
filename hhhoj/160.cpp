#include <cstdio>
using namespace std;
typedef long long LL;
LL Min(LL a, LL b) {
	return a < b ? a : b;
}
void Read(LL &x) {
	scanf("%lld", &x);
}
LL T, N, M, S, fullM;
LL Calc(LL x) {
	LL s1 = (S - x) / (N - 2) + 1, R = (S - x) % (N - 2), L = N - 2 - R;
	LL Ret = 0;
	Ret += (s1 - 1) * L * (L - 1) / 2;
	Ret += s1 * R * (R - 1) / 2;
	Ret += x * (N - 2 - (fullM - M));
	Ret += S;
	Ret += s1 * L * R;
	return Min(Ret, (LL)1e18);
}
int main() {
	Read(T);
	while (T--) {
		Read(N); Read(M); Read(S);
		fullM = N * (N - 1) / 2;
		if (fullM - M >= N - 1) 
			printf("%lld\n", M - 1 + S - (N - 2));
		else {
			LL Ans = 1e18;
			Ans = Min(Ans, Calc((S + N - 2) / (N - 1)));
			Ans = Min(Ans, Calc(S - N + 2));
			Ans = Min(Ans, Calc(S - S / (N - 1) * (N - 2)));
			printf("%lld\n", Ans);
		}
	}
	return 0;
}
