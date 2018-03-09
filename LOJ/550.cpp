#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
LL T, n, m, k;
int main() {
	cin >> T;
	while (T--) {
		cin >> n >> m >> k;
		cout << (n * n / 4) * m + (m * m / 4) * n << endl;
	}
	return 0;
}
