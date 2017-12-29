#include <bits/stdc++.h>
using namespace std;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}

int N, M, B, a[V], block[V], Ans[V];
set<int> S;
multiset<int> S1;
struct Node {
	int l, r, id;
	friend bool operator < (const Node &a, const Node &b) {
		if (block[a.l] != block[b.l]) return a.l < b.l;
		else if (block[a.l] & 1) return a.r < b.r;
		return a.r > b.r;
	}
} v[V];
void Add(int p) {
	S.insert(a[p]);
	set<int>::iterator it = S.find(a[p]);
	int ll = 0, rr = 0;
	if (it != S.begin()) {
		--it; ll = *it;
		S1.insert(a[p] - *it); ++it;
	}
	if (++it != S.end()) {
		rr = *it;
		S1.insert(*it - a[p]);
	}
	if (ll && rr) S1.erase(S1.find(rr - ll));
}
void Del(int p) {
	set<int>::iterator it = S.find(a[p]);
	int ll = 0, rr = 0;
	if (it != S.begin()) {
		--it; ll = *it;
		S1.erase(S1.find(a[p] - *it)); ++it;
	}
	if (++it != S.end()) {
		rr = *it;
		S1.erase(S1.find(*it - a[p]));
	}
	if (ll && rr) S1.insert(rr - ll);
	S.erase(a[p]);
}
void Solve() {
	int L = 1, R = 0;
	for (int i = 1; i <= M; i++) {
		while (R < v[i].r) ++R, Add(R);
		while (L > v[i].l) --L, Add(L);
		while (R > v[i].r) Del(R), --R;
		while (L < v[i].l) Del(L), ++L;
		Ans[v[i].id] = *S1.begin();
	}
}
int main() {
	int i, j;
	Read(N); Read(M); B = sqrt(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]); block[i] = (i - 1) / B + 1;
	}
	for (i = 1; i <= M; i++) {
		Read(v[i].l); Read(v[i].r);
		v[i].id = i;
	}
	sort(v + 1, v + M + 1);
	Solve();
	for (i = 1; i <= M; i++) printf("%d\n", Ans[i]);
	return 0;
}
