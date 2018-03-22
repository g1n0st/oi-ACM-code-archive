#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 300010;
void Read(int &x) {
	scanf("%d", &x);
}
int n, a[V];
LL ans, f[V];
LL dfs(int x) {
	if (!x) return 0;
	if (~f[x]) return f[x];
	f[x] = 1LL << 60;
	for (int i = 1; i <= n; i++) f[x] = min(f[x], dfs(x & a[i]) + (x & a[i]));
	return f[x];
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); int K = (1 << 18) - 1, tK = K;
	for (int i = 1; i <= n; i++) {
		Read(a[i]); K &= a[i];
	}
	for (int i = 1; i < (1 << 18); i <<= 1)
		if (K & i) {
			ans += (LL)i * n;
		}
	memset(f, -1, sizeof f);
	cout << ans + dfs(tK - K) << endl;
	return 0;
}
