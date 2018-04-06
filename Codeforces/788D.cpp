#include <bits/stdc++.h>
using namespace std;
const int INF = 100000000;
inline int Ask(int x, int y) {
	printf("0 %d %d\n", x, y);
	fflush(stdout);
	scanf("%d", &x);
	return x;
}

vector<int> G, a1, a2;
void Work(int x, int y) {
	if (x > y) return ;
	int mid = (x + y) >> 1;
	int res = Ask(mid, mid);
	if (!res) {
		G.emplace_back(mid); res = 1;
	}
	Work(x, mid - res); Work(mid + res, y);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Work(-INF, INF);
	int pos = INF;
	sort(G.begin(), G.end());
	for (int i = 0; i < G.size() - 1; i++)
		if (G[i] + 1 != G[i + 1]) pos = G[i] + 1;
	for (auto v : G) {
		if (!Ask(v, pos)) a1.emplace_back(v);
		if (!Ask(pos, v)) a2.emplace_back(v);
	}
	printf("1 %d %d\n", a1.size(), a2.size());
	for (auto v : a1) printf("%d ", v); putchar('\n');
	for (auto v : a2) printf("%d ", v); putchar('\n');
	fflush(stdout);
	return 0;
}
