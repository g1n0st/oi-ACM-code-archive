#include <bits/stdc++.h>
using namespace std;
const int V = 500010;
int N, a[V], vis[V], vis1[V];
char get(void) {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c;
	while (c < '0' || c > '9') {
		c = get();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = get();
	}
}
void No() {
	printf("YES\n");
	exit(0);
}
bool Range(int x) {
	return x > 0 && x <= N;
}
void Solve(int l, int r) {
	if (l == r) return;
	int Mid = (l + r) >> 1;
	for (int i = l; i <= Mid; i++) vis[a[i]] = 1;
	for (int i = Mid + 1; i <= r; i++)
		if (Range(a[Mid] * 2 - a[i]) && vis[a[Mid] * 2 - a[i]])
			No();
	Solve(Mid + 1, r);
	for (int i = l; i <= Mid; i++) vis[a[i]] = 0;
	
	for (int i = Mid + 1; i <= r; i++) vis1[a[i]] = 1;
	for (int i = l; i <= Mid; i++)
		if (Range(a[Mid] * 2 - a[i]) && vis1[a[Mid] * 2 - a[i]])
			No();
	Solve(l, Mid);
	for (int i = Mid + 1; i <= r; i++) vis1[a[i]] = 0;
}
int main(void) {
	//freopen("in.txt", "r", stdin);
	//freopen("b.txt", "w", stdout);
	Read(N);
	for (int i = 1; i <= N; i++) {
		Read(a[i]);
	}
	Solve(1, N);
	printf("NO\n");
	return 0;
}
