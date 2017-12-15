#include <cstdio>
#include <algorithm>
#include <cmath>
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
const double eps = 1e-10;
int sg(double x) {
	return (x > eps) - (x < -eps);
}
const int M = 39989;
const int P = 1000000000;
double vy[V]; int vl[V];
int Q, lastAns, tot;
struct Line {
	int l, r;
	double k, b;
	Line() {}
	Line(int x1, int y1, int x2, int y2) {
		l = min(x1, x2); r = max(x1, x2);
		if (x1 ^ x2) {
			k = 1.0 * (y1 - y2) / (x1 - x2);
			b = 1.0 * y1 - k * x1;
		} else {
			k = 0.0; b = max(y1, y2);
		}
	}
	double f(int x) {
		return x * k + b;
	}
} s[V];
struct Node {
	int l, r, li;
} node[V];
void Build(int o, int l, int r) {
	node[o].l = l; node[o].r = r;
	if (l == r) return;
	int Mid = (l + r) >> 1;
	Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
}
int cross(int a, int b) {
	return floor((s[a].b - s[b].b) / (s[b].k - s[a].k));
}
void Update(int x, int Now) {
	double y = s[Now].f(x);
	int f = sg(y - vy[x]);
	if (!vl[x] || f > 0 || (f == 0 && x < vl[x])) {
		vl[x] = Now; vy[x] = y;
	}
}
void Modify(int o, int Now) {
	int Mid = (node[o].l + node[o].r) >> 1;
	if (node[o].l >= s[Now].l && node[o].r <= s[Now].r) {
		int lf = sg(s[Now].f(node[o].l) - s[node[o].li].f(node[o].l)) > 0;
		int rf = sg(s[Now].f(node[o].r) - s[node[o].li].f(node[o].r)) > 0;
		if (lf && rf) node[o].li = Now;
		else if (lf || rf) {
			int t = cross(Now, node[o].li);
			if (t <= Mid && lf) Modify(o << 1, Now);
			if (t <= Mid && rf) Modify(o << 1, node[o].li), node[o].li = Now;
			if (Mid < t && rf) Modify(o << 1 | 1, Now);
			if (Mid < t && lf) Modify(o << 1 | 1, node[o].li), node[o].li = Now;
		} else {
			Update(node[o].l, Now);
			Update(node[o].r, Now);
		}
		return;
	}
	if (s[Now].l <= Mid) Modify(o << 1, Now);
	if (Mid < s[Now].r) Modify(o << 1 | 1, Now);
}
int ansL; double ansY;
void Query(int o, int p) {
	if (node[o].li) {
		double y = s[node[o].li].f(p);
		int f = sg(y - ansY);
		if (f > 0 || (f == 0 && node[o].li < ansL)) {
			ansL = node[o].li; ansY = y;
		}
	}
	if (node[o].l == node[o].r) return;
	int Mid = (node[o].l + node[o].r) >> 1;
	if (p <= Mid) Query(o << 1, p);
	if (Mid < p) Query(o << 1 | 1, p);
}
int main() {
	int i, j;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(Q);
	Build(1, 1, M);
	int op, x1, y1, x2, y2;
	while (Q--) {
		Read(op);
		if (op & 1) {
			Read(x1); Read(y1); Read(x2); Read(y2);
			x1 = (x1 + lastAns - 1) % M + 1; x2 = (x2 + lastAns - 1) % M + 1;
			y1 = (y1 + lastAns - 1) % P + 1; y2 = (y2 + lastAns - 1) % P + 1;
			s[++tot] = Line(x1, y1, x2, y2);
			Modify(1, tot);
		} else {
			Read(x1);
			x1 = (x1 + lastAns - 1) % M + 1;
			ansL = 0; ansY = -1.0;
			Query(1, x1);
			int f = sg(vy[x1] - ansY);
			if (f > 0 || (f == 0 && vl[x1] < ansL)) ansL = vl[x1];
			lastAns = ansL;
			printf("%d\n", lastAns);
		}
	}
	return 0;
}
