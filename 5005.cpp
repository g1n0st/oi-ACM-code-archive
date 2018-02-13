#include <bits/stdc++.h>
using namespace std;
const int V = 200010;
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
	for (; !isdigit(c); c = get()) if (c == '-') f ^= 1;
	for (; isdigit(c); x = x * 10 + c - '0', c = get()); if (f) x = -x;
}
int fa[V];
int getf(int x) {
	return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
int n, m, cnt; vector<int> g;
struct Node {
	int l, r, op;
	Node() {}
	Node(int op, int l, int r) : l(l), r(r), op(op) {}
} a[V], p[V];
int id(int x) {
	return lower_bound(g.begin(), g.end(), x) - g.begin() + 1;
}
namespace SGT {
	vector<int> v[V << 2];
	void Del(int o, int l, int r, int pos) {
		if (v[o].size()) {
			for (int i = 0; i < v[o].size(); i++) {
				int id = v[o][i];
				fa[getf(id)] = cnt;
				p[cnt].l = min(p[cnt].l, p[id].l);
				p[cnt].r = max(p[cnt].r, p[id].r);
			}
			v[o].clear();
		}
		if (l == r) return;
		int Mid = (l + r) >> 1;
		if (pos <= Mid) Del(o << 1, l, Mid, pos);
		else Del(o << 1 | 1, Mid + 1, r, pos);
	}
	void Upd(int o, int l, int r, int L, int R) {
		if (L > R) return;
		if (l >= L && r <= R) {
			v[o].push_back(cnt); return;
		}
		int Mid = (l + r) >> 1;
		if (L <= Mid) Upd(o << 1, l, Mid, L, R);
		if (Mid < R) Upd(o << 1 | 1, Mid + 1, r, L, R);
	}
}
using SGT::Del; using SGT::Upd;
bool chk(Node a, Node b) {
	return (b.l < a.l && a.l < b.r) || (b.l < a.r && a.r < b.r);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	Read(n);
	int op, l, r;
	for (int i = 1; i <= n; i++) {
		Read(op); Read(l); Read(r);
		if (op & 1) g.push_back(l), g.push_back(r);
		a[i] = Node(op, l, r);
	}
	sort(g.begin(), g.end()); g.erase(unique(g.begin(), g.end()), g.end());
	m = g.size() + 1;
	for (int i = 1; i <= m; i++) fa[i] = i;
	for (int i = 1; i <= n; i++) {
		if (a[i].op & 1) {
			a[i].l = id(a[i].l); a[i].r = id(a[i].r);
			p[++cnt] = a[i];
			Del(1, 1, m, a[i].l); Del(1, 1, m, a[i].r); Upd(1, 1, m, p[cnt].l + 1, p[cnt].r - 1);
		}
		else {
			int x = getf(a[i].l), y = getf(a[i].r);
			if (x == y || chk(p[x], p[y])) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
