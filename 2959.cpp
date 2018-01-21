#include <bits/stdc++.h>
using namespace std;
const int V = 1000010;
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

struct UFS {
	int f[V];
	int find(int x) {
		return f[x] == x ? x : f[x] = find(f[x]);
	}
	void merge(int x, int y) {
		x = find(x); y = find(y);
		f[x] = y;
	}
	void init(int n) {
		for (int i = 1; i <= n; i++) f[i] = i;
	}
} f1, f2;
namespace LCT {
	int fa[V], sum[V], val[V], c[V][2], rev[V], st[V], top;
	int Rt(int x) {
		int f = f1.find(fa[x]);
		return c[f][0] != x && c[f][1] != x;
	}
	int get(int x) {
		return c[f1.find(fa[x])][1] == x;
	}
	void pushUp(int x) {
		sum[x] = sum[c[x][0]] + sum[c[x][1]] + val[x];
	}
	void pushDown(int x) {
		int &l = c[x][0], &r = c[x][1];
		if (rev[x]) {
			rev[l] ^= 1; rev[r] ^= 1; rev[x] ^= 1; swap(l, r);
		}
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], l = get(x), r = l ^ 1;
		if (!Rt(y)) {
			if (c[z][0] == y) c[z][0] = x;
			else c[z][1] = x;
		}
		fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
		c[y][l] = c[x][r]; c[x][r] = y;
		pushUp(y); pushUp(x);
	}
	void splay(int x) {
		st[top = 1] = x;
		for (int i = x; !Rt(i); i = f1.find(fa[i])) st[++top] = f1.find(fa[i]);
		for (int i = top; i; i--) {
			pushDown(st[i]); fa[st[i]] = f1.find(fa[st[i]]);
		}
		while (!Rt(x)) {
			int y = fa[x];
			if (!Rt(y)) {
				if (get(x) ^ get(y)) rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
	}
	void access(int x) {
		int t = 0;
		while (x) {
			splay(x); c[x][1] = t; pushUp(x); t = x; x = f1.find(fa[x]);
		}
	}
	void rever(int x) {
		access(x); splay(x); rev[x] ^= 1;
	}
	void link(int x, int y) {
		rever(x); fa[x] = y;
	}
	void merge(int x, int y) {
		f1.merge(x, y); pushDown(x);
		if (x ^ y) val[y] += val[x];
		if (c[x][0]) merge(c[x][0], y);
		if (c[x][1]) merge(c[x][1], y);
		c[x][1] = c[x][0] = 0;
	}
	void work(int x, int y) {
		rever(x); access(y); splay(y); merge(y, y); pushUp(y);
	}
	void modify(int x, int v) {
		x = f1.find(x); access(x); splay(x); val[x] += v; pushUp(x);
	}
	int query(int x, int y) {
		rever(x); access(y); splay(y); return sum[y];
		return 0;
	}
}
int N, M, a[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Read(N); Read(M); f1.init(N); f2.init(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]); LCT::val[i] = a[i];
	}
	int op, x, y, fx, fy;
	while (M--) {
		Read(op); Read(x); Read(y);
		switch (op) {
		case 1:
			x = f1.find(x); y = f1.find(y);
			if (x == y) continue;
			fx = f2.find(x), fy = f2.find(y);
			if (fx == fy) LCT::work(x, y);
			else f2.f[fy] = fx; LCT::link(x, y);
			break;
		case 2: LCT::modify(x, y - a[x]); a[x] = y; break;
		default:
			x = f1.find(x); y = f1.find(y);
			if (f2.find(x) ^ f2.find(y)) printf("-1\n");
			else printf("%d\n", LCT::query(x, y));
		}
	}
	return 0;
}
