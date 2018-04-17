#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL oo = 1LL << 60;

LL T, n, h, x, y, a, b;

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> T;
	while (T--) {
		cin >> n >> h >> x >> y >> a >> b;
		LL X[2] = { x - 1, n - x };
		LL Y[2] = { y - 1, h - y };
		LL ans = oo;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++) {
				if (X[i] % a || Y[j] % b) continue;
				LL a1 = X[i] / a, a2 = Y[j] / b;
				if (abs(a1 - a2) & 1) continue;
				ans = min(ans, max(a1, a2));
			}
		if (ans == oo) cout << -1 << endl;
		else cout << ans << endl;
	}
	return 0;
}
