#include <bits/stdc++.h>
using namespace std;
const int V = 1000010;
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
int fa[V];
int getf(int x) {
	return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
void Init(int n) {
	for (int i = 1; i <= n; i++) fa[i] = i;
}
void Merge(int x, int y) {
	x = getf(x); y = getf(y);
	if (x == y) return;
	fa[x] = y;
}
struct Node {
	int p, x, y;
	Node (int p = 0, int x = 0, int y = 0) : p(p), x(x), y(y) {}
	friend bool operator < (const Node &a, const Node &b) {
		return a.p > b.p;
	}
} v[V]; 
int T, N, M;
int tot, a[V << 1];
int Solve() {
	Read(N);
	int x, y, p;
	for (int i = 1; i <= N; i++) {
		Read(x); Read(y); Read(p); v[i] = Node(p, x, y);
		a[++tot] = x; a[++tot] = y;
	}
	sort(v + 1, v + 1 + N);
	sort(a + 1, a + 1 + tot); M = unique(a + 1, a + 1 + tot) - a;
	Init(M);
	for (int i = 1; i <= N; i++) {
		x = v[i].x, y = v[i].y;
		x = lower_bound(a + 1, a + 1 + M, x) - a;
		y = lower_bound(a + 1, a + 1 + M, y) - a;
		if (v[i].p) Merge(x, y);
		else {
			x = getf(x); y = getf(y);
			if (x == y) return printf("NO\n"), 0;
		}
	}
	return printf("YES\n"), 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T); while (T--) Solve();
	return 0;
}
