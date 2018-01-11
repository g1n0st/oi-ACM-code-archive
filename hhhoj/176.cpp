#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
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
	x = 0; static char c;
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
struct Node {
	int op, t, w;
	Node() {}
	Node(int op, int t, int w) : op(op), t(t), w(w) {}
	friend bool operator < (const Node &a, const Node &b) {
		return a.op < b.op;
	}
} o[V];
vector<Node> g[V];
int Mx[V << 2];
LL lv[V << 2];
LL Query(int o, int l, int r, int x) {
	if (l == r) {
		if (Mx[o] <= x) return 0; else return Mx[o];
	}
	int Mid = (l + r) >> 1;
	if (x >= Mx[o << 1 | 1]) return Query(o << 1, l, Mid, x);
	else return lv[o] + Query(o << 1 | 1, Mid + 1, r, x);
}
void pushUp(int o, int l, int r) {
	Mx[o] = max(Mx[o << 1], Mx[o << 1 | 1]);
	lv[o] = Query(o << 1, l, (l + r >> 1), Mx[o << 1 | 1]);
}
void Modify(int o, int l, int r, int p, int x) {
	if (l == r) {
		Mx[o] = x; return;
	}
	int Mid = (l + r) >> 1;
	if (p <= Mid) Modify(o << 1, l, Mid, p, x); else Modify(o << 1 | 1, Mid + 1, r, p, x);
	pushUp(o, l, r);
}
LL t; int now;
void Find(int o, int l, int r, int L, int R) {
	if (l >= L && r <= R) {
		t += Query(o, l, r, now); now = max(now, Mx[o]);
		return;
	}
	int Mid = (l + r) >> 1;
	if (Mid < R) Find(o << 1 | 1, Mid + 1, r, L, R); if (L <= Mid) Find(o << 1, l, Mid, L, R);
}
int N, M;
LL Ans[V];
int main() {
	int i, j;
	Read(N); Read(M);
	int op, l, r, x;
	for (i = 1; i <= M; i++) {
		Read(op);
		if (op & 1) {
			Read(l); Read(r); Read(x);
			g[l].emplace_back(Node(op, i, x));
			g[r + 1].emplace_back(Node(op, i, 0));
		}
		else {
			Read(x); g[x].emplace_back(Node(op, i, 0));
		}
	}
	for (i = 1; i <= N; i++) sort(g[i].begin(), g[i].end());
	memset(Ans, -1, sizeof Ans);
	for (i = 1; i <= N; i++) {
		for (auto p : g[i]) {
			if (p.op & 1) Modify(1, 1, M, p.t, p.w);
			else {
				t = now = 0; 
				Find(1, 1, M, 1, p.t); Ans[p.t] = t;
			}
		}
	}
	for (i = 1; i <= M; i++)
		if (~Ans[i]) printf("%lld\n", Ans[i]);
	return 0;
}
