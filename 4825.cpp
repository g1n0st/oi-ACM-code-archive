#include <bits/stdc++.h>
using namespace std;
const int V = 400000;
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
void Wt(int x) {
	printf("%d\n", x);
}
namespace LCT {
	int c[V][2], fa[V], siz[V], rev[V];
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
		siz[x] = 1;
		if (c[x][0]) siz[x] += siz[c[x][0]];
		if (c[x][1]) siz[x] += siz[c[x][1]];
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], l = c[y][1] == x, r = l ^ 1;
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
			access(x); splay(x); rev[x] ^= 1;
		}
		void link(int x, int y) {
			rever(x); fa[x] = y;
		}
		void cut(int x, int y) {
			rever(x); access(y);  splay(y); fa[x] = c[y][0] = 0;
		}
		int query(int x, int y) {
			rever(x); access(y); splay(y); return siz[y];
		}
	}
} using namespace LCT::func;
set<int> S;
map<int, int> C;
int prev(int x) {
	set<int>::iterator it = S.find(x);
	return it == S.begin() ? 0 : *--it;
}
int sufx(int x) {
	set<int>::iterator it = S.find(x);
	return ++it == S.end() ? 0 : *it;
}
int Q, Root, L[V], R[V], F[V], a[V], n;
void getMin() {
	int x = C[*S.begin()], y = R[x], z = F[x];
	Wt(query(x, Root)); if (x == Root) return;
	if (y) cut(x, y); cut(x, z); if (y) link(y, z);
	link(x, Root); R[x] = Root; F[x] = 0; F[Root] = x; Root = x;
	L[z] = y; if (y) F[y] = z;
}
void getMax() {
	int x = C[*S.rbegin()], y = L[x], z = F[x];
	Wt(query(x, Root)); if (x == Root) return; 
	if (y) cut(x, y); cut(x, z); if (y) link(y, z);
	link(x, Root); L[x] = Root; F[x] = 0; F[Root] = x; Root = x;
	R[z] = y; if (y) F[y] = z;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(Q);
	int op, x, p, s;
	while (Q--) {
		Read(op);
		switch(op) {
		case 1:
			Read(x); a[++n] = x; LCT::siz[n] = 1; S.insert(x); C[x] = n;
			if (!Root) {
				Root = n; Wt(1); break;
			}
			p = C[prev(x)], s = C[sufx(x)];
			if (p && !R[p]) R[p] = n, link(p, n), F[n] = p;
			if (s && !L[s]) L[s] = n, link(s, n), F[n] = s;
			Wt(query(Root, n)); break;
		case 2: getMin(); break;
		case 3: getMax(); break;
		case 4: getMin(); S.erase(S.begin());
			if (!L[Root] && !R[Root]) {
				Root = 0; break;
			}
			cut(Root, R[Root]); Root = R[Root]; F[Root] = 0; break;
		case 5: getMax(); S.erase(--S.end());
			if (!L[Root] && !R[Root]) {
				Root = 0; break;
			}
			cut(Root, L[Root]); Root = L[Root]; F[Root] = 0; break;
		}
	}
	return 0;
}
