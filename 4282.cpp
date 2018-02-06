#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
int n, cnt, tot, a[V], b[V];
int cal(int x) {
	int l = 0, r = tot, mid, ret;
	while (l <= r) {
		if (b[mid = (l + r) >> 1] < x) l = (ret = mid) + 1;
		else r = mid - 1;
	}
	return ret;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d", &n);
	char s[10]; int x;
	for (int i = 1; i <= n; i++) {
		scanf("%s", s);
		if (s[0] == 'K') scanf("%d", &x), a[++tot] = x - cnt;
		else cnt++;
	}
	memset(b, 0x3f, sizeof b); b[0] = -b[0];
	int ans = 0;
	for (int i = 1; i <= tot; i++) {
		int p = cal(a[i]);
		ans = max(p + 1, ans); b[p + 1] = a[i];
	}
	ans += cnt;
	cout << ans << endl;
	return 0;
}
