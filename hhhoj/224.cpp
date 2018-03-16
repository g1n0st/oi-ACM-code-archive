#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef unsigned long long ULL;
const int N = 20;
const int tx[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int ty[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
int t[N][N], s[N], vis[N][N], top, L;
ULL ans;
unordered_map<ULL, int> M;
void dfs1(int x, int y, int w, ULL state) {
	if (x < 0 || y < 0 || x >= 8 || y >= 8 || s[w] != t[x][y] || vis[x][y]) return;
	if (w ^ top) state |= 1ULL << (x * 8 + y);
	if (!w) {
		for (ULL s = state; ; s = (s - 1) & state) {
			M[s] += __builtin_popcountll(s) & 1 ? -1 : 1;
			if (!s) return;
		}
		return;
	}
	vis[x][y] = 1;
	for (int i = 0; i < 8; i++) dfs1(x + tx[i], y + ty[i], w - 1, state);
	vis[x][y] = 0;
}
void dfs2(int x, int y, int w, ULL state) {
	if (x < 0 || y < 0 || x >= 8 || y >= 8 || s[w] != t[x][y] || vis[x][y]) return;
	if (w ^ top) state |= 1ULL << (x * 8 + y);
	if (w == L - 1) {
		for (ULL s = state; ; s = (s - 1) & state) {
			ans += M[s]; if (!s) return;
		}
		return;
	}
	vis[x][y] = 1;
	for (int i = 0; i < 8; i++) dfs2(x + tx[i], y + ty[i], w + 1, state);
	vis[x][y] = 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d", &L); getchar();
	for (int i = 0; i < L; i++) s[i] = getchar(); getchar();
	for (int i = 0; i < 8; i++, getchar())
		for (int j = 0; j < 8; j++) t[i][j] = getchar();
	top = L / 2;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (t[i][j] == s[top]) {
				M.clear(); dfs1(i, j, top, 0); dfs2(i, j, top, 0);
			}
	cout << ans << endl;
	return 0;
}
