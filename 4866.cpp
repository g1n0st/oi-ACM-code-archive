#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
const int V = 60010;
typedef long long LL;
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
		x = x * 10 + c - '0';
		c = get();
	}
}
void Read(char *s) {
	int cnt = 0; static char c;
	while (c > 'z' || c < 'a') c = get();
	while (c >= 'a' && c <= 'z') {
		s[cnt++] = c; c = get();
	}
}
int f[V * 30], cnt;
map<int, int> G;
LL Ans[V], Now;
int N, M, B, bel[V], a[V][30];
char c[V];
struct Node {
	int l, r, id;
	friend bool operator < (const Node x, const Node y) {
		return bel[x.l] < bel[y.l] ||
			(bel[x.l] == bel[y.l] && (bel[x.l] & 1 ? x.r < y.r : x.r > y.r));
	}
} v[V];
void Add(int *x) {
	for (int i = 0; i < 27; i++) Now += f[x[i]];
	f[x[26]]++;
}
void Del(int *x) {
	f[x[26]]--;
	for (int i = 0; i < 27; i++) Now -= f[x[i]];
}
void Solve() {
	int L = 1, R = 0, i, j;
	for (i = 1; i <= M; i++) {
		while (L > v[i].l) L--, Add(a[L]);
		while (R < v[i].r) R++, Add(a[R]);
		while (L < v[i].l) Del(a[L]), L++;
		while (R > v[i].r) Del(a[R]), R--;
		Ans[v[i].id] = Now;
	}
}
int main() {
	int i, j; G.clear();
	Read(N); Read(M); B = sqrt(N);
	Read(c + 1);
	for (i = 1; i <= N; i++) {
		bel[i] = (i - 1) / B + 1;
		a[i][26] = a[i - 1][26] ^ (1 << (c[i] - 'a'));
	}
	for (i = 0; i <= N; i++)
		for (j = 0; j < 26; j++) a[i][j] = a[i][26] ^ (1 << j);
	for (i = 0; i <= N; i++)
		for (j = 0; j < 27; j++) {
			if (!G.count(a[i][j])) G[a[i][j]] = ++cnt;
			a[i][j] = G[a[i][j]];
		}
	for (i = 1; i <= M; i++) {
		Read(v[i].l); Read(v[i].r);
		v[i].l--; v[i].id = i;
	}
	sort(v + 1, v + 1 + M);
	Solve();
	for (i = 1; i <= M; i++) printf("%lld\n", Ans[i]);
	return 0;
}
