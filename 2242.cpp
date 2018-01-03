#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
void Read(LL &x) {
	scanf("%lld", &x);
}
LL Pow(LL x, LL y, LL P) {
	LL R = 1;
	while (y) {
		if (y & 1) R = R * x % P;
		y >>= 1;
		if (y) x = x * x % P;
	}
	return R;
}
LL P, A, B;
map<LL, int>mp;
void Solve3() {
	int i, j;
	mp.clear(); A %= P; B %= P;
	if (!A && B) return printf("Orz, I cannot find x!\n"), (void)0;
	if (!A && !B) return printf("1\n"), (void)0;
	//if (!(A % P)) return printf("Orz, I cannot find x!\n"), (void)0;
	LL M = ceil(sqrt(P)), As = 1;
	mp[1] = M + 1;
	for (i = 1; i < M; i++) {
		As = As * A % P;
		if (!mp[As]) mp[As] = i;
	}
	LL T = Pow(A, P - M - 1, P); As = 1;
	for (i = 0; i < M; i++) {
		int x = mp[As * B % P];
		if (x) {
			if (x == M + 1) x = 0;
			printf("%lld\n", 1LL * i * M + x); return;
		}
		As = As * T % P;
	}
	printf("Orz, I cannot find x!\n");
}
void Solve2() {
	A %= P; B %= P;
	if (!A && B) return printf("Orz, I cannot find x!\n"), (void)0;
	printf("%lld\n", B * Pow(A, P - 2, P) % P);
}
LL N, K;
int main() {
	Read(N); Read(K);
	while (N--) {
		Read(A); Read(B); Read(P);
		if (K == 1) printf("%lld\n", Pow(A, B, P));
		if (K == 2) Solve2();
		if (K == 3) Solve3();
	}
	return 0;
}
