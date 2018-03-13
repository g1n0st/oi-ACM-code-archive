#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
typedef pair<int, int> PI;
void Read(int &x) {
	scanf("%d", &x);
}
bool cmp(PI a, PI b) {
	if (a.first == b.first) return a.second < b.second;
	else return a.first > b.first;
}
PI a[V]; int n, f[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int x; Read(n);
	for (int i = 1; i <= n; i++) {
		Read(x); a[i] = PI(x, i);
	}
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; i++) f[a[i].second] = n - i + 1;
	for (int i = 1; i <= n; i++) printf("%d ", f[i]);
	return 0;
}
