#include <bits/stdc++.h>
using namespace std;
const int V = 1000010;
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
	while (c >= '0'&& c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
int f[V], s[V], N, M, P;
int getF(int x) {
	return f[x] ? f[x] = getF(f[x]) : x;
}
void Init(int n) {
	for (int i = 1; i <= n; i++) f[i] = 0;
	for (int i = 1; i <= n; i++) s[i] = 1;
}
void Merge(int x, int y) {
	x = getF(x); y = getF(y);
	if (x == y) return;
	f[x] = y; s[y] += s[x];
}
#define S_WIN return puts("Shanghai"), 0
#define H_WIN return puts("Hourai"), 0
int T;
int Solve() {
	int i, j, x, y;
	Read(N); Read(M); Read(P); Init(N);
	for (i = 1; i <= M; i++) {
		Read(x); Read(y); Merge(x, y);
	}
	x = getF(1), y = getF(2);
	if (x == y) S_WIN;
	int lst = (N * (N - 1) / 2 - M) & 1;
	if (N & 1) {
		if (lst) S_WIN;
		else H_WIN;
	}
	int xo = (s[x] & 1), yo = (s[y] & 1);
	if (P) {
		int tot = 0;
		for (i = 1; i <= N; i++)
			if (!f[i]) tot++;
		if (lst) {
			if (tot == 2 && xo && yo) H_WIN;
			else S_WIN;
		}
		else {
			if (tot <= 3 && (xo || yo)) S_WIN;
			else H_WIN;
		}
	}
	else {
		if (lst && (!xo || !yo)) S_WIN;
		else if (!lst && (xo || yo)) S_WIN;
		else H_WIN;
	}
}
int main() {
	Read(T); while (T--) Solve();
	return 0;
}
