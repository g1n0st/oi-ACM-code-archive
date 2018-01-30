#include <bits/stdc++.h>
using namespace std;
typedef unsigned U;
const int V = 100010;
const int B = V / 32 + 1;
const int vM = V / 3;
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
int cnt[65536];
struct Bitset {
	U a[B];
	void set0() {
		memset(a, 0, sizeof a);
	}
	void set1() {
		memset(a, -1, sizeof a);
	}
	void operator &= (Bitset b) {
		for (int i = 0; i < B; i++) a[i] &= b.a[i];
	}
	void operator ^= (int x) {
		a[x >> 5] ^= (1u << (x & 31));
	}
	int count() {
		int r = 0;
		for (int i = 0; i < B; i++)
			r += cnt[(a[i] & 65535)] + cnt[(a[i] >> 16)];
		return r;
	}
} ans[vM + 10], now;
int N, M, a[V], b[V], bel[V], Block;
int t[V], Ans[vM + 10];
struct Node {
	int l, r, id;
	void Set(int x) {
		Read(l); Read(r); id = x; Ans[x] += r - l + 1;
	}
	friend bool operator < (const Node &a, const Node &b) {
		if (bel[a.l] ^ bel[b.l]) return a.l < b.l;
		return (bel[a.l] ^ 1) ? a.r < b.r : a.r > b.r;
	}
} v[V + 10]; int tot;
void Pre() {
	for (int i = 1; i < 65536; i++) cnt[i] = cnt[i >> 1] + (i & 1);
	Block = sqrt(N);
	for (int i = 1; i <= N; i++) bel[i] = (i - 1) / Block + 1;
}
void Add(int x) {
	now ^= (x + t[x]); t[x]++;
}
void Del(int x) {
	t[x]--; now ^= (x + t[x]);
}
void Solve(int m) {
	now.set0(); tot = 0;
	for (int i = 1; i <= m; i++) {
		ans[i].set1(); Ans[i] = 0;
		v[++tot].Set(i); v[++tot].Set(i); v[++tot].Set(i);
	}
	memset(t, 0, sizeof t);
	sort(v + 1, v + 1 + tot);
	int L = 1, R = 0;
	for (int i = 1; i <= tot; i++) {
		while (L > v[i].l) --L, Add(a[L]);
		while (L < v[i].l) Del(a[L]), L++;
		while (R < v[i].r) ++R, Add(a[R]);
		while (R > v[i].r) Del(a[R]), R--;
		ans[v[i].id] &= now;
	}
	for (int i = 1; i <= m; i++) Ans[i] -= 3 * ans[i].count();
	for (int i = 1; i <= m; i++) printf("%d\n", Ans[i]);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	Read(N); Read(M); Pre();
	for (int i = 1; i <= N; i++) {
		Read(a[i]); b[i] = a[i];
	}
	sort(b + 1, b + 1 + N);
	for (int i = 1; i <= N; i++) a[i] = lower_bound(b + 1, b + 1 + N, a[i]) - b - 1;
	if (M >= vM) Solve((M -= vM, vM));
	if (M >= vM) Solve((M -= vM, vM));
	if (M) Solve(M);
	return 0;
}
