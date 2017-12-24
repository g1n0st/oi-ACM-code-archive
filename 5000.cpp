#include <bits/stdc++.h>
using namespace std;
const int V = 10010;
int N, K, f[V][30][32], g[V][30][32], L, P;
char s[V * 20];
void Add(int &x, int y) {
	(x += y) %= P;
}
int main() {
	int i, j, k, a, b, c;
	scanf("%d%d", &N, &K);
	for (i = 1; i <= N; i++)
		for (j = 1; j <= K; j++) {
			scanf("%d%d", &a, &b);
			f[i][j][0] = b; g[i][j][0] = a;
		}
	scanf("%s", &s); L = strlen(s);
	scanf("%d", &P);
	for (k = 1; k <= 30; k++)
		for (i = 1; i <= N; i++)
			for (j = 1; j <= K; j++) {
				Add(f[i][j][k], f[i][j][k - 1] + f[g[i][j][k - 1]][j][k - 1]);
				g[i][j][k] = g[g[i][j][k - 1]][j][k - 1];
			}
	int Now = 1, Ans = 0;
	for (k = 0; k < L; k++) {
		if (s[k] == '[') {
			a = 0; k++;
			while (s[k] >= '0' && s[k] <= '9') {
				a = a * 10 + s[k] - '0'; k++;
			}
			b = s[k] - 'A' + 1;
			for (c = 0; a; a >>= 1, c++)
				if (a & 1) {
					Add(Ans, f[Now][b][c]);
					Now = g[Now][b][c];
				}
			k++;
		}
		else {
			b = s[k] - 'A' + 1;
			Add(Ans, f[Now][b][0]);
			Now = g[Now][b][0];
		}
	}
	printf("%d\n", Ans);
	return 0;
}
