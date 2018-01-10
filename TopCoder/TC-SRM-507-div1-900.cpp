#line 5 "CubeBuilding.cpp"  
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;
const int P = 1000000007;
typedef long long LL;
class CubeBuilding {
public:
	LL C[110][110];
	void Add(LL &x, LL y) {
		(x += y) %= P;
	}
	void initC(int n) {
		int i, j;
		memset(C, 0, sizeof C);
		C[0][0] = 1;
		for (i = 1; i <= n; i++) {
			C[i][0] = 1;
			for (j = 1; j <= i; j++) 
				Add(C[i][j], C[i - 1][j] + C[i - 1][j - 1]);
		}
	}
	int N;
	LL a[26][76][26][2];
	void GetA() {
		memset(a, 0, sizeof a);
		for (int i = 0; i < 26; i++) a[0][0][i][1] = 1;
		for (int n = 1; n <= N; n++)
			for (int t = 0; t < 76; t++)
				for (int mx = 0; mx < 26; mx++)
					for (int d = 0; d < 2; d++) {
						LL &r = a[n][t][mx][d];
						for (int u = 0; u <= mx && u <= t; u++)
							Add(r, a[n - 1][t - u][mx][(u == mx) | d]);
					}
	}
	LL g[26][51];
	void GetG() {
		memset(g, 0, sizeof g);
		for (int y = 0; y < 26; y++)
			for (int n = 0; n < 51; n++) {
				LL &r = g[y][n];
				for (int mx = 0; mx <= y; mx++)
					Add(r, 1LL * a[N][y + n][mx][0] * C[y + n - mx][n] % P);
			}
	}
	LL f[26][26][51];
	void GetF() {
		memset(f, 0, sizeof f);
		f[0][0][0] = 1;
		for (int i = 1; i <= N; i++)
			for (int y = 0; y < 26; y++)
				for (int n = 0; n < 51; n++) {
					LL &r = f[i][y][n];
					for (int ly = 0; ly <= y; ly++)
						for (int ln = 0; ln <= n; ln++)
							Add(r, 1LL * f[i - 1][y - ly][n - ln] * g[ly][ln] % P);
				}
	}
	int getCount(int R, int G, int B, int N) {
		//$CARETPOSITION$  
		this->N = N;
		initC(100); GetA(); GetG(); GetF();
		LL Ans = 0;
		Add(Ans, 1LL * f[N][R][G + B] * C[G + B][B] % P);
		Add(Ans, 1LL * f[N][G][R + B] * C[R + B][R] % P);
		Add(Ans, 1LL * f[N][B][R + G] * C[R + G][G] % P);
		return (int)(Ans % P);
	}
};
