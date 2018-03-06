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

const int N = V * 5, M = N * 60;
int head[M / 2], sub;
struct Edge {
	int to, nxt, v;
	Edge(int to = 0, int nxt = 0, int v = 0) : to(to), nxt(nxt), v(v) {}
} edge[M / 3 * 2];
void Link(int a, int b, int v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}

namespace SGT {
	int ls[M / 2], rs[M / 2], d[M / 2], pT;
	int r1[N], r2[N];
	void Add(int &x, int y, int l, int r, int p, int v) {
		x = ++pT; ls[x] = ls[y]; rs[x] = rs[y];
		if (l == r) return (void)(d[x] = v);
		int mid = (l + r) >> 1; if (p <= mid) Add(ls[x], ls[y], l, mid, p, v); else Add(rs[x], rs[y], mid + 1, r, p, v);
	}
	void Ask(int x, int l, int r, int L, int R, int p) {
		if (!x) return; if (l >= L && r <= R) return Link(p, x, 0); int mid = (l + r) >> 1;
		if (L <= mid) Ask(ls[x], l, mid, L, R, p); if (mid < R) Ask(rs[x], mid + 1, r, L, R, p);
	}
} using namespace SGT;
struct O {
	int x, y; O(int x = 0, int y = 0) : x(x), y(y) {}
} a[V], s, t;
struct L {
	O x, y; L() {} L(O x, O y) : x(x), y(y) {}
} p1[N], p2[N]; int N1, N2;
struct Qr {
	int x, y, z;
	Qr(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
	friend bool operator < (const Qr &a, const Qr &b) {
		return a.x < b.x;
	}
} q1[N], q2[N]; int M1, M2;
bool cmp1(const O &a, const O &b) {
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}
bool cmp2(const O &a, const O &b) {
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}
int ln, lm, n, Q, X[N], tX, Y[N], tY;
void Work1() {
	sort(a + 1, a + 1 + n, cmp1);
	for (int i = 1, j = 1, k; i <= tX; i++)
		if (a[j].x == i) {
			for (k = j; k <= n && a[k].x == i; ++k);
			if (a[j].y > 1) p1[++N1] = L(O(i, 1), O(i, a[j].y - 1));
			for (; j + 1 < k; j++) if (a[j].y + 1 < a[j + 1].y) p1[++N1] = L(O(i, a[j].y + 1), O(i, a[j + 1].y - 1));
			if (a[j].y < tY) p1[++N1] = L(O(i, a[j].y + 1), O(i, tY)); j++;
		}
		else p1[++N1] = L(O(i, 1), O(i, tY));
		for (int i = 1; i <= N1; i++) {
			q1[++M1] = Qr(p1[i].x.y, p1[i].x.x, i); q1[++M1] = Qr(p1[i].y.y + 1, p1[i].y.x, 0);
		}
		sort(q1 + 1, q1 + 1 + M1);
}
void Work2() {
	sort(a + 1, a + 1 + n, cmp2);
	for (int i = 1, j = 1, k; i <= tY; i++)
		if (a[j].y == i) {
			for (k = j; k <= n && a[k].y == i; ++k);
			if (a[j].x > 1) p2[++N2] = L(O(1, i), O(a[j].x - 1, i));
			for (; j + 1 < k; j++) if (a[j].x + 1 < a[j + 1].x) p2[++N2] = L(O(a[j].x + 1, i), O(a[j + 1].x - 1, i));
			if (a[j].x < tX) p2[++N2] = L(O(a[j].x + 1, i), O(tX, i)); j++;
		}
		else p2[++N2] = L(O(1, i), O(tX, i));
		for (int i = 1; i <= N2; i++) {
			q2[++M2] = Qr(p2[i].x.x, p2[i].x.y, i + N1);
			q2[++M2] = Qr(p2[i].y.x + 1, p2[i].x.y, 0);
		}
		sort(q2 + 1, q2 + 1 + M2);
}
int Gx(O x) {
	int l = 0, r = N1, mid;
	while (l < r - 1) {
		mid = (l + r) >> 1; if (cmp1(p1[mid].y, x)) l = mid; else r = mid;
	}
	return r;
}
int Gy(O x) {
	int l = 0, r = N2, mid;
	while (l < r - 1) {
		mid = (l + r) >> 1; if (cmp2(p2[mid].y, x)) l = mid; else r = mid;
	}
	return r + N1;
}
int Q1[M], Q2[M], dis[M];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(ln); Read(lm); Read(n); Read(Q); X[++tX] = ln; Y[++tY] = lm;
	for (int i = 1; i <= n; i++) {
		Read(a[i].x); Read(a[i].y);  X[++tX] = a[i].x; Y[++tY] = a[i].y;
		if (a[i].x > 1) X[++tX] = a[i].x - 1; if (a[i].y > 1) Y[++tY] = a[i].y - 1;
	}
	Read(s.x); Read(s.y); X[++tX] = s.x; Y[++tY] = s.y;
	if (s.x > 1) X[++tX] = s.x - 1; if (s.y > 1) Y[++tY] = s.y - 1;
	sort(X + 1, X + tX + 1); sort(Y + 1, Y + tY + 1);
	tX = unique(X + 1, X + tX + 1) - X - 1; tY = unique(Y + 1, Y + tY + 1) - Y - 1;
	for (int i = 1; i <= n; i++) {
		a[i].x = lower_bound(X + 1, X + tX + 1, a[i].x) - X;
		a[i].y = lower_bound(Y + 1, Y + tY + 1, a[i].y) - Y;
	}
	s.x = lower_bound(X + 1, X + tX + 1, s.x) - X;
	s.y = lower_bound(Y + 1, Y + tY + 1, s.y) - Y;
	Work1(); Work2(); pT = N1 + N2;
	for (int i = 1, j = 1; i <= tX; i++) {
		r1[i] = r1[i - 1];
		for (; j <= M2 && q2[j].x == i; j++) Add(r1[i], r1[i], 1, tY, q2[j].y, q2[j].z);
	}
	for (int i = 1, j = 1; i <= tY; i++) {
		r2[i] = r2[i - 1];
		for (; j <= M1 && q1[j].x == i; j++) Add(r2[i], r2[i], 1, tX, q1[j].y, q1[j].z);
	}
	for (int i = N1 + N2 + 1; i <= pT; i++) {
		if (ls[i]) Link(i, ls[i], 0); if (rs[i]) Link(i, rs[i], 0); if (d[i]) Link(i, d[i], 1);
	}
	for (int i = 1; i <= N1; i++) Ask(r1[p1[i].x.x], 1, tY, p1[i].x.y, p1[i].y.y, i);
	for (int i = 1; i <= N2; i++) Ask(r2[p2[i].x.y], 1, tX, p2[i].x.x, p2[i].y.x, i + N1);
	memset(dis, -1, sizeof(dis));
	int  h1(0), t1(0), h2(0), t2(0);
	int u = Gx(s), v = Gy(s); Q1[t1++] = u; Q1[t1++] = v;
	dis[u] = dis[v] = 0;
	while (h1 != t1) {
		h2 = t2 = 0; Q2[t2++] = Q1[h1++];
		while (h2 != t2) {
			int u = Q2[h2++];
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to; if (!~dis[v]) if (edge[i].v) dis[Q1[t1++] = v] = dis[u] + 1;
				else dis[Q2[t2++] = v] = dis[u];
			}
		}
	}
	while (Q--) {
		Read(t.x); Read(t.y);
		t.x = lower_bound(X + 1, X + tX + 1, t.x) - X;
		t.y = lower_bound(Y + 1, Y + tY + 1, t.y) - Y;
		printf("%d\n", min(dis[Gx(t)], dis[Gy(t)]));
	}
	return 0;
}
