#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
void Read(int &x) {
	scanf("%d", &x);
}
int pri[V], tot, vis[V];
void Pre(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) pri[++tot] = i;
		for (int j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[i * pri[j]] = 1; if (i % pri[j] == 0) break;
		}
	}
}
int n;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Pre(n);
	int i = 1, j = tot, ans = 0;
	while (i <= j) {
		ans++;
		if (pri[i] * pri[j] <= n) i++, j--;
		else j--;
	}
	cout << ans << endl;
	return 0;
}
