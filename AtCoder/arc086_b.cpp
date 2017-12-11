#include <cstdio>
#include <iostream>
using namespace std;
int N, a[110];
void Read(int &x) {
	scanf("%d", &x);
}
int xx[1000], yy[1000], num;
void Add(int x, int y) {
	a[y] += a[x];
	num++; xx[num] = x; yy[num] = y;
}
void Solve1() {
	for (int i = 2; i <= N; i++)
		if (a[i] < a[i - 1]) Add(i - 1, i);
}
void Solve2() {
	for (int i = N; i > 1; i--) {
		if (a[i] < a[i - 1]) Add(i, i - 1);
	}
}
int main() {
	int i, j;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N);
	int Mxp = 1, Mnp = 1, Mx = -1000010, Mn = 1000010;
	for (i = 1; i <= N; i++) {
		Read(a[i]);
		if (a[i] > Mx) Mx = a[i], Mxp = i;
		if (a[i] < Mn) Mn = a[i], Mnp = i;
	}
	if (Mn >= 0) Solve1();
	else if (Mx <= 0) Solve2();
	else if (Mx + Mn > 0) {
		for (i = 1; i <= N; i++) Add(Mxp, i);
		Solve1();
	}
	else {
		for (i = 1; i <= N; i++) Add(Mnp, i);
		Solve2();
	}
	printf("%d\n", num);
	for (i = 1; i <= num; i++) printf("%d %d\n", xx[i], yy[i]);
	return 0;
}
