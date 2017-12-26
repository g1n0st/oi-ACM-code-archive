#include <bits/stdc++.h>
using namespace std;
const int V = 2000;
int N, M, L, a[100][V], b[100][V], f[100][V], p[100], w[100];
int main() {
	int i, j, k, x, l;
	while (scanf("%d%d", &N, &M), ~N && ~M) {
		memset(p, 0, sizeof p);
		memset(w, 0, sizeof w);
		memset(f, 0, sizeof f); L = 0;
		for (i = 1; i <= N; i++) {
			scanf("%d", &x); l = 0;
			while (!(x & 1)) x >>= 1, l++;
			a[l][++p[l]] = x; w[l] += x; scanf("%d", &b[l][p[l]]);
			L = max(L, l);
		}
		for (i = 0; i <= L; i++)
			for (j = 1; j <= p[i]; j++)
				for (k = w[i]; k >= a[i][j]; k--)
					f[i][k] = max(f[i][k], f[i][k - a[i][j]] + b[i][j]);
		while (M >> L) L++; L--;
		for (i = 1; i <= L; i++) {
			w[i] += (w[i - 1] + 1) >> 1;
			for (j = w[i]; ~j; j--)
				for (k = 0; k <= j; k++)
					f[i][j] = max(f[i][j], f[i][j - k] + f[i - 1][min(w[i - 1], (k << 1) | ((M >> (i - 1)) & 1))]);
		}
		printf("%d\n", f[L][1]);
	}
	return 0;
}
