#include "rts.h"
#include <bits/stdc++.h>
using namespace std;
const int V = 3000010;
namespace LCT {
	int c[V][2], rev[V], fa[V], L[V], R[V];
	bool rt(int x) {
		return c[fa[x]][0] != x && c[fa[x]][1] != x;
	}
	void pushUp(int x) {
		L[x] = R[x] = x;
		if (c[x][0]) L[x] = L[c[x][0]];
		if (c[x][1]) R[x] = R[c[x][1]];
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
		if (!rt(y)) {
			if (c[z][0] == y) c[z][0] = x;
			else c[z][1] = x;
		}
		fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
		c[y][l] = c[x][r]; c[x][r] = y;
		pushUp(y); pushUp(x);
	}
	namespace func {
		void splay(int x) {
			while (!rt(x)) {
				int y = fa[x], z = fa[y];
				if (!rt(y)) {
					if ((c[y][0] == x) ^ (c[z][0] == y)) rotate(x);
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
	}
}
using namespace LCT::func;
int p[V], vis[V];
void play(int n, int T, int opt) {
	srand(19260817);
	for (int i = 1; i <= n; i++) LCT::L[i] = LCT::R[i] = i;
	for (int i = 1; i <= n; i++) p[i] = i;
	random_shuffle(p + 1, p + 1 + n);
	vis[1] = 1;
	if (opt == 3) {
		int l = 1, r = 1;
		for (int i = 1; i <= n; i++)
			if (!vis[p[i]]) {
				int rt = explore(l, p[i]), dir = 0;
				if (vis[rt]) rt = explore(r, p[i]), dir = 1;
				while (1) {
					vis[rt] = 1; if (rt == p[i]) break;
					rt = explore(rt, p[i]);
				}
				dir ? r = p[i] : l = p[i];
			}
		return;
	}
	for (int i = 1; i <= n; i++) if (!vis[p[i]]) {
		int rt = 1;
		while (1) {
			splay(rt);
			while (1) {
				int o = explore(rt, p[i]);
				if (o == LCT::R[LCT::c[rt][0]]) rt = LCT::c[rt][0];
				else if (o == LCT::L[LCT::c[rt][1]]) rt = LCT::c[rt][1];
				else {
					if (!vis[o]) vis[o] = 1, LCT::fa[o] = rt;
					rt = o; break;
				}
			}
			if (rt == p[i]) break;
		}
		access(rt);
	}
}
