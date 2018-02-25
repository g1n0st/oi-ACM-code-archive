#include <bits/stdc++.h>
using namespace std;
const int V = 200000;
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
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get()); s[len] = 0;
}
namespace SGT {
	const int N = V * 50;
	int ls[N], rs[N], pT;
	namespace func {
		int rt[V];
		void Upd(int &x, int l, int r, int p) {
			x = ++pT; if (l == r) return;
			int mid = (l + r) >> 1;
			if (p <= mid) Upd(ls[x], l, mid, p);
			else Upd(rs[x], mid + 1, r, p);
		}
		int Merge(int x, int y) {
			if (!x || !y) return x + y;
			int z = ++pT;
			ls[z] = Merge(ls[x], ls[y]); rs[z] = Merge(rs[x], rs[y]);
			return z;
		}
		int Query(int x, int l, int r, int L, int R) {
			if (!x) return 0; if (l == L && r == R) return 1;
			int mid = (l + r) >> 1;
			if (R <= mid) return Query(ls[x], l, mid, L, R);
			if (mid < L) return Query(rs[x], mid + 1, r, L, R);
			if (Query(ls[x], l, mid, L, mid)) return 1;
			return Query(rs[x], mid + 1, r, mid + 1, R);
		}
	};
}
using namespace SGT::func;
namespace SAM {
	int fa[V], len[V], c[V][26], pT, Rt, lst;
	void init() {
		Rt = lst = ++pT;
	}
	int extend(int x) {
		int cur = ++pT; len[cur] = len[lst] + 1;
		int p = lst;
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) fa[cur] = Rt;
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) fa[cur] = q;
			else {
				++pT; fa[pT] = fa[q]; len[pT] = len[p] + 1;
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[cur] = fa[q] = pT;
			}
		}
		return lst = cur;
	}
	int q[V], v[V], f[V][23];
	void Work(int n) {
		for (int i = 1; i <= pT; i++) q[len[i]]++;
		for (int i = 1; i <= n; i++) q[i] += q[i - 1];
		for (int i = pT; i; i--) v[q[len[i]]--] = i;
		for (int i = pT; i; i--) {
			int t = v[i];
			f[t][0] = fa[t]; rt[fa[t]] = Merge(rt[fa[t]], rt[t]);
		}
		for (int j = 1; j <= 20; j++)
			for (int i = 1; i <= pT; i++)
				f[i][j] = f[f[i][j - 1]][j - 1];
	}
}
char s[V];
int n, q, pos[V];
bool chk(int x, int d, int a, int b) {
	a += x - 1; d = pos[d];
	if (SAM::len[d] < x) return 0;
	for (int i = 20; ~i; i--)
		if (SAM::len[SAM::f[d][i]] >= x) d = SAM::f[d][i];
	return Query(rt[d], 1, n, a, b);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(q); Read(s + 1, n);
	reverse(s + 1, s + n + 1); SAM::init();
	for (int i = 1; i <= n; i++) {
		pos[i] = SAM::extend(s[i] - 'a');
		Upd(rt[pos[i]], 1, n, i);
	}
	SAM::Work(n);
	int a, b, c, d;
	while (q--) {
		Read(a); Read(b); Read(c); Read(d);
		a = n - a + 1; b = n - b + 1; c = n - c + 1; d = n - d + 1;
		swap(a, b); swap(c, d);
		int l = 1, r = min(b - a + 1, d - c + 1), ans = 0, mid;
		while (l <= r) {
			mid = (l + r) >> 1;
			if (chk(mid, d, a, b)) l = (ans = mid) + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
