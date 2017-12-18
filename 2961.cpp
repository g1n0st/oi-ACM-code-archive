#include <cstdio>
#include <algorithm>
using namespace std;
const int V = 500010;
struct Node {
	double x, y, k;
	int id, p, op;
	friend bool operator < (const Node &a, const Node &b) {
		return a.k < b.k;
	}
} v[V], tmp[V];
int cnt, N, ok[V], q1[V], q2[V];
const double eps = 1e-10;
const double INF = 1e40;
double sqr(double x) {
	return x * x;
}
double dis(int x, int y) {
	return sqr(v[x].x - v[y].x) + sqr(v[x].y - v[y].y);
}
double sg(double x) {
	return (x > eps) - (x < -eps);
}
double gk(int x, int y) {
	if (!sg(v[x].x - v[y].x)) return INF;
	return (v[x].y - v[y].y) / (v[x].x - v[y].x);
}
void Solve(int l, int r) {
	if (l == r) return;
	int Mid = (l + r) >> 1, i, j = l, k = Mid + 1, t1 = 0, t2 = 0;
	for (i = l; i <= r; i++)
		if (v[i].id <= Mid) tmp[j++] = v[i];
		else tmp[k++] = v[i];
	for (i = l; i <= r; i++) v[i] = tmp[i];
	Solve(l, Mid);
	for (i = l; i <= Mid; i++)
		if (!v[i].op) {
			while (t1 > 1 && sg(gk(q1[t1 - 1], i) - gk(q1[t1 - 1], q1[t1])) > 0) --t1;
			q1[++t1] = i;
			while (t2 > 1 && sg(gk(q2[t2 - 1], i) - gk(q2[t2 - 1], q2[t2])) < 0) --t2;
			q2[++t2] = i;
		}
	reverse(q2 + 1, q2 + t2 + 1);
	for (i = Mid + 1; i <= r; i++) 
		if (v[i].op) {
			while (t1 > 1 && v[i].k > gk(q1[t1 - 1], q1[t1])) --t1;
			if (t1 && dis(q1[t1], 0) < dis(q1[t1], i)) ok[v[i].p] = 0;
			while (t2 > 1 && v[i].k > gk(q2[t2 - 1], q2[t2])) --t2;
			if (t2 && dis(q2[t2], 0) < dis(q2[t2], i)) ok[v[i].p] = 0;
		}
	Solve(Mid + 1, r);
	j = l; k = Mid + 1;
	for (i = l; i <= r; i++) {
		if (k > r) tmp[i] = v[j++];
		else if (j > Mid) tmp[i] = v[k++];
		else {
			if (v[j].x < v[k].x) tmp[i] = v[j++];
			else tmp[i] = v[k++];
		}
	}
	for (i = l; i <= r; i++) v[i] = tmp[i];
}
int main() {
	int i, j;
	scanf("%d", &N); bool flg = 0;
	for (i = 1; i <= N; i++) {
		scanf("%d%lf%lf", &v[i].op, &v[i].x, &v[i].y);
		if (v[i].op) {
			v[i].p = ++cnt; ok[cnt] = flg;
		} else flg = 1;
		v[i].id = i; v[i].k = v[i].y ? (-v[i].x / v[i].y) : INF;
	}
	sort(v + 1, v + 1 + N); Solve(1, N);
	for (i = 1; i <= cnt; i++) puts(ok[i] ? "Yes" : "No");
	return 0;
}
