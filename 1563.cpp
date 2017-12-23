#include <bits/stdc++.h>
using namespace std;
const int V = 120000;
typedef long double ld;
int Q, N, L, P;
ld f[V], s[V];
char str[V];
ld Pow(ld x, int y) {
	if (x < 0) x = -x;
	ld Ret = 1;
	while (y) {
		if (y & 1) Ret = Ret * x;
		y >>= 1;
		if (y) x = x * x;
	}
	return Ret;
}
ld cal(int i, int j) {
	return f[j] + Pow(s[i] - s[j] + i - j - 1 - L, P);
}
struct Node {
	int l, r, id;
	Node(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id) {}
} q[V];
int S, T;
void Solve() {
	int i, j;
	scanf("%d%d%d", &N, &L, &P);
	for (i = 1; i <= N; i++) {
		scanf("%s", str);
		s[i] = s[i - 1] + strlen(str);
	}
	q[S = T = 0] = Node(1, N, 0);
	for (i = 1; i <= N; i++) {
		while (i > q[S].r) ++S;
		f[i] = cal(i, q[S].id);
		if (cal(N, i) > cal(N, q[T].id)) continue;
		while (i < q[T].l && cal(q[T].l, i) < cal(q[T].l, q[T].id)) --T;
		int L = max(q[T].l, i + 1), R = q[T].r, Mid, Pos = min(q[T].r + 1, N);
		while (L <= R) {
			Mid = (L + R) >> 1;
			if (cal(Mid, i) < cal(Mid, q[T].id)) R = (Pos = Mid) - 1;
			else L = Mid + 1;
		}
		q[T].r = Pos - 1;
		q[++T] = Node(Pos, N, i);
	}
	if (f[N] > 1e18) printf("Too hard to arrange\n");
	else printf("%lld\n", (long long)f[N]);
	printf("--------------------\n");
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d", &Q);
	while (Q--) Solve();
	return 0;
}
