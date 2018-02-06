#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
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
int tag[V << 2], val[V << 1];
void setv(int o, int v) {
	tag[o] = val[o] = v;
}
void pushDown(int o) {
	if (tag[o]) {
		setv(o << 1, tag[o]); setv(o << 1 | 1, tag[o]); tag[o] = 0;
	}
}
void Modify(int o, int l, int r, int L, int R, int v) {
	if (l >= L && r <= R) return setv(o, v);
	int Mid = (l + r) >> 1; pushDown(o);
	if (L <= Mid) Modify(o << 1, l, Mid, L, R, v);
	if (Mid < R) Modify(o << 1 | 1, Mid + 1, r, L, R, v);
}
int Query(int o, int l, int r, int p) {
	if (l == r) return val[o];
	int Mid = (l + r) >> 1; pushDown(o);
	if (p <= Mid) return Query(o << 1, l, Mid, p);
	else return Query(o << 1 | 1, Mid + 1, r, p);
}
int N, L[V], R[V], a[V * 5], tot, vis[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N);
	for (int i = 1; i <= N; i++) {
		Read(L[i]); Read(R[i]); a[++tot] = L[i]; a[++tot] = R[i];
	}
	sort(a + 1, a + 1 + tot); tot = unique(a + 1, a + 1 + tot) - a - 1;
	for (int i = 1; i <= N; i++) {
		L[i] = lower_bound(a + 1, a + tot + 1, L[i]) - a;
		R[i] = lower_bound(a + 1, a + tot + 1, R[i]) - a;
		Modify(1, 1, tot, L[i], R[i], i);
	}
	int ans = 0;
	for (int i = 1; i <= tot; i++) {
		int x = Query(1, 1, tot, i);
		if (x && !vis[x]) {
			vis[x] = 1; ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
