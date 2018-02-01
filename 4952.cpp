#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int V = 2018;
int n, t;
DB d[V], s[V];
bool check(DB x) {
	DB tx = 0;
	for (int i = 1; i <= n; i++){
		DB m = (s[i] + x);
		if (m <= 0) return 0;
		tx += d[i] / m;
	}
	return tx < t;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> n >> t;
	for (int i = 1; i <= n; i++) cin >> d[i] >> s[i];
	DB l = -2000000, r = 2000000, Mid, Ans;
	while (l + 1e-7 < r) check(Mid = (l + r) / 2) ? r = Mid : l = Mid;
	printf("%.9lf\n", l);
	return 0;
}
