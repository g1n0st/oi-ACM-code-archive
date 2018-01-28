#include<bits/stdc++.h>
using namespace std;
int f[2][4210];
int N, P;
int main() {
	int i, j;
	cin >> N >> P;
	f[1][1] = 1;
	for (i = 2; i <= N; i++)
		for (j = 1; j <= i; j++)
			f[i & 1][j] = (f[i & 1][j - 1] + f[(i & 1) ^ 1][i - j]) % P;
	printf("%d\n", f[N & 1][N] * 2 % P);
	return 0;
}
