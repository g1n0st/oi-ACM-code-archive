#include <bits/stdc++.h>
using namespace std;
const int V = 400010;
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
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
int N, lm[V], rm[V], a[V];
namespace Trie {
	int c[V * 32][2], rt, pT;
	void Init() {
		for (int i = 1; i <= pT; i++) c[i][0] = c[i][1] = 0;
		rt = pT = 1;
	}
	void Insert(int x) {
		int p = rt;
		for (int i = 31; ~i; i--) {
			int w = (x >> i) & 1;
			if (!c[p][w]) c[p][w] = ++pT;
			p = c[p][w];
		}
	}
	int Work(int x) {
		int p = rt, r = 0;
		for (int i = 31; ~i; i--) {
			int w = (x >> i) & 1;
			if (c[p][!w]) r += (1 << i), p = c[p][!w];
			else p = c[p][w];
		}
		return r;
	}
}
void Work(int *am) {
	Trie::Init(); Trie::Insert(0); int now = 0;
	for (int i = 1; i <= N; i++) {
		now ^= a[i]; Trie::Insert(now); am[i] = Trie::Work(now);
	}
	for (int i = 1; i <= N; i++) am[i] = max(am[i], am[i - 1]);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N);
	for (int i = 1; i <= N; i++) Read(a[i]);
	Work(lm); reverse(a + 1, a + 1 + N); 
	Work(rm); reverse(rm + 1, rm + 1 + N);
	int ans = 0;
	for (int i = 1; i < N; i++) ans = max(ans, lm[i] + rm[i + 1]);
	printf("%d\n", ans);
	return 0;
}
