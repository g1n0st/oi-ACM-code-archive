#include <bits/stdc++.h>
using namespace std;

int n, K;
int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	cin >> n >> K;

	for (int i = 1; i < K; i++) cout << i << ' ' << 0 << endl;

	n -= K - 1;
	if (n == 1) cout << K << ' ' << 0 << endl;
	else cout << n << ' ' << 1 << endl;
	return 0;
}
