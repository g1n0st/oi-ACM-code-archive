#include <bits/stdc++.h>
using namespace std;
const int P = 1000000007;
void Read(int &x) {
	scanf("%d", &x);
}
void Add(int &x, int y) {
	(x += y) %= P;
}
const int x5[] = { 1, 5, 25, 125, 625, 3125, 15625, 78125 };
int s[100][10], b[480000][9], N, M, K, T;
int f[2][480000];
void Init() {
	int i, j;
	T = 6;
	for (i = 0; i < M; i++) T *= 5;
	for (i = 0; i < T; i++) {
		int t = i;
		for (j = 0; j < M; j++) b[i][j] = t % 5, t /= 5;
		b[i][M] = t;
	}
}
int main() {
	int i, j, k, x, y;
	Read(N); Read(M); Read(K); Init();
	while (K--) {
		Read(x); Read(y); s[x][y] = 1;
	}
	int pre = 1, now = 0;
	f[now][0] = 1;
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++) {
			swap(now, pre);
			memset(f[now], 0, sizeof f[now]);
			int * h = f[now];
			for (k = 0; k < T; k++) {
				int	v = f[pre][k];
				if (!v || (!j && b[k][M])) continue;
				if (s[i][j]) {
					if (!b[k][M] && !b[k][j]) Add(h[k], v);
					continue;
				}
				int t = k - b[k][M] * x5[M] - b[k][j] * x5[j];
				if (b[k][M] && b[k][j]) {
					int g = 0;
					if (b[k][M] == 5) continue;
					if (b[k][M] == 4) g += 2; else g += 4 - b[k][M];
					if (b[k][j] == 4) g += 2; else g += 4 - b[k][j];
					if (g == 3) Add(h[t], v);
					else if (g < 3) {
						Add(h[t + x5[j]], v); Add(h[t + x5[M]], v);
					}
				}

				else if (b[k][M])
					switch (b[k][M]) {
					case 3:
						Add(h[t + x5[j] + x5[M]], v); Add(h[t + x5[j] * 2], v); Add(h[t + x5[M] * 2], v);
						break;
					case 5: case 2:
						Add(h[t + x5[j]], v); Add(h[t + x5[M]], v);
						break;
					case 4:
						Add(h[t + x5[M]], v);
						break;
					case 1:
						Add(h[t], v);
						break;
					}

				else if (b[k][j])
					switch (b[k][j]) {
					case 3:
						Add(h[t + x5[j] + x5[M]], v); Add(h[t + x5[j] * 2], v); Add(h[t + x5[M] * 5], v);
						break;
					case 2:
						Add(h[t + x5[j]], v); Add(h[t + x5[M]], v);
						break;
					case 4:
						Add(h[t + x5[j]], v);
						break;
					case 1:
						Add(h[t], v);
						break;
					}

				if (!b[k][M] && !b[k][j]) {
					Add(f[now][t + x5[j] * 3], v); Add(f[now][t + x5[j] * 4 + x5[M]], v);
					Add(f[now][t + x5[j] + x5[M] * 4], v); Add(f[now][t + x5[M] * 3], v);
				}
			}
		}
	printf("%d", f[now][0]);
	return 0;
}
