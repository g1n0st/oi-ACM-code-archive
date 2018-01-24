#include <bits/stdc++.h>
using namespace std;
const int V = 500010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c; int f = 0;
	for (; !(c >= '0' && c <= '9'); c = get()) f ^= (c == '-');
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get()); if (f) x = -x;
}
struct Xor {
	int p[32];
	Xor() {
		memset(p, 0, sizeof p);
	}
	void Add(int x) {
		for (int i = 31; ~i; i--) {
			if (!(x >> i)) continue;
			if (!p[i]) {
				p[i] = x; break;
			}
			x ^= p[i];
		}
	}
	int Query() {
		int r = 0;
		for (int i = 31; ~i; i--)
			if ((r ^ p[i]) > r) r ^= p[i];
		return r;
	}
};
vector<int> val[V << 2];
void Update(int o, int l, int r, int L, int R, int x) {
	if (l == L && r == R) return val[o].push_back(x);
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Update(o << 1, l, Mid, L, R, x);
	if (Mid < L) return Update(o << 1 | 1, Mid + 1, r, L, R, x);
	Update(o << 1, l, Mid, L, Mid, x); Update(o << 1 | 1, Mid + 1, r, Mid + 1, R, x);
}
void Query(int o, int l, int r, Xor jd) {
	for (int i = 0; i < val[o].size(); i++) jd.Add(val[o][i]);
	if (l == r) {
		printf("%d\n", jd.Query()); return;
	}
	int Mid = (l + r) >> 1;
	Query(o << 1, l, Mid, jd); Query(o << 1 | 1, Mid + 1, r, jd);
}
map<int, int> t;
int N, M;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x; Read(N); M = 1 << 30;
	for (i = 1; i <= N; i++) {
		Read(x); t[x] = i;
		if (x > 0) M = min(M, x);
	}
	for (map<int, int>::iterator it = t.find(M); it != t.end(); it++) {
		int l = it->second, id = it->first;
		int r = t.count(-id) ? (t[-id] - 1) : N;
		Update(1, 1, N, l, r, id);
	}
	Xor nul;
	Query(1, 1, N, nul);
	return 0;
}
