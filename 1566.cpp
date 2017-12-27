#include <bits/stdc++.h>
using namespace std;
const int V = 510;
const int P = 1024523;
int N, M, f[2][V][V];
char s1[V], s2[V];
void Add(int &x, int y) {
	(x += y) %= P;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, k;
	scanf("%d%d", &N, &M);
	scanf("%s%s", s1 + 1, s2 + 1);
	reverse(s1 + 1, s1 + 1 + N);
	reverse(s2 + 1, s2 + 1 + M);
	f[0][0][0] = 1; 
	for (i = 0; i < N + M; i++) {
		int o = i & 1;
		for (j = 0; j <= N && j <= i; j++)
			for (k = 0; k <= N && j <= i; k++)
				if (f[o][j][k]) {
					if (s1[j + 1] == s2[i - k + 1]) Add(f[o ^ 1][j + 1][k], f[o][j][k]);
					if (s2[i - j + 1] == s1[k + 1]) Add(f[o ^ 1][j][k + 1], f[o][j][k]);
					if (s2[i - j + 1] == s2[i - k + 1]) Add(f[o ^ 1][j][k], f[o][j][k]);
					if (s1[j + 1] == s1[k + 1]) Add(f[o ^ 1][j + 1][k + 1], f[o][j][k]);
					f[o][j][k] = 0;
				}
	}
	printf("%d\n", f[(N + M) & 1][N][N]);
	return 0;
}
