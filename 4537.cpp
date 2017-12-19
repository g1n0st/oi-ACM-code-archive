#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
const int V = 200005;

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
	int u, v, a, b, id;
	void Read(int i) {
		::Read(u); ::Read(v); ::Read(a); ::Read(b);
		id = i;
	}
} e[V], q[V], a[V];
struct Op {
	int x, y, f, mxA, mxB, siz;
	Op() {}
	Op(int x, int y, int f, int mxA, int mxB, int siz) :
		x(x), y(y), f(f), mxA(mxA), mxB(mxB) {}
} op[V];
int cmpA(const Node &a, const Node &b) {
	return a.a < b.a;
}
int cmpB(const Node &a, const Node &b) {
	return a.b < b.b;
}
int N, M, Q, B, Ans[V];
int fa[V], mxA[V], mxB[V], siz[V], tot;
int getf(int x, int f) {
	if (fa[x] == x) return x;
	if (f) op[++tot] = Op(x, 0, fa[x], 0, 0, 0);
	return fa[x] = getf(fa[x], f);
}
void Merge(int x, int y, int a, int b, int f) {
	x = getf(x, f); y = getf(y, f);
	if (siz[x] < siz[y]) swap(x, y);
	if (f) op[++tot] = Op(x, y, fa[y], mxA[x], mxB[x], siz[x]);
	if (x == y) {
		mxA[x] = max(mxA[x], a); mxB[x] = max(mxB[x], b);
		return;
	}
	fa[y] = x; siz[x] += siz[y];
	mxA[x] = max(mxA[x], max(mxA[y], a));
	mxB[x] = max(mxB[x], max(mxB[y], b));
}
void Pop(int x) {
	if (!op[x].y) fa[op[x].x] = op[x].f;
	else {
		fa[op[x].y] = op[x].f;
		mxA[op[x].x] = op[x].mxA;
		mxB[op[x].x] = op[x].mxB;
		siz[op[x].x] = op[x].siz;
	}
}
void Init() {
	int i, j;
	for (i = 1; i <= N; i++) {
		fa[i] = i; siz[i] = 1; mxA[i] = mxB[i] = -1;
	}
}
int main() {
	int i, j, k, l;
	for (Read(N), Read(M), i = 1; i <= M; i++) e[i].Read(i);
	for (Read(Q), i = 1; i <= Q; i++) q[i].Read(i);
	sort(e + 1, e + 1 + M, cmpA);
	sort(q + 1, q + 1 + Q, cmpB);
	for (B = sqrt(M), k = 1; k <= M; k += B) {
		int cnt = 0;
		for (i = 1; i <= Q; i++)
			if (q[i].a >= e[k].a && (k + B > M || q[i].a < e[k + B].a))
				a[++cnt] = q[i];
		sort(e + 1, e + k, cmpB);
		Init();
		for (i = j = 1; i <= cnt; i++) {
			while (j < k && e[j].b <= a[i].b) {
				Merge(e[j].u, e[j].v, e[j].a, e[j].b, 0); j++;
			}
			tot = 0;
			for (l = k; l <= min(M, k + B - 1); l++)
				if (e[l].a <= a[i].a && e[l].b <= a[i].b)
					Merge(e[l].u, e[l].v, e[l].a, e[l].b, 1);
			int x = getf(a[i].u, 1), y = getf(a[i].v, 1);
			if (x == y && mxA[x] == a[i].a && mxB[x] == a[i].b) Ans[a[i].id] = 1;
			while (tot) Pop(tot--);
		}
	}
	for (i = 1; i <= Q; i++) puts(Ans[i] ? "Yes" : "No");
	return 0;
}
