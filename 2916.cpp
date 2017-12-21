#include <cstdio>
using namespace std;
const int V = 100100;
void Read(int &x) {
	scanf("%d", &x);
}
int N, M, d[V];
int main() {
	int i, j, x, y;
	Read(N); Read(M);
	for (i = 1; i <= M; i++) {
		Read(x); Read(y);
		d[x]++; d[y]++;
	}
	int Ans = 0;
	for (i = 1; i <= N; i++) {
		Ans -= d[i] * (N - 1 - d[i]);
	}
	Ans /= 2;
	Ans += N * (N - 1) * (N - 2) / 6;
	printf("%d", Ans);
	return 0;
}
