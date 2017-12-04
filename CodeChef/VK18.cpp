#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 2000010;
int N, T;
LL a[V], pp[V], ss[V], suf[V];
int Abs(int a) {
	return a < 0 ? -a : a;
}
void Read(int &x) {
	scanf("%d", &x);
}
void Solve() {
	Read(N);
	LL Ans = pp[N + 1];
	int M = 2 * N + 1;
	LL t = ss[N + 2] - ss[M];
	LL x = 2000001 - M;
	t -= x * (suf[N + 2] - suf[M]);
	cout << Ans + t << endl;
}
int Calc(int x) {
	int a[2] = {0, 0};
	while (x) {
		a[x % 2] += x % 10;
		x /= 10;;
	}
	return Abs(a[0] - a[1]);
}
void Init(int n) {
	int i, j;
	for (i = 2; i <= n; i++) a[i] = Calc(i);
	for (i = 2; i <= n; i++) pp[i] = pp[i - 1] + (i - 1) * a[i];
	for (i = n; i; i--) ss[i] = ss[i + 1] + (n - i + 1) * a[i];
	for (i = n; i; i--) suf[i] = suf[i + 1] + a[i];
}
int main(void) {
	//freopen("in.txt", "r", stdin);
	Read(T); Init(2000000);
	while (T--) Solve();
}
