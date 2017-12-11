#include <deque>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int V = 200010;
const int P = 1000000007;
int Max(int a, int b) {
	return a > b ? a : b;
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
		x = x * 10 + c - '0';
		c = get();
	}
}
int N, F[V], pw[V], cnt[V], MxDep;
vector<int> G[V];
deque<int> f[V][3];
void Add(int &x, int y) {
	(x += y) %= P;
}
void Dfs(int u, int d) {
	int i, j;
	++cnt[d]; MxDep = Max(MxDep, d);
	int SZ = 0;
	for (auto v : G[u]) {
		Dfs(v, d + 1);
		if (f[u][0].size() < f[v][0].size())
			for (i = 0; i < 3; i++) swap(f[u][i], f[v][i]);
		int sz = f[v][0].size(); SZ = Max(SZ, sz);
		for (i = 0; i < sz; i++) {
			int tmp[3] = { 0, 0, 0 }, s = 0, t = 0;
			for (j = 0; j < 3; j++) Add(s, f[v][j][i]);
			for (j = 0; j < 3; j++) Add(t, f[u][j][i]);
			Add(tmp[0], 1LL * f[u][0][i] * f[v][0][i] % P);
			Add(tmp[1], 1LL * f[u][1][i] * f[v][0][i] % P);
			Add(tmp[1], 1LL * f[u][0][i] * f[v][1][i] % P);
			Add(tmp[2], 1LL * s * t % P);
			Add(tmp[2], P - tmp[0]);
			Add(tmp[2], P - tmp[1]);
			for (j = 0; j < 3; j++) f[u][j][i] = tmp[j];
		}
		for (i = 0; i < 3; i++) {
			deque<int> emp; f[v][i].swap(emp);
		}
	}
	f[u][0].push_front(1); f[u][1].push_front(1); f[u][2].push_front(0);
	for (i = 0; i <= SZ; i++) {
		Add(f[u][0][i], f[u][2][i]); f[u][2][i] = 0;
	}
}
int main() {
	int i, j;
	Read(N);
	for (pw[0] = 1, i = 1; i <= N; i++) pw[i] = (pw[i - 1] * 2LL) % P;
	for (i = 1; i <= N; i++) {
		Read(F[i]); G[F[i]].emplace_back(i);
	}
	Dfs(0, 0);
	int Ans = 0;
	for (i = 0; i <= MxDep; i++) {
		int v = f[0][1][i]; Add(Ans, 1LL * v * pw[N + 1 - cnt[i]] % P);
	}
	printf("%d\n", Ans);
	return 0;
}
