#include <bits/stdc++.h>
using namespace std;
const int P = 1000000007;
const int V = 20;
const int L = 100000;
const int INV2 = (P + 1) >> 1;
const int INV4 = (P + 1) >> 2;
void Read(int &x) {
	scanf("%d", &x);
}
int Mul(int x, int y) {
	return 1LL * x * y % P;
}
void Add(int &x, int y) {
	(x += y) %= P;
}
int N, M;
int u[L], v[L], s[L], cnt, flg[V][V], fir[1 << V];
vector<int> G[V];
map<int, int> f[1 << V];
int main() {
	//freopen("in.txt", "r", stdin);
	int i, j;
	int typ, x, y, x1, y1;
	Read(N); Read(M);
	for (i = 1; i <= M; i++) {
		Read(typ); Read(x); Read(y);
		x--; y--; G[x].push_back(y);
		if (typ) {
			Read(x1); Read(y1);
			x1--; y1--; G[x1].push_back(y1);
			if (x1 == x || y1 == y) continue;
			if (x1 < x) swap(x1, x), swap(y1, y);
			++cnt; u[cnt] = x1; v[cnt] = y1; s[cnt] = (typ & 1) ? 1 : -1;
			flg[x][y] = cnt;
		}
	}
	f[0][0] = 1;
	int S = 1 << N;
	for (i = 0; i < S; i++) {
		if (!(i & 1)) fir[i] = 0;
		else fir[i] = fir[i >> 1] + 1;
	}
	map<int, int>::iterator it;
	int s1, s2;
	for (s1 = 0; s1 < S; s1++) {
		int u = fir[s1];
		for (it = f[s1].begin(); it != f[s1].end(); it++) {
			int s2 = it->first, val = it->second;
			for (int v1 = 0; v1 < G[u].size(); v1++) {
				int v = G[u][v1];
				if ((s2 >> v) & 1) continue;
				Add(f[s1 | (1 << u)][s2 | (1 << v)], Mul(val, INV2));
				if (flg[u][v]) {
					int x = ::u[flg[u][v]], y = ::v[flg[u][v]];
					if ((s1 >> x) & 1) continue;
					if ((s2 >> y) & 1) continue;
					Add(f[s1 | (1 << u) | (1 << x)][s2 | (1 << v) | (1 << y)], (P + s[flg[u][v]] * Mul(val, INV4)) % P);
				}
			}
		}
	}
	int Ans = f[S - 1][S - 1];
	for (i = 1; i <= N; i++) (Ans <<= 1) %= P;
	printf("%d\n", Ans);
	return 0;
}
