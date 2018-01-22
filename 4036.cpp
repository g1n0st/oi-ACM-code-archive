#include <bits/stdc++.h>
using namespace std;
const int V = 21;
double p[1 << V];
int N, cnt[1 << V], S;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	scanf("%d", &N); S = 1 << N;
	for (i = 0; i < S; i++) scanf("%lf\n", &p[i]);
	for (j = 0; j < N; j++)
		for (i = 0; i < S; i++)
			if ((i >> j) & 1) p[i] += p[i ^ (1 << j)], cnt[i]++;
	double Ans = 0;
	for (i = 0; i < S - 1; i++) {
		if (p[i] >= 1 - 1e-18) return printf("INF\n"), 0;
		if ((N - cnt[i]) & 1) Ans -= 1 / (p[i] - 1);
		else Ans += 1 / (p[i] - 1);
	}
	printf("%.10lf\n", Ans);
	return 0;
}
