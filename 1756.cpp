
#include <cstdio>
#include <algorithm>
using namespace std;
const int V = 500010 * 4;
void Read(int &x) {
	scanf("%d", &x);
}
int N, M, a[V];
struct Node {
	int tot, lm, rm, mx;
	Node() {}
	Node(int tot, int lm, int rm, int mx) : tot(tot), lm(lm), rm(rm), mx(mx) {}
} v[V];
Node Merge(Node a, Node b) {
	Node x;
	x.tot = a.tot + b.tot;
	x.lm = max(a.lm, a.tot + b.lm);
	x.rm = max(b.rm, b.tot + a.rm);
	x.mx = max(a.mx, b.mx);
	x.mx = max(x.mx, max(x.lm, x.rm));
	x.mx = max(x.mx, a.rm + b.lm);
	return x;
}
void Modify(int o, int l, int r, int p, int val) {
	if (l == r) {
		v[o] = Node(val, val, val, val);
		return;
	}
	int Mid = (l + r) >> 1;
	if (p <= Mid) Modify(o << 1, l, Mid, p, val);
	else Modify(o << 1 | 1, Mid + 1, r, p, val);
	v[o] = Merge(v[o << 1], v[o << 1 | 1]);
}
Node Query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return v[o];
	int Mid = (l + r) >> 1;
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	else if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	return Merge(Query(o << 1, l, Mid, L, Mid), Query(o << 1 | 1, Mid + 1, r, Mid + 1, R));
}
void Build(int o, int l, int r) {
	if (l == r) {
		v[o] = Node(a[l], a[l], a[l], a[l]);
		return;
	}
	int Mid = (l + r) >> 1;
	Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
	v[o] = Merge(v[o << 1], v[o << 1 | 1]);
}
int main() {
	int i, j;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(M);
	for (i = 1; i <= N; i++) Read(a[i]);
	Build(1, 1, N);
	int op, x, l, r, v;
	while (M--) {
		Read(op);
		if (op & 1) {
			Read(l); Read(r);
			if (l > r) swap(l, r);
			printf("%d\n", Query(1, 1, N, l, r).mx);
		}
		else {
			Read(x); Read(v);
			Modify(1, 1, N, x, v);
		}
	}
	return 0;
}
