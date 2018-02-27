#include <bits/stdc++.h>
typedef long long LL;
const int N = 310;
using namespace std;
void Read(int &x) {
	scanf("%d", &x);
}
void Max(LL &a, LL b) {
	a = max(a, b);
}
LL f[N][N][N];
int n, K, w[N], c[N];
char s[N];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K); scanf("%s", s + 1);
	for (int i = 0; i < (1 << K); i++) Read(c[i]), Read(w[i]);
	memset(f, 0xc0, sizeof f);
	for (int i = 1; i <= n; i++) f[i][i][s[i] - '0'] = 0;
	for (int l = 2; l <= n; l++) 
		for (int i = 1; i + l - 1 <= n; i++) {
			int j = i + l - 1, len = j - i;
			while (len > K - 1) len -= K - 1;
			for (int m = j; m > i; m -= (K - 1))
				for (int z = 0; z < (1 << len); z++) {
					Max(f[i][j][z << 1], f[i][m - 1][z] + f[m][j][0]);
					Max(f[i][j][z << 1 | 1], f[i][m - 1][z] + f[m][j][1]);
				}
			if (len == K - 1) {
				LL g[2]; memset(g, 0xc0, sizeof g);
				for (int z = 0; z < (1 << K); z++) Max(g[c[z]], f[i][j][z] + w[z]);
				Max(f[i][j][0], g[0]); Max(f[i][j][1], g[1]);
			}
	}
	LL ans = 0;
	for (int i = 0; i < (1 << K); i++) Max(ans, f[1][n][i]);
	cout << ans << endl;
	return 0;
}
