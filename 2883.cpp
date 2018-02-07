#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
typedef long long LL;
typedef set<int>::iterator It;
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
void Read(char &x) {
	x = get(); while (!isupper(x)) x = get();
}

int n, m, a[V], pre[3 * V];
struct Node {
	int a, b; char op;
} v[V];
vector<int> g;
set<int> S[3 * V];

namespace SGT1 {
	const int N = V * 40;
	int ls[N], rs[N], pT; LL sum[N];
	void Mo(int &x, int l, int r, int p, int v) {
		if (!x) x = ++pT; sum[x] += v;
		if (l == r) return;
		int Mid = (l + r) >> 1;
		if (p <= Mid) Mo(ls[x], l, Mid, p, v); else Mo(rs[x], Mid + 1, r, p, v);
	}
	LL Qur(int x, int l, int r, int L, int R) {
		if (!x) return 0; if (l == L && r == R) return sum[x];
		int Mid = (l + r) >> 1;
		if (R <= Mid) return Qur(ls[x], l, Mid, L, R);
		if (Mid < L) return Qur(rs[x], Mid + 1, r, L, R);
		return Qur(ls[x], l, Mid, L, Mid) + Qur(rs[x], Mid + 1, r, Mid + 1, R);
	}
}
namespace SGT2 {
	int rt[V << 2];
	void Mo(int o, int l, int r, int p1, int p2, int v) {
		SGT1::Mo(rt[o], 0, n, p2, v); if (l == r) return;
		int Mid = (l + r) >> 1;
		if (p1 <= Mid) Mo(o << 1, l, Mid, p1, p2, v);
		else Mo(o << 1 | 1, Mid + 1, r, p1, p2, v);
	}
	LL Qur(int o, int l, int r, int l1, int r1, int l2, int r2) {
		if (l == l1 && r == r1) return SGT1::Qur(rt[o], 0, n, l2, r2);
		int Mid = (l + r) >> 1;
		if (r1 <= Mid) return Qur(o << 1, l, Mid, l1, r1, l2, r2);
		if (Mid < l1) return Qur(o << 1 | 1, Mid + 1, r, l1, r1, l2, r2);
		return Qur(o << 1, l, Mid, l1, Mid, l2, r2) + Qur(o << 1 | 1, Mid + 1, r, Mid + 1, r1, l2, r2);
	}
	namespace func {
		void Cha(int pos, int pre, int val) {
			Mo(1, 1, n, pos, pre, val);
		}
		LL Query(int l, int r) {
			return Qur(1, 1, n, l, r, 0, l - 1);
		}
	}
}
using namespace SGT2::func;
int id(int x) {
	return lower_bound(g.begin(), g.end(), x) - g.begin();
}
void Del(int x, int y) {
	int t = id(x);
	It it = S[t].find(y); It pre = --it; ++it; It nxt = ++it; --it;
	Cha(*it, *pre, -x);
	if (nxt != S[t].end()) {
		Cha(*nxt, *it, -x); Cha(*nxt, *pre, x);
	}
	S[t].erase(it);
}
void Add(int x, int y) {
	int t = id(x);
	S[t].insert(y);
	It it = S[t].find(y); It pre = --it; ++it; It nxt = ++it; --it;
	if (nxt != S[t].end()) {
		Cha(*nxt, *pre, -x); Cha(*nxt, *it, x);
	}
	Cha(*it, *pre, x);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); g.push_back(a[i]);
	}
	Read(m);
	for (int i = 1; i <= m; i++) {
		Read(v[i].op); Read(v[i].a); Read(v[i].b);
		if (v[i].op == 'U') g.push_back(v[i].a), g.push_back(v[i].b);
	}
	sort(g.begin(), g.end()); g.erase(unique(g.begin(), g.end()), g.end());
	for (int i = 0; i < g.size(); i++) S[i].insert(0);
	for (int i = 1; i <= n; i++) {
		int t = id(a[i]); Cha(i, pre[t], a[i]); pre[t] = i; S[t].insert(i);
	}
	for (int i = 1; i <= m; i++) {
		if (v[i].op == 'Q') printf("%lld\n", Query(v[i].a, v[i].b));
		else {
			int p = v[i].a, y = v[i].b;
			Del(a[p], p); a[p] = y; Add(a[p], p);
		}
	}
	return 0;
}
