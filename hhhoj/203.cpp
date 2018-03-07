#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PI;
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
void Read(char *s, int len) {
	len = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); s[len++] = c, c = get());
}
vector<PI> G[V];
int n, m, P[V], ans[V];
char s[V];
namespace SGT {
	int val[V];
	void Add(int x, int v) {
		for (; x; x -= x & -x) val[x] = max(val[x], v);
	}
	int Query(int x) {
		int r = 0;
		for (; x <= n; x += x & -x) r = max(r, val[x]);
		return r;
	}
}
namespace SAM {
	int fa[V << 1], len[V << 1], c[V << 1][2], lst, rt, pT;
	void init() {
		rt = lst = ++pT;
	}
	int extend(int x) {
		int cur = ++pT; len[cur] = len[lst] + 1;
		int p = lst;
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) fa[cur] = rt;
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) fa[cur] = q;
			else {
				++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (p && c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[q] = fa[cur] = pT;
			}
		}
		return lst = cur;
	}
} using SAM::len;
namespace LCT {
	int c[V << 1][2], fa[V << 1], mark[V << 1];
	int Rt(int x) {
		return c[fa[x]][0] != x && c[fa[x]][1] != x;
	}
	void pushDown(int x) {
		int &l = c[x][0], &r = c[x][1];
		if (mark[x]) {
			mark[l] = mark[r] = mark[x];
		}
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
		if (!Rt(y)) {
			if (c[z][0] == y) c[z][0] = x;
			else c[z][1] = x;
		}
		fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
		c[y][l] = c[x][r]; c[x][r] = y;
	}
	int s[V], t;
	void splay(int x) {
		s[++t] = x;
		for (int i = x; !Rt(i); i = fa[i]) s[++t] = fa[i];
		while (t) pushDown(s[t--]);
		while (!Rt(x)) {
			int y = fa[x], z = fa[y];
			if (!Rt(y)) {
				if ((c[y][0] == x) ^ (c[z][0] == y)) rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
	}
	void access(int x) {
		for (int t = 0; x; t = x, x = fa[x]) {
			splay(x); if (mark[x]) SGT::Add(mark[x], SAM::len[x]);
			c[x][1] = t;
		}
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Read(s + 1, n); SAM::init();
	for (int i = 1; i <= n; i++) P[i] = SAM::extend(s[i] - '0');
	for (int i = 2; i <= SAM::pT; i++) LCT::fa[i] = SAM::fa[i];
	int l, r;
	for (int i = 1; i <= m; i++) {
		Read(l); Read(r); G[r].emplace_back(PI(l, i));
	}
	for (int i = 1; i <= n; i++) {
		LCT::access(P[i]); LCT::splay(P[i]); LCT::mark[P[i]] = i;
		for (auto v : G[i]) ans[v.second] = SGT::Query(v.first);
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}
