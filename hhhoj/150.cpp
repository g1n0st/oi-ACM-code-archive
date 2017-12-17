#include <bits/stdc++.h>
using namespace std;
typedef priority_queue<int> pq;
const int V = 400010, BV = 650;
int N, M, Q, a[V], bel[V], l[V], r[V]; 
pq q[BV], f[BV];
void Upd(int b, int l, int r, int &x) {
	pq em1; swap(em1, q[b]);
	for (int i = ::l[b]; i <= ::r[b]; i++) {
		f[b].push(-a[i]); a[i] = -f[b].top(); f[b].pop();
		if (i >= l && i <= r && a[i] > x) swap(a[i], x);
		q[b].push(a[i]);
	}
	pq em2; swap(em2, f[b]);
}
void Modify(int l, int r, int &x) {
	if (bel[l] == bel[r]) return Upd(bel[l], l, r, x);
	Upd(bel[l], l, r, x);
	for (int i = bel[l] + 1; i < bel[r]; i++) {
		f[i].push(-x); q[i].push(x); x = q[i].top(); q[i].pop();
	}
	Upd(bel[r], l, r, x);
}
int main() {
	int i, j, l, r, x;
	scanf("%d%d", &N, &Q); M = sqrt(N) + 1;
	for (i = 1; i <= N; i++) {
		bel[i] = (i - 1) / M + 1; scanf("%d", &a[i]); q[bel[i]].push(a[i]);
		::r[bel[i]] = i; if (!::l[bel[i]]) ::l[bel[i]] = i;
	}
	while (Q--) {
		scanf("%d%d%d", &l, &r, &x);
		(l <= r) ? Modify(l, r, x) : (Modify(l, N, x), Modify(1, r, x));
		printf("%d\n", x);
	}
	return 0;
}
