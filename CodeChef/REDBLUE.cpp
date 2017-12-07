#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
const int V = 2010;
int Min(int a, int b) {
	return a < b ? a : b;
}
void Read(int &x) {
	scanf("%d", &x);
}
int T, N, M, Tot, isR[V], pos[V];

struct SGT {
	int Tag[V << 2], Mn[V << 2];
	void pushDown(int o) {
		if (Tag[o]) {
			Mn[o << 1] += Tag[o]; Mn[o << 1 | 1] += Tag[o];
			Tag[o << 1] += Tag[o]; Tag[o << 1 | 1] += Tag[o];
			Tag[o] = 0;
		}
	}
	void pushUp(int o) {
		Mn[o] = Min(Mn[o << 1], Mn[o << 1 | 1]);
	}
	void Modify(int o, int l, int r, int L, int R, int v) {
		if (L > R) return;
		if (l >= L && r <= R) {
			Mn[o] += v; Tag[o] += v;
			return;
		}
		int Mid = (l + r) >> 1;
		pushDown(o);
		if (L <= Mid) Modify(o << 1, l, Mid, L, R, v);
		if (Mid < R) Modify(o << 1 | 1, Mid + 1, r, L, R, v);
		pushUp(o);
	}
	void ToDif(int x) {
		Modify(1, 1, N, 1, x - 1, 1);
		Modify(1, 1, N, x, N, -1);
	}
	void ToSa(int x) {
		Modify(1, 1, N, 1, x - 1, -1);
		Modify(1, 1, N, x, N, 1);
	}
	void Init() {
		int i, j;
		for (i = 1; i <= N; i++) Modify(1, 1, N, i, i, i);
	}
	void Clear() {
		memset(Tag, 0, sizeof Tag);
		memset(Mn, 0, sizeof Mn);
		Tot = 0;
	}
} R, B;

struct P {
	int x, y, c;
	P() {}
	P(int x, int y, int c) : x(x), y(y), c(c) {}
	friend bool operator < (const P &a, const P &b) {
		if (a.x != b.x) return a.x < b.x;
		return a.y < b.y;
	}
} p[V];
struct E {
	int n1, n2, a, b;;
	E() {}
	E(int n1, int n2, int a, int b) : n1(n1), n2(n2), a(a), b(b) {}
	friend bool operator < (const E &a, const E &b) {
		if (1LL * a.n1 * b.n2 != 1LL * b.n1 * a.n2) {
			return 1LL * a.n1 * b.n2 > 1LL * b.n1 * a.n2;
		}
		if (a.b != b.b) return a.b < b.b;
		return a.a < b.a;
	}
} e[V * V];
void Swap(int a, int b) {
	int &x = pos[a], &y = pos[b];
	if (isR[x] ^ isR[y]) {
		if (isR[x]) {
			R.ToDif(x); B.ToSa(x);
			R.ToSa(y); B.ToDif(y);
		}
		else {
			R.ToSa(x); B.ToDif(x);
			R.ToDif(y); B.ToSa(y);
		}
		swap(isR[x], isR[y]);
	}
	swap(x, y);
}
void Clear() {
	R.Clear(); B.Clear();
	Tot = 0;
}
void Solve() {
	Clear();
	int i, j, x, y;
	Read(N); Read(M);
	for (i = 1; i <= N; i++) {
		Read(x); Read(y); p[++Tot] = P(x, y, 0);
	}
	for (i = 1; i <= M; i++) {
		Read(x); Read(y); p[++Tot] = P(x, y, 1);
	}
	N = Tot; M = 0;
	R.Init(); B.Init();
	sort(p + 1, p + 1 + N);
	for (i = 1; i <= N; i++) isR[i] = p[i].c;
	for (i = 1; i <= N; i++) pos[i] = i;
	for (i = 1; i <= N; i++) {
		if (isR[i]) B.ToDif(i);
		else R.ToDif(i);
	}
	for (i = 1; i <= N; i++)
		for (j = i + 1; j <= N; j++)
			e[++M] = E(p[i].y - p[j].y, p[i].x - p[j].x, i, j);
	sort(e + 1, e + 1 + M);
	int Ans = N;
	for (i = 1; i <= M; i++) {
		Swap(e[i].a, e[i].b);
		if (i < M && 1LL * e[i].n1 * e[i + 1].n2 == 1LL * e[i + 1].n1 * e[i].n2) continue;
		Ans = Min(Ans, R.Mn[1]);
		Ans = Min(Ans, B.Mn[1]);
	}
	printf("%d\n", Ans);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T);
	while (T--) Solve();
	return 0;
}
