#include <bits/stdc++.h>
using namespace std;
const int V = 110;
int n, a[V], tot[V], T, ans; char s[V];
void cal(char x, int lst) {
	vector<int> G;
	for (int i = 1; i <= n / 2; i++)
		if (s[i] != s[n - i + 1] && s[i] != x && s[n - i + 1] != x) {
			G.push_back(min(a[i], a[n - i + 1]));
		}
	sort(G.begin(), G.end());
	for (int i = 0; i < lst; i++) ans -= G[i];
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> n >> s + 1;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n / 2; i++) {
		if (s[i] == s[n - i + 1]) {
			tot[s[i] - 'a']++; T++; ans += max(a[i], a[n - i + 1]);
		}
		else {
			ans += a[i] + a[n - i + 1];
		}
	}
	for (int i = 0; i < 26; i++) {
		if (tot[i] * 2 > T) cal(i + 'a', tot[i] * 2 - T);
	}
	cout << ans << endl;
	return 0;
}
