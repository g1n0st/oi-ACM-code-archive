#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
bool judge1(LL n) {
	return n >= 4;
}
bool judge2(LL n) {
	return (n >= 4) && (n % 2 == 0);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	LL T, n;
	cin >> T;
	while (T--) {
		cin >> n;
		puts(judge1(n) ? "Yes" : "No");
		puts(judge2(n) ? "Yes" : "No");
	}
}
