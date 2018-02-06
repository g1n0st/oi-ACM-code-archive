#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 130, M = 26000;
int n, k[N], c[N], mx;
LL m, f[N][M];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> k[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1; i <= n; i++) mx += k[i] * c[i];
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= mx; j++) {
			f[i][j] = f[i - 1][j];
			for (int p = 1; p <= k[i]; p++) {
				if (j - p * c[i] < 0) break;
				f[i][j] = min(m, max(f[i][j], f[i - 1][j - p * c[i]] * (LL)p));
			}
			}
	int r = 0;
	for (;  r <= mx; r++) if (f[n][r] == m) break;
	cout << r << endl;
	return 0;
}
