#include <cstdio>
typedef long long LL;
const int V = 200010;
using namespace std;
LL f[V][2][2][2], Ans;
int N, M; char s[V];
int Max(int a, int b) {
	return a > b ? a : b;
}
int main() {
	int i, j, k, l, t, X, Y, Z;
	scanf("%d%d\n%s", &N, &M, &s);
	f[1][1][1][1] = 1;
	if (s[0] == s[1]) f[1][1][0][0] = M - 1;
	else {
		f[1][1][0][1] = 1; f[1][1][0][0] = M - 2;
	}
	for (i = 1; i < N; i++)
			for (k = 0; k < 2; k++)
				for (l = 0; l < 2; l++)
						for (t = 0; t < 2; t++)
							if (f[i][k][l][t])
								for (j = 1; j <= M; j++) {
									X = i + l - 1;
									if (j == s[i - 1] - 'a' + 1) X = Max(X, k + i - 1);
									Y = i + t - 1;
									if (j == s[i - 1] - 'a' + 1) Y = Max(Y, k + i - 1);
									if (j == s[i] - 'a' + 1) Y = Max(Y, l + i);
									Z = Y;
									if (j == s[i + 1] - 'a' + 1) Z = Max(Z, Max(l + i, t + i));
									X -= (i - 1); Y -= i; Z -= i;
									if (X >= 0 && Y >= 0 && Z >= 0) f[i + 1][X][Y][Z] += f[i][k][l][t];
	}
	for (k = 0; k < 2; k++)
		for (t = 0; t < 2; t++)
			Ans += f[N][k][0][t];
	printf("%lld\n", Ans);
	return 0;
}
