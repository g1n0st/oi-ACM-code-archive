#include <bits/stdc++.h>
using namespace std;
const int P = 998244353;
typedef long long LL;
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
int n;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> n;
	cout << (LL)4 * Ksm(3, n - 1) % P << endl;
	for (int i = 1; i <= n; i++) puts("A 0 0 0 0");
	return 0;
}
