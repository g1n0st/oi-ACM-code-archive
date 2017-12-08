#include <cstdio>
#include <iostream>
using namespace std;
typedef long long LL;
const int V = 3010;
const int P = 1000000007;
LL C[V][V], N, f[V], g[V];
int p[V * V];
void $(LL &x, LL y) {
	(x += (P + y)) %= P;
}
void $(int &x, int y) {
	(x += y) %= P;
}
void Init() {
	int i, j;
	C[0][0] = 1;
	for (i = 1; i <= N; i++) {
		C[i][0] = 1LL;
		for (j = 1; j <= i; j++)
			$(C[i][j], C[i - 1][j] + C[i - 1][j - 1]);
	}
	p[0] = 1LL; for (i = 1; i <= N * N; i++) $(p[i], p[i - 1] * 2 % P);
	g[0] = 1LL; for (i = 1; i <= N; i++) g[i] = g[i - 1] * (-1);
}
int main() {
	int i, j;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> N; Init();
	f[0] = 1LL;
	for (i = 1; i <= N; i++) 
		for (j = 1; j <= i; j++)
			$(f[i], g[j - 1] * p[j * (i - j)] % P * C[i][j] % P * f[i - j] % P);
	cout << f[N] << endl;
	return 0;
}
