#include <bits/stdc++.h>
using namespace std;
const int V = 200010;
typedef long long LL;
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
int N, t[V], pos[V];
int lowbit(int x) {
	return x & (-x);
}
void Add(int x, int v) {
	while (x <= 2 * N) {
		t[x] += v; x += lowbit(x);
	}
}
int Query(int x) {
	int Ret = 0;
	while (x) {
		Ret += t[x]; x -= lowbit(x);
	}
	return Ret;
}
int Query(int l, int r) {
	return Query(r) - Query(l);
}
LL Ans;
int main() {
	int i, j, x;
	Read(N);
	for (i = 1; i <= 2 * N; i++) {
		Read(x);
		if (!pos[x]) {
			pos[x] = i;
			Add(i, 1);
		} else {
			Ans += Query(pos[x], i);
			Add(pos[x], -1);
		}
	}
	cout << Ans << endl;
	return 0;
}
