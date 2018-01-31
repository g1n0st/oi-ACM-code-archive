#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 998244353;
int N, M;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> N;
	for (int i = 1, x; i <= N; i++) {
		cin >> x; M += x;
	}
	int Ans = 1;
	for (int i = 1; i <= M; i++) {
		if (i == M - N + 1) continue;
		Ans = (LL)Ans * i % P;
	}
	cout << Ans << endl;
	return 0;
}
