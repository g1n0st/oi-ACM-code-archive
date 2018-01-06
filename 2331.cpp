#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL P = 20110520;
const int V = 200010 + 5;
char s[110];
LL dp[2][V];
int N, M, c, cnt, tot[2], bit[110];
int mp[110][110], S[2][V];
int h[50000];
struct Edge {
	int nxt, v;
} e[V];

void Add(int s, LL v) {
	int u = s % 50000;
	for (int i = h[u]; i; i = e[i].nxt)
		if (S[c][e[i].v] == s) {
			(dp[c][e[i].v] += v) %= P;
			return;
		}
	e[++cnt].v = ++tot[c];
	e[cnt].nxt = h[u]; h[u] = cnt;
	S[c][tot[c]] = s; dp[c][tot[c]] = v % P;
}
void Dp() {
	tot[c] = 1; dp[c][1] = 1;
	int i, j, k, t;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= tot[c]; j++) S[c][j] <<= 2;
		for (j = 1; j <= M; j++) {
			memset(h, 0, sizeof h); cnt = 0; c ^= 1; tot[c] = 0;
			memset(dp[c], 0, sizeof dp[c]);
			for (k = 1; k <= tot[c ^ 1]; k++) {
				int s = S[c ^ 1][k]; LL v = dp[c ^ 1][k];
				if (!v) continue;
				int p = (s >> bit[j - 1]) & 3, q = (s >> bit[j]) & 3;
				if (!mp[i][j]) {
					if (!p && !q) Add(s, v);
				}
				else if (!p && !q) {
					if (mp[i + 1][j]) Add(s + (1 << bit[j - 1]), v);
					if (mp[i][j + 1]) Add(s + (1 << bit[j]), v);
					if (mp[i + 1][j] && mp[i][j + 1])
						Add(s + (1 << (bit[j - 1] + 1)) + (1 << (bit[j] + 1)), v);
				}
				else if (!p) {
					if (q & 1) {
						s -= (1 << bit[j]);
						if (mp[i][j + 1])  Add(s + (1 << bit[j] + 1), v);
						if (mp[i + 1][j]) Add(s + (1 << bit[j - 1]), v);
					}
					else {
						s -= (1 << bit[j] + 1); Add(s, v);
						if (mp[i + 1][j]) Add(s + (1 << bit[j - 1] + 1), v);
					}
				}
				else if (!q) {
					if (p & 1) {
						s -= (1 << bit[j - 1]);
						if (mp[i][j + 1]) Add(s + (1 << bit[j]), v);
						if (mp[i + 1][j]) Add(s + (1 << bit[j - 1] + 1), v);
					}
					else {
						s -= (1 << bit[j - 1] + 1); Add(s, v);
						if (mp[i][j + 1])  Add(s + (1 << bit[j] + 1), v);
					}
				}
				else if (p == 1 && q == 1) Add(s - (1 << bit[j - 1]) - (1 << bit[j]), v);
			}
		}
	}
}
int main() {
	int i, j;
	scanf("%d%d", &N, &M);
	for (i = 0; i <= 100; i++) bit[i] = i << 1;
	if (N >= M) {
		for (i = 1; i <= N; i++) {
			scanf("%s", s + 1);
			for (j = 1; j <= M; j++)
				if (s[j] == '_') mp[i][j] = 1;
		}
	}
	else {
		for (i = 1; i <= N; i++) {
			scanf("%s", s + 1);
			for (j = 1; j <= M; j++)
				if (s[j] == '_') mp[j][i] = 1;
		}
		swap(N, M);
	}
	Dp(); printf("%lld\n", dp[c][1]);
	return 0;

}
