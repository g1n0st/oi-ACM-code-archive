#include <bits/stdc++.h>
using namespace std;
const int V = 110;
typedef long long LL;
const LL P = 1e9 + 7;
char mp[V][V];
int N, M;
LL g[V][V];
LL Gauss(int n) {
    LL Det = 1; int f = 1;
    int i, j, k;
    for (i = 1; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            LL x = g[i][i], y = g[j][i];
            while (y) {
                LL t = x / y; x %= y; swap(x, y);
                for (k = i; k < n; k++)
                    g[i][k] = (g[i][k] - t * g[j][k] % P + P) % P;
                for (k = i; k < n; k++)
                    swap(g[i][k], g[j][k]);
                f = -f;
            }
        }
        if (!g[i][i]) return 0;
        Det = Det * g[i][i] % P;
    }
    if (f == -1) Det = (P - Det) % P;
    return Det;
}
int main() {
    int i, j, k;
    scanf("%d", &N);
    for (i = 1; i <= N; i++) scanf("%s", mp[i] + 1);
    for (i = 1; i <= N; i++)
			for (j = 1; j <= N; j++)
				if (mp[i][j] == '1') {
					g[N - i + 1][N - j + 1] = (P - 1);
					g[N - j + 1][N - j + 1]++;
				}
		
    printf("%lld\n", Gauss(N));
    return 0;
}
