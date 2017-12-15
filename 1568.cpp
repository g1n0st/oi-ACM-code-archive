#ifdef LOCAL_EDITER
#include "dataMkr.h"
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int V = 200010;
const double eps = 1e-10;
const int M = 50010;
int sg(double x) {
	return (x > eps) - (x < eps);
}
struct Node {
	double k, b;
	Node() {
	}
	Node(double k, double b) : k(k), b(b) {}
	double f(int x) {
		return k * (x - 1) + b;
	}
} s[V];
int cross(int a, int b) {
	return floor((s[a].b - s[b].b) / (s[b].k - s[a].k));
}
int Q, tot;
int li[V]; double vy[V];
void Modify(int o, int l, int r, int x) {
	int Mid = (l + r) >> 1;
	int lf = (s[x].f(l) - s[li[o]].f(l)) > 0;
	int rf = (s[x].f(r) - s[li[o]].f(r)) > 0;
	if (lf && rf) {
		li[o] = x; return;
	}
	else if (lf || rf) {
		int t = cross(li[o], x);
		if (t <= Mid && lf) Modify(o << 1, l, Mid, x);
		if (t <= Mid && rf) Modify(o << 1, l, Mid, li[o]), li[o] = x;
		if (Mid < t && rf) Modify(o << 1 | 1, Mid + 1, r, x);
		if (Mid < t && lf) Modify(o << 1 | 1, Mid + 1, r, li[o]), li[o] = x;
	} else {
		vy[l] = max(vy[l], s[x].f(l));
		vy[r] = max(vy[r], s[x].f(r));
	}
}
double Ans;
void Query(int o, int l, int r, int p) {
	if (li[o]) Ans = max(Ans, s[li[o]].f(p));
	if (l == r) return;
	int Mid = (l + r) >> 1;
	if (p <= Mid) Query(o << 1, l, Mid, p);
	if (Mid < p) Query(o << 1 | 1, Mid + 1, r, p);
}
#ifdef LOCAL_EDITER
class Mkr : dataMkr {
public:
	void o(string name) {
		Open(name);
		int N = 100000;
		p(N), ed();
		while (N--) {
			int op = Rd(2);
			if (op & 1) {
				fp << "Project " << dRd() * 1000000 << ' ' << dRd() * 100 << endl;
			}
			else {
				fp << "Query " << Rd(50000) << endl;
			}
		}
		cerr << "data Completed" << endl;
	}
} mkr;
#endif
int main() {
#ifdef LOCAL_EDITER
	mkr.o("in.txt");
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int btime = clock();
#endif
	int i, j;
	scanf("%d\n", &Q);
	char op[10]; double k, b; int x;
	while (Q--)	{
		scanf("%s", op);
		if (op[0] == 'P') {
			scanf("%lf%lf\n", &b, &k);
			s[++tot] = Node(k, b);
			Modify(1, 1, M, tot);
		} else {
			scanf("%d\n", &x);
			Ans = 0.0;
			Query(1, 1, M, x);
			//printf("%lf\n", Ans);
			printf("%lld\n", (long long)(floor(Ans / 100.0)));
		}
	};
	return 0;
}
