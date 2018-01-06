#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 2e5 + 5;
char s[20];
LL Ans, dp[2][V];
int N, M, c, cnt, ex, ey, tot[2], bit[20];
int mp[20][20], S[2][V];
int h[V];
struct Edge {
	int nxt, v;
} e[V];

void Add(int s, LL v) {
	int u = s % V;
	for (int i = h[u]; i; i = e[i].nxt)
		if (S[c][e[i].v] == s) {
			dp[c][e[i].v] += v;
			return;
		}
	e[++cnt].v = ++tot[c];
	e[cnt].nxt = h[u]; h[u] = cnt;
	S[c][tot[c]] = s; dp[c][tot[c]] = v;
}
void Dp() {
	tot[0] = 1; dp[c][1] = 1;
	int i, j, k, t;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= tot[c]; j++) S[c][j] <<= 2;
		for (j = 1; j <= M; j++) {
			memset(h, 0, sizeof h); cnt = 0; c ^= 1; tot[c] = 0;
			for (k = 1; k <= tot[c ^ 1]; k++) {
				int s = S[c ^ 1][k]; LL v = dp[c ^ 1][k];
				int p = (s >> bit[j - 1]) & 3, q = (s >> bit[j]) & 3;
				if (!mp[i][j]) { 
					if (!p && !q) Add(s, v);
				}
				else if (!p && !q) {
					if (!mp[i + 1][j] || !mp[i][j + 1]) continue;
					Add(s + (1 << bit[j - 1]) + (1 << (bit[j] + 1)), v);
				}
				else if (!p && q) {
					if (mp[i][j + 1]) Add(s, v);
					if (mp[i + 1][j]) Add(s + (1 << bit[j - 1]) * q - (1 << bit[j]) * q, v);
				}
				else if (p && !q) {
					if (mp[i + 1][j]) Add(s, v);
					if (mp[i][j + 1]) Add(s + (1 << bit[j]) * p - (1 << bit[j - 1]) * p, v);
				}
				else if (p + q == 2) {
					int b = 1;
					for (t = j + 1; t <= M; t++) {
						int p = (s >> bit[t]) & 3;
						if (p == 1) b++; if (p == 2) b--;
						if (!b) {
							s -= (1 << bit[t]);
							break;
						}
					}
					Add(s - (1 << bit[j - 1]) - (1 << bit[j]), v);
				}
				else if (p + q == 4) {
					int b = 1;
					for (t = j - 2; ~t; t--) {
						int p = (s >> bit[t]) & 3;
						if (p == 2) b++; if (p == 1) b--;
						if (!b) {
							s += (1 << bit[t]);
							break;
						}
					}
					Add(s - (1 << (bit[j - 1] + 1)) - (1 << (bit[j] + 1)), v);
				}
				else if (p == 2 && q == 1) Add(s - (1 << (bit[j - 1] + 1)) - (1 << bit[j]), v);
				else if (p == 1 && q == 2)
					if (i == ex && j == ey) Ans += v;
			}
		}
	}
}
int main() {
	int i, j;
	scanf("%d%d", &N, &M);
	for (i = 0; i < 26; i++) bit[i] = i << 1;
	for (i = 1; i <= N; i++) {
		scanf("%s", s + 1);
		for (j = 1; j <= M; j++)
			if (s[j] == '.') mp[i][j] = 1, ex = i, ey = j;
	}
	Dp(); printf("%lld\n", Ans);
	return 0;
}
