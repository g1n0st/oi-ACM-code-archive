#include <bits/stdc++.h>
using namespace std;
const int V = 1010;
int a[V][V], T, N, M;
int Min(int a, int b) {
	return a < b ? a : b;
}
void Solve() {
	int i, j;
	scanf("%d%d\n", &N, &M);
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) 
			a[i][j] = (getchar() == 'G');
		getchar();
	}
	int Ans1 = 0, Ans2 = 0;
	for (i = 1; i <= N; i++) 
		for (j = 1; j <= M; j++) {
			if (((i ^ j) & 1) & a[i][j]) Ans1 += 3;
			if ((!((i ^ j) & 1)) & (!a[i][j])) Ans1 += 5;
	}
	for (i = 1; i <= N; i++)
		for (j = 1; j <= M; j++) {
			if ((!((i ^ j) & 1)) & a[i][j]) Ans2 += 3;
			if (((i ^ j) & 1) & (!a[i][j])) Ans2 += 5;
	}
	cout << Min(Ans1, Ans2)	<< endl;
}
int main(void) {
	//freopen("in.txt", "r", stdin);
	scanf("%d\n", &T);
	while (T--) Solve();
	return 0;
}
