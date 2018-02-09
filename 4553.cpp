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
int t[V];
int lowbit(int x) {
	return x & (-x);
}
void Add(int x, int v) {
	while (x < V) {
		t[x] = v ? max(v, t[x]) : 0; x += lowbit(x);
	}
}
int Query(int x) {
	int r = 0;
	while (x) {
		r = max(t[x], r); x -= lowbit(x);
	}
	return r;
}

int n, m, lv[V], rv[V], v[V], f[V];
struct Node {
	int x, y, id;
	Node() {}
	Node(int x, int y, int id) : x(x), y(y), id(id) {}
	friend bool operator < (const Node &a, const Node &b) {
		return a.x ^ b.x ? a.x < b.x : (a.y ^ b.y ? a.y < b.y : a.id < b.id);
	}
} q[V];
void Solve(int l, int r) {
	if (l == r) {
		f[l] = max(f[l], 1); return;
	}
	int Mid = (l + r) >> 1; Solve(l, Mid);
	for (int i = l; i <= r; i++)
		q[i] = (i <= Mid ? Node(v[i], rv[i], i) : Node(lv[i], v[i], i));
	sort(q + l, q + r + 1);
	for (int i = l; i <= r; i++)
		if (q[i].id <= Mid) Add(q[i].y, f[q[i].id]);
		else f[q[i].id] = max(f[q[i].id], Query(q[i].y) + 1);
	for (int i = l; i <= r; i++) if (q[i].id <= Mid) Add(q[i].y, 0);
	Solve(Mid + 1, r);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	for (int i = 1; i <= n; i++) {
		Read(v[i]); lv[i] = rv[i] = v[i];
	}
	int x, y;
	while (m--) {
		Read(x); Read(y); lv[x] = min(lv[x], y); rv[x] = max(rv[x], y);
	}
	Solve(1, n);
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, f[i]);
	cout << ans << endl;
	return 0;
}
