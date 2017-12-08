#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <map>
typedef long long LL;
using namespace std;
unsigned Rd(int x) {
	return (((LL)rand() << 15) | rand()) % x;
}
int Abs(int x) {
	return x < 0 ? -x : x;
}
int M, Tot, Ans, Ansv;
map<unsigned, int> rc;
int main(void) {
	int i, j; unsigned x;
	srand(10086);
	scanf("%d", &M);
	for (i = 1; i <= M; i++) {
		scanf("%u", &x);
		if (!rc.count(x)) rc[x] = ++Tot;
	} Ansv = 1 << 30;
	for (i = 10; i <= 10000000; i *= 10) {
		int cnt = 0; rc.clear();
		for (j = 1; j <= M; j++) {
			x = Rd(i);
			if (!rc.count(x)) rc[x] = ++cnt;
		}
		if (Abs(cnt - Tot) < Ansv) {
			Ansv = Abs(cnt - Tot); Ans = i;
		}
	}
	printf("%d\n", Ans);
	return 0;
}
