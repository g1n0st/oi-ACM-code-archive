#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const int V = 100000;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
const int N = 1100;
int f[2][N][N], n, m;
int U[N][N], L[N][N], R[N][N], D[N][N];
LL ans;
namespace Bit {
	int n, a[N];
	void add(int x) {
		for (; x; x -= x & -x) a[x]++;
	}
	int query(int x) {
		int r = 0;
		for (; x <= n; x += x & -x) r += a[x];
		return r;
	}
	void clear() {
		for (int i = 1; i <= n; i++) a[i] = 0;
	}
}
vector<PI> G[N];
void Solve(int x, int y) {
	Bit::clear();
	for (int i = 1; i <= Bit::n; i++) G[i].clear();
	int tx = x, ty = y, p = 2;
	while (tx <= n && ty <= m) {
		G[p - 1].emplace_back(PI(p, 1));
		G[p - min(U[tx][ty], L[tx][ty]) - 1].emplace_back(PI(p, -1));
		++tx; ++ty; ++p;
	}
	tx = x; ty = y; p = 2;
	while (tx <= n && ty <= m) {
		Bit::add(p + min(D[tx][ty], R[tx][ty]));
		for (auto e : G[p]) ans += e.second * Bit::query(e.first);
		++tx; ++ty; ++p;
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Bit::n = max(n, m) + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m - 1; j++) Read(f[0][i][j]);
	for (int i = 1; i <= n - 1; i++)
		for (int j = 1; j <= m; j++) Read(f[1][i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 2; j <= m; j++) L[i][j] = f[0][i][j - 1] ? L[i][j - 1] + 1 : 0;
	for (int i = 1; i <= n; i++)
		for (int j = m - 1; j; j--) R[i][j] = f[0][i][j] ? R[i][j + 1] + 1 : 0;
	for (int j = 1; j <= m; j++)
		for (int i = 2; i <= n; i++) U[i][j] = f[1][i - 1][j] ? U[i - 1][j] + 1 : 0;
	for (int j = 1; j <= m; j++)
		for (int i = n - 1; i; i--) D[i][j] = f[1][i][j] ? D[i + 1][j] + 1 : 0;
	for (int i = 1; i <= n; i++) Solve(i, 1);
	for (int i = 2; i <= m; i++) Solve(1, i);
	cout << ans << endl;
	return 0;
}
