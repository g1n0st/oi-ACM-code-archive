#include <bits/stdc++.h>
using namespace std;
const int V = 21;
void Read(int &x) {
	scanf("%d", &x);
}
int N, M, R, Mn, a[V], b[V], c[V], cnt[1 << V], Ans[V];
int op(int x, int a) {
	return (x ^ (x << 1) ^ (x >> 1) ^ a) & R;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x;
	Read(N); Read(M); R = (1 << M) - 1;
	for (i = 1; i <= N; i++) 
		for (j = 1; j <= M; j++) {
			scanf("%d", &x); a[i] = a[i] << 1 | x;
	}
	for (i = 1; i <= R; i++) cnt[i] = cnt[i - (i & -i)] + 1;
	Mn = 1 << 30;
	for (i = 0; i <= R; i++) {
		b[1] = i; c[1] = op(i, a[1]);
		for (j = 2; j <= N; j++) {
			b[j] = c[j - 1]; c[j] = op(b[j], b[j - 1] ^ a[j]);
		}
		if (!c[N]) {
			int tmp = 0;
			for (j = 1; j <= N; j++) tmp += cnt[b[j]];
			if (tmp < Mn) {
				Mn = tmp;
				for (j = 1; j <= N; j++) Ans[j] = b[j];
			}
		}
	}
	if (Mn == 1 << 30) {
		printf("IMPOSSlBLE\n");
		return 0;
	}
	for (i = 1; i <= N; i++)
		for (j = M - 1; ~j; j--)
			printf("%d%c", (Ans[i] >> j) & 1, j ? ' ' : '\n');
	return 0;
}
