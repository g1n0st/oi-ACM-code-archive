#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db eps = 1e-7;
const int V = 110;
struct Mat {
	db a[V][V];
	db Gauss(int n) {
		db det = 1;
		int i, j, k;
		for (i = 1; i < n; i++) {
			int r = i;
			for (j = i; j < n; j++)
				if (fabs(a[j][i]) > fabs(a[r][i])) r = i;
			if (r != i) for (k = 1; k < n; k++) swap(a[i][k], a[r][k]);
			if (-eps < a[i][i] && a[i][i] < eps) return 0;
			for (j = i + 1; j < n; j++) {
				db tmp = -a[j][i] / a[i][i];
				for (k = i; k <= n; k++) a[j][k] += tmp * a[i][k];
			}
			det *= a[i][i];
		}
		return det < 0 ? -det : det;
	}
} m;
int N;
int main() {
	scanf("%d", &N); db pr = 1;
	int i, j;
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++) {
			scanf("%lf", &m.a[i][j]);
			if (m.a[i][j] > 1 - eps) m.a[i][j] -= eps;
			if (i < j) pr *= (1 - m.a[i][j]);
			m.a[i][j] /= (1 - m.a[i][j]);
		}
	for (i = 1; i <= N; i++) {
		db s = 0;
		for (j = 1; j <= N; j++) s += m.a[i][j];
		m.a[i][i] = -s;
	}
	printf("%.8lf\n", m.Gauss(N) * pr);
	return 0;
}
