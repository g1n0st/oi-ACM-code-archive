#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL a, b, c;
LL gcd(LL x, LL y) {
	return !y ? x : gcd(y, x % y);
}
LL lcm(LL x, LL y) {
	return x / gcd(x, y) * y;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> a >> b >> c;
	cout << lcm(a, lcm(b, c)) << endl;
	return 0;
}
