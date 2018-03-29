#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1 << 20;
const int P = 998244353;
const int N = 20;
void Read(int &x) {
	scanf("%d", &x);
}
int n, m, e[N], cnt; LL ans;
int cir[V][N], cb[V], fb[V], b[V], f[V], d[N];
void Pre(int n) {
	b[0] = 1; for (int i = 1; i <= n; i++) b[i] = b[i - 1] << 1;
	for (int i = 1; i < b[n]; i++) {
		for (int j = i; j; j &= j - 1) cb[i]++;
		for (int j = i & -i; j > 1; j >>= 1) fb[i]++;
	}
}
inline void Add(int &x, int y) {
	x += y; while (x < 0) x += P; while (x >= P) x -= P;
}
void dfs(int x, int s, int t) {
	if(!t) return;
	if (x == n) {
		Add(f[s], t); ans = (ans - ((LL)t << cnt)) % P;
		return;
	}
	dfs(x+ 1, s, t);
	if ((~s) >> x & 1) dfs(x + 1, s | 1 << x, (LL)-t * d[x] % P);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Pre(n);
	int x, y;
	for (int i = 1; i <= m; i++) {
		Read(x); Read(y); --x; --y;
		if (x > y) swap(x, y);
		e[x] |= b[y]; e[y] |= b[x];
		cir[b[x] | b[y]][y]++;
	}
	for (int i = 1; i < b[n]; i++)
		for (int j = 0; j < n; j++)
			if (cir[i][j])
			for (int k = fb[i] + 1; k < n; k++)
				if (!((i >> k) & 1) && (e[j] >> k & 1)) Add(cir[i | b[k]][k], cir[i][j]);
	for (int i = 0; i < b[n]; i++) 
		if (cb[i] > 2) {
		int cc = 0;
		for (int j = 0; j < n; j++)
			if ((e[fb[i]] >> j) & 1) Add(cc, cir[i][j]);
		if (cc & 1) cc += P; cc >>= 1;
		Add(f[i], cc);
		for (int j = 0; j < n; j++)
			d[j] = cb[e[j] & i];
		cnt = cb[i]; dfs(0, i, -f[i]);
	}
	(ans += P) %= P; cout << ans << endl;
	return 0;
}
