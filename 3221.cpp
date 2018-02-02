#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
typedef long long LL;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T>
void Read(T &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
char GetC() {
	char c = get();
	while (!islower(c)) c = get();
	return c;
}
LL gs(LL a, LL b, LL l) {
	return a * l + l * (l - 1) / 2 * b;
}
namespace SGT {
	const int N = V * 200;
	int rt[N], ls[N], rs[N], pT;
	LL vA[N], vB[N], sum[N];
	void Upd(int &x, int y, int l, int r, int L, int R, LL A, LL B) {
		x = ++pT;
		ls[x] = ls[y]; rs[x] = rs[y];
		sum[x] = sum[y] + gs(A, B, R - L + 1); vA[x] = vA[y]; vB[x] = vB[y];
		if (l == L && r == R) {
			vA[x] += A; vB[x] += B; return;
		}
		int Mid = (l + r) >> 1;
		if (R <= Mid) return Upd(ls[x], ls[y], l, Mid, L, R, A, B);
		if (Mid < L) return Upd(rs[x], rs[y], Mid + 1, r, L, R, A, B);
		LL rA = (Mid - L + 1) * B + A;
		Upd(ls[x], ls[y], l, Mid, L, Mid, A, B);
		Upd(rs[x], rs[y], Mid + 1, r, Mid + 1, R, rA, B);
	}
	LL Qur(int x, int l, int r, int L, int R) {
		if (!x) return 0;
		if (l == L && r == R) return sum[x];
		LL ths = gs(vA[x], vB[x], R - l + 1) - gs(vA[x], vB[x], (L - 1) - l + 1);
		int Mid = (l + r) >> 1;
		if (R <= Mid) return ths + Qur(ls[x], l, Mid, L, R);
		if (Mid < L) return ths + Qur(rs[x], Mid + 1, r, L, R);
		return ths + Qur(ls[x], l, Mid, L, Mid) + Qur(rs[x], Mid + 1, r, Mid + 1, R);
	}
}
using SGT::rt; using SGT::Upd; using SGT::Qur;

int N, M, Tot, Now; LL lstAns;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}

int siz[V], dep[V], fa[V], top[V], pos[V], pT;
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; dep[v] = dep[u] + 1; Dfs1(v); siz[u] += siz[v];
	}
}
void Dfs2(int u, int path) {
	pos[u] = ++pT; top[u] = path;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return; Dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && v ^ k) Dfs2(v, v);
	}
}
int lca(int x, int y) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return pos[x] < pos[y] ? x : y;
}

void Modify(int tar, int pre, int x, int y, LL A, LL B) {
	int g = 0;
	int l = lca(x, y);
	while (top[x] ^ top[l]) {
		LL tA = (dep[x] - dep[top[x]]) * B + A;
		Upd(rt[tar], rt[g ? tar : pre], 1, N, pos[top[x]], pos[x], tA, -B), g = 1;
		x = fa[top[x]]; A = tA + B;
	}
	LL fA = (dep[x] - dep[l]) * B + A;
	if (x ^ l) {
		Upd(rt[tar], rt[g ? tar : pre], 1, N, pos[l] + 1, pos[x], fA - B, -B), g = 1;
	}
	while (top[y] ^ top[l]) {
		LL tA = (dep[top[y]] - dep[l]) * B + fA;
		Upd(rt[tar], rt[g ? tar : pre], 1, N, pos[top[y]], pos[y], tA, B), g = 1;
		y = fa[top[y]];
	}
	if (y ^ l) {
		Upd(rt[tar], rt[g ? tar : pre], 1, N, pos[l] + 1, pos[y], fA + B, B), g = 1;
	}
	Upd(rt[tar], rt[g ? tar : pre], 1, N, pos[l], pos[l], fA, 0);
}
LL Query(int tar, int x, int y) {
	LL r = 0;
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		r += Qur(rt[tar], 1, N, pos[top[y]], pos[y]); y = fa[top[y]];
	}
	if (pos[x] > pos[y]) swap(x, y);
	r += Qur(rt[tar], 1, N, pos[x], pos[y]);
	return r;
}
int main() {
	//freopen("3221.in", "r", stdin);
	//freopen("3221.out", "w", stdout);
	Read(N); Read(M);
	char op; LL x, y, A, B;
	for (int i = 1; i < N; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	Dfs1(1); Dfs2(1, 1);
	while (M--) {
		op = GetC();
		if (op == 'c') {
			Read(x); Read(y); Read(A); Read(B); x ^= lstAns; y ^= lstAns;
			Modify(++Tot, Now, x, y, A, B); Now = Tot;
		}
		else if (op == 'q') {
			Read(x); Read(y); x ^= lstAns; y ^= lstAns;
			printf("%lld\n", lstAns = Query(Now, x, y));
		}
		else {
			Read(x); x ^= lstAns;
			Now = x;
		}
	}
	return 0;
}
