#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int V = 5000010 * 4;
const LL oo = 0xcfcfcfcfcfcfcfcfLL;
void Read(int &x) {
	scanf("%d", &x);
}
LL mx[V], m2[V], v1[V], v2[V];
int N, M, a[V];
void Cal(int o, LL a, LL b, LL c, LL d) {
	mx[o] = max(mx[o], v1[o] + a);
	m2[o] = max(m2[o], max(v2[o] + a, b));
	v1[o] = max(v1[o] + c, oo);
	v2[o] = max(v2[o] + c, d);
}
void pushDown(int o) {
	Cal(o << 1, mx[o], m2[o], v1[o], v2[o]);
	Cal(o << 1 | 1, mx[o], m2[o], v1[o], v2[o]);
	mx[o] = m2[o] = v1[o] = v2[o] = 0;
}
void Cha(int o, int l, int r, int L, int R, int op, int x) {
	if (l >= L && r <= R) {
		if (op == 1) Cal(o, x, 0, x, 0);
		if (op == 2) Cal(o, 0, 0, -x, 0);
		if (op == 3) Cal(o, 0, x, oo, x);
		return;
	}
	pushDown(o);
	int Mid = (l + r) >> 1;
	if (L <= Mid) Cha(o << 1, l, Mid, L, R, op, x);
	if (Mid < R) Cha(o << 1 | 1, Mid + 1, r, L, R, op, x);
}
LL Que(int o, int l, int r, int p, int op) {
	if (l == r) {
		if (op == 4) return max(a[l] + v1[o], v2[o]);
		else return max(a[l] + mx[o], m2[o]);
	}
	pushDown(o);
	int Mid = (l + r) >> 1;
	if (p <= Mid) return Que(o << 1, l, Mid, p, op);
	else return Que(o << 1 | 1, Mid + 1, r, p, op);
}
int main() {
	int i, j;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(M);
	for (i = 1; i <= N; i++) Read(a[i]);
	int op, l, r, x;
	while (M--) {
		Read(op);
		if (op <= 3) {
			Read(l); Read(r); Read(x);
			Cha(1, 1, N, l, r, op, x);
		}
		else {
			Read(x); printf("%lld\n", Que(1, 1, N, x, op));
		}
	}
	return 0;
}
