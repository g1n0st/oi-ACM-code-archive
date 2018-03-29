#ifdef ONLINE_JUDGE
#include "mythological.h"
#endif
#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
const int N = V * 50;
int n, m, a[V], s[V], t;
int pT, rt[V << 2];
int fa[N], len[N]; map<int, int> c[N];
vector<int> rl[V << 2], rr[V << 2], vl[V << 2], vr[V << 2];
int head[N], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[N];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int dep[N], siz[N], top[N], pT1;
void dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		dep[v] = dep[u] + 1; dfs1(v); siz[u] += siz[v];
	}
}
void dfs2(int u, int path) {
	top[u] = path;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (siz[v] > siz[k]) k = v;
	}
	if (!k) return; dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v ^ k) dfs2(v, v);
	}
}
int lca(int x, int y) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}
void Build(int o, int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	int p = rt[o] = ++pT, cur = 0; t = 0;
	for (int i = mid; i >= l; i--) {
		s[++t] = a[i];
		if (t > 1 && s[t] == s[t - 1]) {
			t -= 2; cur++; p = fa[p];
		}
		else {
			if (!c[p].count(a[i])) {
				c[p][a[i]] = ++pT;
				len[pT] = len[p] + 1;
				fa[pT] = p;
				Add(p, pT);
			}
			p = c[p][a[i]];
		}
		rl[o].push_back(p); vl[o].push_back(cur);
	}
	t = 0; cur = 0; p = rt[o];
	for (int i = mid + 1; i <= r; i++) {
		s[++t] = a[i];
		if (t > 1 && s[t] == s[t - 1]) {
			t -= 2; cur++; p = fa[p];
		}
		else {
			if (!c[p].count(a[i])) {
				c[p][a[i]] = ++pT;
				len[pT] = len[p] + 1;
				fa[pT] = p;
				Add(p, pT);
			}
			p = c[p][a[i]];
		}
		rr[o].push_back(p); vr[o].push_back(cur);
	}
	dfs1(rt[o]); dfs2(rt[o], rt[o]);
	Build(o << 1, l, mid); Build(o << 1 | 1, mid + 1, r);
}
int Query(int o, int l, int r, int L, int R) {
	if (l == r) return 0;
	int mid = (l + r) >> 1;
	if (l <= L && R <= r && mid >= L && mid < R) {
		int p = mid - L, q = R - (mid + 1);
		return vl[o][p] + vr[o][q] + len[lca(rl[o][p], rr[o][q])];
	}
	if (R <= mid) return Query(o << 1, l, mid, L, R);
	else return Query(o << 1 | 1, mid + 1, r, L, R);
}
void init(int n, int m, int a[], int t) {
	::n = n; ::m = m;
	for (int i = 1; i <= n; i++) ::a[i] = a[i];
	Build(1, 1, n);
}

int query(int l, int r) {
	return Query(1, 1, n, l, r) * 2;
}

#ifndef ONLINE_JUDGE
int w, x, q, y, z[V];
void Read(int &x) {
	scanf("%d", &x);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(w); Read(x); Read(q); Read(y);
	for (int i = 1; i <= w; i++) Read(z[i]);
	init(w, x, z, y);
	int a, b;
	while (q--) {
		//printf("%d %d\n", a, b);
		Read(a); Read(b); printf("%d\n", query(a, b));
	}
	return 0;
}

#endif
