#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T>
void Read(T &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int N, a[V];  LL K, b[V];
struct Xor {
	int p[32];
	Xor() {
		memset(p, 0, sizeof p);
	}
	void Add(int x) {
		for (int i = 30; ~i; i--) {
			if (!(x >> i)) continue;
			if (!p[i]) {
				p[i] = x; break;
			}
			x ^= p[i];
		}
	}
	int Query() {
		int r = 0;
		for (int i = 30; ~i; i--)
			if ((r ^ p[i]) > r) r ^= p[i];
		return r;
	}
	friend Xor operator + (Xor a, Xor b) {
		Xor r = a;
		for (int i = 30; ~i; i--)
			if (b.p[i]) r.Add(b.p[i]);
		return r;
	}
} bs[V << 2];
void Build(int o, int l, int r) {
	if (l == r) return bs[o].Add(a[l]);
	int Mid = (l + r) >> 1;
	Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
	bs[o] = bs[o << 1] + bs[o << 1 | 1];
}
Xor Query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return bs[o];
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	return Query(o << 1, l, Mid, L, Mid) + Query(o << 1 | 1, Mid + 1, r, Mid + 1, R);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Read(N); Read(K);
	for (i = 1; i <= N; i++) {
		Read(a[i]); Read(b[i]);
	}
	for (i = 1; i <= N; i++) b[i] += b[i - 1];
	Build(1, 1, N);
	int Ans = 0;
	for (i = 1, j = 0; i <= N; i++) {
		while (j + 1 <= N && b[j + 1] - b[i - 1] <= K) j++;
		if (j < i) continue;
		Ans = max(Ans, Query(1, 1, N, i, j).Query());
	}
	cout << Ans << endl;
	return 0;
}
