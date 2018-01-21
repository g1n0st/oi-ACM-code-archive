#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1010;
const int P = 1000000007;
void Read(int &x) {
	scanf("%d", &x);
}
int Ksm(int x, LL y = P - 2) {
	int r = 1;
	if (y < 0) y += (P - 1);
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1;
		if (y) x = (LL)x * x % P;
	}
	return r;
}
int sum[V], mat[V][V], A[V], B[V];
void Pre(int d) {
	int i, j, k, t;
	for (i = 1; i <= d + 2; i++) {
		sum[i] = (Ksm(i, d) + sum[i - 1]) % P;
		mat[i - 1][d + 2] = sum[i]; mat[i - 1][0] = 1;
		for (j = 1; j <= d + 1; j++) mat[i - 1][j] = (LL)mat[i - 1][j - 1] * i % P;
	}
	for (i = 0; i <= d + 1; i++) {
		for (j = i; j <= d + 1; j++) if (mat[j][i]) break;
		if (i ^ j) for (k = 0; k <= d + 2; k++) swap(mat[i][k], mat[j][k]);
		for (j = 0; j <= d + 1; j++)
			if (i ^ j && mat[j][i]) {
				t = (LL)mat[j][i] * Ksm(mat[i][i]) % P;
				for (k = 0; k <= d + 2; k++) mat[j][k] = ((LL)mat[j][k] - (LL)t * mat[i][k] % P + P) % P;
			}
	}
	for (i = 0; i <= d + 1; i++) A[i] = (LL)mat[i][d + 2] * Ksm(mat[i][i]) % P;
}
int D, W;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(D); Read(W); Pre(D);
	int i, p, a;
	for (i = 0; i <= D + 1; i++) B[i] = 1;
	while (W--) {
		Read(p); Read(a);
		for (i = 0; i <= D + 1; i++) 
			B[i] = (LL)B[i] * Ksm(p, (LL)a * i % (P - 1)) % P * (1LL + P - Ksm(p, D - i)) % P;
	}
	int Ans = 0;
	for (i = 1; i <= D + 1; i++) Ans = (Ans + (LL)A[i] * B[i] % P) % P;
	printf("%d\n", Ans);
	return 0;
}
