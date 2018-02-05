#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long U;
typedef long long LL;
const int V = 4000010;
const int base = 13331;
map<U, int> h;
U ha[V], p[V];
string s1[V], s2[V];
U Hash(string s) {
	U r = 0;
	for (int i = 0; i < s.size(); i++)
		r = r * base + s[i] - 'a' + 1;
	return r;
}
U subHash(int l, int r) {
	int len = r - l + 1;
	return ha[r] - ha[l - 1] * p[len];
}
int n, m, l1, l2;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	std::ios::sync_with_stdio(false);
	cin >> n >> m >> l1 >> l2;
	p[0] = 1; for (int i = 1; i <= l1 + l2; i++) p[i] = p[i - 1] * base;
	for (int i = 1; i <= n; i++) cin >> s1[i];
	for (int i = 1; i <= m; i++) cin >> s2[i];
	if (l1 < l2) {
		swap(n, m); swap(s1, s2); swap(l1, l2);
	}
	for (int i = 1; i <= m; i++) h[Hash(s2[i])]++;
	int len = (l1 + l2) / 2;
	LL ans = 0;
	for (int i = 1; i <= n; i++) {
		string &s = s1[i];
		for (int j = 0; j < len * 2; j++)
			ha[j + 1] = ha[j] * base + s[j % len] - 'a' + 1;
		U x = 0;
		for (int j = len; j < l1; j++)
			x = x * base + s[j] - 'a' + 1;
		for (int j = 1; j <= len; j++) {
			U y = subHash(j, j + l1 - len - 1);
			if (x == y) ans += h[subHash(j + l1 - len, j + len - 1)];
		}
	}
	cout << ans << endl;
	return 0;
}
