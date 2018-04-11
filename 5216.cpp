#include <bits/stdc++.h>
using namespace std;
const int N = 105;
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
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}

int n, m, Q;

struct E {
	int u, v, w;
} e[V << 2];

int fa[N];
int getf(int x) {
	return x == fa[x] ? x : fa[x] = getf(fa[x]);
}

int ans[V << 2][N], tmp[N][N], cnt;
void pushUp(int res[], int a[], int b[]) {
	int now = 0, p = 1, q = 1;
	for (int i = 1; i <= n; i++) fa[i] = i;
	while (now < n && (a[p] || b[q])) {
		while (now < n && a[p] && e[a[p]].w <= e[b[q]].w) {
			int fu = getf(e[a[p]].u), fv = getf(e[a[p]].v);
			if (fu != fv) fa[fu] = fv, res[++now] = a[p];
			++p;
		}
		while (now < n && b[q] && e[a[p]].w >= e[b[q]].w) {
			int fu = getf(e[b[q]].u), fv = getf(e[b[q]].v);
			if (fu != fv) fa[fu] = fv, res[++now] = b[q];
			++q;
		}
	}
	while (now < n && res[now]) res[++now] = 0;
}
void build(int o, int l, int r) {
	if (l == r) {
		ans[o][1] = r;
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	pushUp(ans[o], ans[o << 1], ans[o << 1 | 1]);
}
void query(int o, int l, int r, int L, int R, int now) {
	if (l == L && r == R) {
		for (int i = 1; i < n; i++) tmp[now][i] = ans[o][i];
		return;
	}
	int mid = (l + r) >> 1, ls = 0, rs = 0;
	if (R <= mid) query(o << 1, l, mid, L, R, ls = ++cnt);
	else if (mid < L) query(o << 1 | 1, mid + 1, r, L, R, rs = ++cnt);
	else {
		query(o << 1, l, mid, L, mid, ls = ++cnt);
		query(o << 1 | 1, mid + 1, r, mid + 1, R, rs = ++cnt);
	}
	if (ls && !rs) for (int i = 1; i < n; i++) tmp[now][i] = tmp[ls][i];
	if (!ls && rs) for (int i = 1; i < n; i++) tmp[now][i] = tmp[rs][i];
	if (ls && rs) pushUp(tmp[now], tmp[ls], tmp[rs]);
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Read(Q);
	for (int i = 1; i <= m; i++) {
		Read(e[i].u); Read(e[i].v); Read(e[i].w);
	}
	e[0].w = 1 << 30;
	build(1, 1, m);
	int l, r;
	while (Q--) {
		Read(l); Read(r); int Ans = 0;
		query(1, 1, m, l, r, cnt = 1);
		for (int i = 1; tmp[1][i]; i++) Ans += e[tmp[1][i]].w;
		printf("%d\n", Ans);
	}
	return 0;
}
