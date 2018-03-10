#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
typedef pair<PI, int> PII;
typedef pair<int, LL> PL;
const int V = 300010;
void Min(int &x, int y) {
	x = min(x, y);
}
void Max(int &x, int y) {
	x = max(x, y);
}
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
struct SGT {
	LL val[V << 2]; int tag[V << 2];
	void set0(int x, int len, int v) {
		val[x] += (LL)len * v; tag[x] += v;
	}
	void pushDown(int o, int l, int r) {
		if (tag[o] && l < r) {
			int mid = (l + r) >> 1;
			set0(o << 1, mid - l + 1, tag[o]); set0(o << 1 | 1, r - mid, tag[o]); tag[o] = 0;
		}
	}
	void pushUp(int o) {
		val[o] = val[o << 1] + val[o << 1 | 1];
	}
	void add(int o, int l, int r, int L, int R) {
		if (l >= L && r <= R) return set0(o, r - l + 1, 1);
		int mid = (l + r) >> 1; pushDown(o, l, r);
		if (L <= mid) add(o << 1, l, mid, L, R);
		if (mid < R) add(o << 1 | 1, mid + 1, r, L, R);
		pushUp(o);
	}
	LL query(int o, int l, int r, int L, int R) {
		if (l == L && r == R) return val[o];
		int mid = (l + r) >> 1; pushDown(o, l, r);
		if (R <= mid) return query(o << 1, l, mid, L, R);
		if (mid < L) return query(o << 1 | 1, mid + 1, r, L, R);
		return query(o << 1, l, mid, L, mid) + query(o << 1 | 1, mid + 1, r, mid + 1, R);
	}
	int n; SGT(int n = 0) : n(n) {}
	void add(int l, int r) {
		add(1, 1, n, l, r);
	}
	LL query(int l, int r) {
		return query(1, 1, n, l, r);
	}
} t3, t2;
int n, Q, p[V];
PII q[V];
/*
|
1 | 0
---+---
2 | 3
|
*/
int s[V], t, f[4][V];
int deg[V], liml[V], limr[V], r4[V], r3[V];
void Link(int u, int v) {
	++deg[u]; ++deg[v]; Min(liml[v], u); Max(limr[u], v);
}
void Pre() {
	t = 0; for (int i = 1; i <= n; i++) {
		while (t && p[s[t]] < p[i]) --t; f[1][i] = s[t]; s[++t] = i;
	}
	t = 0; for (int i = n; i; i--) {
		while (t && p[s[t]] < p[i]) --t; f[0][i] = s[t]; s[++t] = i;
	}
	t = 0; for (int i = 1; i <= n; i++) {
		while (t && p[s[t]] > p[i]) --t; f[2][i] = s[t]; s[++t] = i;
	}
	t = 0; for (int i = n; i; i--) {
		while (t && p[s[t]] > p[i]) --t; f[3][i] = s[t]; s[++t] = i;
	}
	memset(liml, 0x3f, sizeof liml);
	for (int i = 1; i <= n; i++) {
		if (f[3][i]) Link(i, f[3][i]); if (f[0][i]) Link(i, f[0][i]);
		if (f[1][i] && f[3][f[1][i]] != i) Link(f[1][i], i);
		if (f[2][i] && f[0][f[2][i]] != i) Link(f[2][i], i);
	}
	for (int i = 1; i <= n; i++) r4[i] = n + 1;
	for (int i = 1; i <= n; i++)
		if (f[0][i] && f[1][i] && f[2][i] && f[3][i] && (deg[i] & 1)) {
			Min(r4[liml[i]], limr[i]);
		}
	for (int i = n - 1; i; i--) Min(r4[i], r4[i + 1]);
	r3[n] = n + 1;
	for (int i = n - 1; i; i--) {
		r3[i] = r3[i + 1];
		if (i < n - 1 && ((p[i] - p[i + 1] > 0) ^ (p[i + 1] - p[i + 2] > 0))) r3[i] = i + 2;
	}
}
int Solve0() {
	return n == 1 ? 1 : (r3[1] == n + 1 ? 2 : (r4[1] == n + 1 ? 3 : 4));
}
PL ans[V];
void Solve() {
	for (int i = Q, j = n; i; i--) {
		int id = q[i].second, l = q[i].first.first, r = q[i].first.second, len = r - l + 1;
		while (j >= 1 && j >= l) {
			if (r3[j] > j + 1) t2.add(j + 1, r3[j] - 1);
			if (r4[j] > r3[j]) t3.add(r3[j], r4[j] - 1);
			j--;
		}
		if (len == 1) ans[id] = PL(1, 1LL);
		else if (r < r3[l]) ans[id] = PL(2, (LL)len * (len + 1) / 2 - len);
		else if (r < r4[l]) ans[id] = PL(3, t3.query(l, r));
		else ans[id] = PL(4, (LL)len * (len + 1) / 2 - len - t2.query(l, r) - t3.query(l, r));
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); t2.n = t3.n = n;
	for (int i = 1; i <= n; i++) Read(p[i]);
	int l, r; Read(Q);
	for (int i = 1; i <= Q; i++) {
		Read(l); Read(r); q[i] = PII(PI(l, r), i);
	}
	sort(q + 1, q + 1 + Q);
	Pre();
	printf("%d\n", Solve0());
	Solve();
	for (int i = 1; i <= Q; i++) {
		printf("%d %lld\n", ans[i].first, ans[i].second);
	}
	return 0;
}
