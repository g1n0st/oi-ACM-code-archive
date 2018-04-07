#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL n;
// A006520
// sum of A006519 (lowbit)
LL f(LL n) {
	if (n == 1) return 1;
	return 2 * f(n / 2) + (n - n / 2);
}
int main() {
	//freopen("in.txt", "r", stdin);
	cin >> n;
	cout << f(n - 1) << endl;
	return 0;
}
