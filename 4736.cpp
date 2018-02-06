#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const int V = 400010;
const int INF = 1 << 30;
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
void Read(char &x) {
	x = get(); while (!islower(x)) x = get();
}
int n, m, val[V];
namespace LCT {
	LL w[V], sum[V];
	int c[V][2], fa[V], rev[V], p[V];
	int Rt(int x) {
		return c[fa[x]][0] != x && c[fa[x]][1] != x;
	}
	void pushDown(int x) {
		int &l = c[x][0], &r = c[x][1];
		if (rev[x]) {
			rev[l] ^= 1; rev[r] ^= 1; rev[x] ^= 1; swap(l, r);
		}
	}
	void pushUp(int x) {
		int l = c[x][0], r = c[x][1];
		sum[x] = sum[l] + sum[r] + w[x]; p[x] = x;
		if (l && val[p[l]] < val[p[x]]) p[x] = p[l];
		if (r && val[p[r]] < val[p[x]]) p[x] = p[r];
 	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
		if (!Rt(y)) {
			if (c[z][0] == y) c[z][0] = x;
			else c[z][1] = x;
		}
		fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
		c[y][l] = c[x][r]; c[x][r] = y;
		pushUp(y); pushUp(x);
	}
	int s[V], t;
	namespace func {
		void splay(int x) {
			s[++t] = x;
			for (int i = x; !Rt(i); i = fa[i]) s[++t] = fa[i];
			while (t) pushDown(s[t--]);
			while (!Rt(x)) {
				int y = fa[x], z = fa[y];
				if (!Rt(y)) {
					if ((c[z][0] == y) ^ (c[y][0] == x)) rotate(x);
					else rotate(y);
				}
				rotate(x);
			}
		}
		void access(int x) {
			for (int t = 0; x; t = x, x = fa[x]) {
				splay(x); c[x][1] = t; pushUp(x);
			}
		}
		void rever(int x) {
			access(x); splay(x);  rev[x] ^= 1;
		}
		void link(int x, int y) {
			rever(x); fa[x] = y;
		}
		void cut(int x, int y) {;
			rever(x); access(y); splay(y);
			c[y][0] = fa[x] = 0;
		}
		int find(int x) {
			access(x); splay(x);
			while (c[x][0]) x = c[x][0];
			return x;
		}
		int getmn(int x, int y) {
			rever(x); access(y); splay(y);
			return p[y];
		}
	}
}
using namespace LCT::func;
PI e[V];
void Find() {
	int id, u, v, t, l;
	Read(id); Read(u); Read(v); Read(t); Read(l); u++; v++;
	e[id] = PI(u, v); id += n + 1;
	val[id] = t; LCT::p[id] = id; LCT::w[id] = LCT::sum[id] = l;
	if (find(u) ^ find(v)) {
		link(id, u); link(id, v);
	}
	else {
		int p = getmn(u, v);
		if (val[p] < t) {
			cut(p, e[p - n - 1].first); cut(p, e[p - n - 1].second); 
			link(id, u); link(id, v);
		}
	}
}
void Modify() {
	int id, w; Read(id); Read(w); id += n + 1;
	LCT::w[id] = w; splay(id);
}
void Query() {
	int x, y; Read(x); Read(y); x++; y++;
	if (find(x) ^ find(y)) return (void)printf("-1\n");
	rever(x); access(y); splay(y);
	printf("%lld\n", LCT::sum[y]);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	for (int i = 1; i <= n; i++) val[i] = INF;
	char op;
	while (m--) {
		Read(op);
		switch (op) {
		case 'f': Find(); break;
		case 'm': Query(); break;
		default: Modify();
		}
	}
	return 0;
}
