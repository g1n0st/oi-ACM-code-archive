#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
void Read(int &x) {
	scanf("%d", &x);
}
struct P {
	int x, y;
	P(int x = 0, int y = 0) : x(x), y(y) {}
};
vector<P> G, R;
int inLine(P a, P b, P c) {
	if (a.x == b.x) return c.x == a.x;
	if (a.y == b.y) return c.y == a.y;
	int u1 = a.x - b.x, d1 = a.y - b.y;
	int u2 = c.x - b.x, d2 = c.y - b.y;
	return (LL)u1 * d2 == (LL)u2 * d1;
}
int Solve(P a, P b) {
	R.clear();
	for (auto v : G)
		if (!inLine(a, b, v)) R.emplace_back(v);
	if (R.size() <= 2) return 1;
	for (auto v : R)
		if (!inLine(R[0], R[1], v)) return 0;
	return 1;
}
int n;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	int x, y;
	for (int i = 0; i < n; i++) {
		Read(x); Read(y); G.emplace_back(P(x, y));
	}
	if (n <= 3) puts("YES");
	else if (
		Solve(G[0], G[1]) ||
		Solve(G[1], G[2]) ||
		Solve(G[0], G[2])) puts("YES");
	else puts("NO");
	return 0;
}
