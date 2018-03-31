#include <bits/stdc++.h>
using namespace std;
int T, n;
void Read(int &x) {
	scanf("%d", &x);
}
int main() {
	//freopen("in.txt", "r", stdin);
	Read(T);
	while (T--) {
		Read(n); int ans = 0;
		for (int i = 30; ~i; i--) {
			int t = (1 << i), f = n / t;
			ans += f * (t - 1); n -= t * f;
		}
		cout << ans << endl;
	}
	return 0;
}
