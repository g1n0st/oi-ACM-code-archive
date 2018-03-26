#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int P = 998244353;

map<vector<int>, int> f[N];
map<vector<int>, bool> g[N];

int n, m;
vector<int> s, t;
int dfs(vector<int> a, int step) {
	if (g[step][a]) return f[step][a];
	g[step][a] = 1; bool flg = 1;
	for (int i = 0; i < n; i++) if (a[i] ^ t[i]) {
		flg = 0; break;
	}
	int ans = 0, pos[3] = { 0, 0, 0 };
	if (flg) ans++;
	if (step == m) return f[step][a] = ans;
	for (int i = 0; i < n; i++) if (!pos[a[i] - 1]) {
		pos[a[i] - 1] = i + 1; int p = a[i];
		for (int j = 1; j <= 3; j++) if (j ^ p && !pos[j - 1]) {
			a[i] = j;
			ans = (ans + dfs(a, step + 1)) % P;
			a[i] = p;
		}
	}
	return f[step][a] = ans;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> n >> m;
	int x;
	for (int i = 1; i <= n; i++) {
		cin >> x; s.emplace_back(x);
	}
	for (int i = 1; i <= n; i++) {
		cin >> x; t.emplace_back(x);
	}
	cout << dfs(s, 0) << endl;
	return 0;
}
