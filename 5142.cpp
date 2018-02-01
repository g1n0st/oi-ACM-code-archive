#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000010;
const int INF = 1 << 30;
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
int N, s[V], f[V]; LL M, pre[V];
int mx[V << 2];
void Build(int o, int l, int r) {
	if (l == r) {
		mx[o] = s[l]; return;
	}
	int Mid = (l + r) >> 1;
	Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
	mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
}
int Query(int o, int l, int r, int L, int R) {
	if (L > R) return INF;
	if (l == L && r == R) return mx[o];
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	return max(Query(o << 1, l, Mid, L, Mid), Query(o << 1 | 1, Mid + 1, r, Mid + 1, R));
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(M);
	for (int i = 1; i <= N; i++) {
		Read(f[i]); Read(s[i]);
	}
	for (int i = 1; i <= N; i++) pre[i] = pre[i - 1] + f[i];
	Build(1, 1, N);
	int Ans = INF;
	for (int i = 1, j = 0; i <= N; i++) {
		while (j <= N && pre[j] - pre[i - 1] < M) j++;
		if (j != N + 1) Ans = min(Ans, Query(1, 1, N, i, j));
	}
	printf("%d\n", Ans);
	return 0;
}
