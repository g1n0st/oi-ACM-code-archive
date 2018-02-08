#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
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
int n, m, a[V], pre[V], tot[V * 10];
namespace SGT {
	const int N = V * 20;
	int rt[V], ls[N], rs[N], sum[N], pT;
	void Add(int &x, int y, int l, int r, int p) {
		x = ++pT; ls[x] = ls[y]; rs[x] = rs[y]; sum[x] = sum[y] + 1;
		if (l == r) return;
		int Mid = (l + r) >> 1;
		if (p <= Mid) return Add(ls[x], ls[y], l, Mid, p);
		else return Add(rs[x], rs[y], Mid + 1, r, p);
	}
	int Query(int x, int y, int l, int r, int L, int R) {
		if (l == L && r == R) return sum[y] - sum[x];
		int Mid = (l + r) >> 1;
		if (R <= Mid) return Query(ls[x], ls[y], l, Mid, L, R);
		if (Mid < L) return Query(rs[x], rs[y], Mid + 1, r, L, R);
		return Query(ls[x], ls[y], l, Mid, L, Mid) + Query(rs[x], rs[y], Mid + 1, r, Mid + 1, R);
	}
	namespace func {
		void Upd(int x, int pre) {
			Add(rt[x], rt[x - 1], 0, n, pre);
		}
		int Qur(int l, int r) {
			return Query(rt[l - 1], rt[r], 0, n, 0, l - 1);
		}
	}
}; using namespace SGT::func; using SGT::rt;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); Upd(i, pre[a[i]]); pre[a[i]] = i;
	}
	Read(m);
	int l, r;
	while (m--) {
		Read(l); Read(r); printf("%d\n", Qur(l, r));
	}
	return 0;
}
