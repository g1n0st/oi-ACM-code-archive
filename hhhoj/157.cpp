#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int V = 1000100;
typedef pair<int, int> pl;
vector<int> G[V];
vector<pl> e;
int N, M, deg[V], f[V];
void Read(int &x) {
	scanf("%d", &x);
}
void Dfs(int x) {
	for (auto ei : G[x]) {
		if (~f[ei]) continue;
		auto ne = e[ei];
		if (ne.first == x) {
			f[ei] = 0; Dfs(ne.second);
		} else {
			f[ei] = 1; Dfs(ne.first);
		}
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x, y;
	Read(N); Read(M);
	for (i = 1; i <= M; i++) {
		Read(x); Read(y);
		e.emplace_back(pl(x, y));
		G[x].emplace_back(e.size() - 1);
		G[y].emplace_back(e.size() - 1);
		deg[x]++; deg[y]++;
	}
	int lst = 0, tot = 0;
	for (i = 1; i <= N; i++) 
		if (deg[i] & 1) {
			if (lst) {
				e.emplace_back(pl(lst, i));
				G[lst].emplace_back(e.size() - 1);
				G[i].emplace_back(e.size() - 1);
				lst = 0; ++tot;
			} else lst = i;
		}
	memset(f, -1, sizeof f);
	printf("%d\n", N - tot * 2);
	for (i = 1; i <= N; i++) Dfs(i);
	for (i = 0; i < M; i++) putchar('0' + f[i]);
	return 0;
}
