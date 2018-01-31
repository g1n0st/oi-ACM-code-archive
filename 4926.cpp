#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N, M, f[5000005], T, Ans;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> N >> M;
	for (int i = 0; i <= M; i++) f[i] = 1;
	for (int i = M + 1; ; i++) {
		f[i] = f[i - 1] + f[i - M];
		if (f[i] > N) {
			T = i; break;
		}
	}
	for (int i = T; i; i--)
		if (f[i] <= N) N -= f[i], Ans += f[i - 1];
	cout << Ans << endl;
	return 0;
}
