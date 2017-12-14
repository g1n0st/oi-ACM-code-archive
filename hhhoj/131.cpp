#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
const int V = 1000010;
using namespace std;
typedef pair<int, int> pl;
int Max(int a, int b) {
	return a > b ? a : b;
}
int Min(int a, int b) {
	return a < b ? a : b;
}
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
int N, a[V], b[V], pa[V], pb[V];
map<pl, int> f;
vector<int> p[2 * V];
int Dfs(int x, int y) {
	if (x == N) return N - y;
	if (y == N) return N - x;
	if (f.count(pl(x, y))) return f[pl(x, y)];
	vector<int>::iterator it = upper_bound(p[x - y + N].begin(), p[x - y + N].end(), x);
	if (it == p[x - y + N].end()) return (f[pl(x, y)] = Max(N - x, N - y));
	int l = *it - 1 - x, tx = x + l, ty = y + l;
	return (f[pl(x, y)] = Min(Dfs(tx + 1, ty), Dfs(tx, ty + 1)) + l + 1);
}
int main() {
	int i, j;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]); pa[a[i]] = i;
	}
	for (i = 1; i <= N; i++) {
		Read(b[i]); pb[b[i]] = i;
	}
	for (i = 1; i <= N; i++) p[pa[i] - pb[i] + N].emplace_back(pa[i]);
	for (i = 0; i <= 2 * N; i++) sort(p[i].begin(), p[i].end());
	printf("%d\n", Dfs(0, 0));
	return 0;
}
