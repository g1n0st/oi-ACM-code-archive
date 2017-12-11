#include <bits/stdc++.h>
using namespace std;
int N, K, M, c[200010], a[200010], Ans, b[200010];
void Read(int &x) {
	scanf("%d", &x);
}
int Max(int a, int b) {
	return a > b ? a : b;
}
int main() {
	int i, j, x;
	//freopen("in.txt", "r", stdin);
	Read(N); Read(K);
	for (i = 1; i <= N; i++) Read(a[i]);
	sort(a + 1, a + 1 + N);
	for (i = 1; i <= N; i++) {
		if (!c[a[i]]) c[a[i]] = ++M;
		b[c[a[i]]]++;
	}
	sort(b + 1, b + 1 + M);
	for (i = 1; i <= M - K; i++) Ans += b[i];
	cout << Ans << endl;
	return 0;
}
