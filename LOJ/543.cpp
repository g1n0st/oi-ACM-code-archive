#include <bits/stdc++.h>
using namespace std;
int T, N, K;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	for (cin >> T; T--; ) {
		cin >> N >> K;
		puts(((N + K) & 1) ? "YES" : "NO");
		while (K--) cin >> N >> N >> N;
	}
	return 0;
}
