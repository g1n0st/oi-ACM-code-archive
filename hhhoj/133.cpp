#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
const int V = 1000010;
using namespace std;
typedef pair<int, int> pl;
int Max(int a, int b) {
	return a > b ? a : b;
}
int Min(int a, int b) {
	return a < b ? a : b;
}
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c;
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
int N, M, a[V], s[V], Ans;
int main() {
	int i, j;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(M);
	for (i = 1; i <= N; i++) {
		Read(a[i]); Read(a[i]);
	}
	a[++N] = 0; int pt = 1;
	for (i = 2; i <= N; i++)
		if (a[i] != a[i - 1])
			a[++pt] = a[i];
	N = pt; pt = 0;
	for (i = 1; i <= N; i++) {
		while (pt && a[i] < s[pt]) --pt, ++Ans;
		while (pt && a[i] == s[pt]) --pt;
		s[++pt] = a[i];
	}
	printf("%d\n", Ans);
	return 0;
}
