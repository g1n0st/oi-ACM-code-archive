#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
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
void Solve() {
	int i, j;
	mp.clear();
	if (!(A % P)) return printf("no solution\n"), (void)0;
	LL M = ceil(sqrt(P)), As = 0;
	for (i = 0; i <= M; i++) {
		if (!i) As = B; else As = As * A % P;
		mp[As] = i;
	}
	LL T = Pow(A, M, P); As = 1;
	for (i = 1; i <= M; i++) {
		As = As * T % P;
		if (mp[As]) {
			printf("%d\n", (i * M % P + P - mp[As]) % P); return;
		}
	}
	printf("no solution\n");
}
int main() {
	while (~scanf("%lld%lld%lld", &P, &A, &B)) Solve();
	return 0;
}
