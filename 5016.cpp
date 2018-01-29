#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100100;
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
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
LL Ans[V];
int a[V], bel[V], N, M, B;
struct Node {
	int l, r, f, id;
	Node(int l = 0, int r = 0, int f = 0, int id = 0) : l(l), r(r), f(f), id(id) {}
	friend bool operator < (const Node &a, const Node &b) {
		if (bel[a.l] ^ bel[b.l]) return a.l < b.l;
		else if (bel[a.l] & 1) return a.r < b.r;
		else return a.r > b.r;
	}
} v[V << 2]; int tot;
void Add(int l, int r, int f, int id) {
	//if (!l || !r) return; 
	v[++tot] = Node(l, r, f, id);
}
int S[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); B = sqrt(N);
	for (int i = 1; i <= N; i++) Read(a[i]);
	for (int i = 1; i <= N; i++) bel[i] = (i - 1) / B + 1;
	int l1, r1, l2, r2;
	Read(M);
	for (int i = 1; i <= M; i++) {
		Read(l1); Read(r1); Read(l2); Read(r2);
		Add(r1, r2, 1, i); Add(l1 - 1, l2 - 1, 1, i);
		Add(l1 - 1, r2, -1, i); Add(r1, l2 - 1, -1, i);
	}
	sort(v + 1, v + 1 + tot);
	int L = 0, R = 0; LL now = 0;
	for (int i = 1; i <= tot; i++) {
		while (L < v[i].l) L++, now += S[a[L]], S[a[L]]++;
		while (R < v[i].r) R++, now += S[a[R]], S[a[R]]++;
		while (L > v[i].l) S[a[L]]--, now -= S[a[L]], L--;
		while (R > v[i].r) S[a[R]]--, now -= S[a[R]], R--;
		Ans[v[i].id] += v[i].f * now;
	}
	for (int i = 1; i <= M; i++) printf("%lld\n", Ans[i]);
	return 0;
}
