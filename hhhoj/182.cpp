#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 2501000;
void Read(int &x) {
	scanf("%d", &x);
}
int m0, md, n0, nd;
int N, M, tN[V], tM[V];
LL Ans, vn[V];
int main() {
	int i, j;
	Read(M); Read(N); Read(m0); Read(md); Read(n0); Read(nd);
	for (i = 1; i <= M; i++) {
		tM[m0]++; m0 = (m0 * 58 + md) % (N + 1);
	}
	for (i = 1; i <= N; i++) {
		tN[n0]++; vn[n0] += n0; n0 = (n0 * 58 + nd) % (M + 1);
	}
	for (i = 1; i <= M; i++) {
		tN[i] += tN[i - 1]; vn[i] += vn[i - 1];
	}
	int x = 0, y; LL sm = 0; Ans = vn[M];
	for (i = 0; i <= N; i++)
		for (j = 0; j < tM[i]; j++) {
			x++; sm += i; y = tN[M - x];
			Ans = min(Ans, sm + vn[M - x] + 1LL * (M - x) * (N - y));
		}
	printf("%lld\n", Ans);
	return 0;
}
