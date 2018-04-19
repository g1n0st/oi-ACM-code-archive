#include <cstdio>
#include <ctype.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

namespace __g1n0st_workspace__ {

	typedef long long LL;
	typedef std::pair<int, int> PI;

	const int V = 1000010;
	const int P = 998244353;

	// fast IO module
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
	char pbuf[V], *pp = pbuf;
	inline void push(const char c) {
		if (pp == pbuf + V) fwrite(pbuf, 1, V, stdout), pp = pbuf;
		*pp++ = c;
	}
	inline void Write(int x) {
		static char sta[20];
		int top = 0;
		if (!x) push('0');
		while (x) sta[++top] = x % 10 ^ '0', x /= 10;
		while (top) push(sta[top--]);
		push('\n');
	}
	inline void flush() {
		fwrite(pbuf, 1, pp - pbuf, stdout);
	}


	inline int Ksm(int x, int y) {
		int r = 1;
		while (y) {
			if (y & 1) r = (LL)r * x % P;
			y >>= 1; if (y) x = (LL)x * x % P;
		}
		return r;
	}
	int fac[V], ifac[V], pow[V], ipow[V];
	void Pre(int n, int T) {
		fac[0] = 1;
		for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % P;
		ifac[n] = Ksm(fac[n], P - 2);
		for (int i = n - 1; ~i; i--) ifac[i] = (LL)ifac[i + 1] * (i + 1) % P;
		pow[0] = 1;
		for (int i = 1; i <= n; i++) pow[i] = Ksm(i, T);
		ipow[0] = 1;
		for (int i = 1; i <= n; i++) ipow[i] = Ksm(pow[i], P - 2);
	}
	inline int C(int n, int k) {
		return (LL)fac[n] * ifac[k] % P * ifac[n - k] % P;
	}

	std::vector<PI> qr;

	// union-find sets
	int f[V];
	void init(int n) {
		for (int i = 1; i <= n; i++) f[i] = i;
	}
	int getf(int x) {
		return x == f[x] ? x : f[x] = getf(f[x]);
	}

	// segment tree maintain chain
	namespace SGT {
		int tag[V << 2], col[V << 2];
		inline void pushDown(int o) {
			if (tag[o]) {
				tag[o << 1] |= tag[o]; tag[o << 1 | 1] |= tag[o];
				col[o << 1] |= tag[o]; col[o << 1 | 1] |= tag[o];
				tag[o] = 0;
			}
		}
		void modify(int o, int l, int r, int L, int R) {
			if (l == L && r == R) {
				tag[o] = col[o] = 1; return;
			}
			pushDown(o);
			int mid = (l + r) >> 1;
			if (R <= mid) modify(o << 1, l, mid, L, R);
			else if (mid < L) modify(o << 1 | 1, mid + 1, r, L, R);
			else {
				modify(o << 1, l, mid, L, mid);
				modify(o << 1 | 1, mid + 1, r, mid + 1, R);
			}
			col[o] = col[o << 1] | col[o << 1 | 1];
		}
		int query(int o, int l, int r, int L, int R) {
			if (l == L && r == R) return col[o];
			pushDown(o);
			int mid = (l + r) >> 1;
			if (R <= mid) return query(o << 1, l, mid, L, R);
			if (mid < L) return query(o << 1 | 1, mid + 1, r, L, R);
			return query(o << 1, l, mid, L, mid) | query(o << 1 | 1, mid + 1, r, mid + 1, R);
		}
	}

	// tree
	int head[V], sub;
	struct Edge {
		int to, nxt;
		Edge() {}
		Edge(int to, int nxt) : to(to), nxt(nxt) {}
	} edge[V << 1];
	void Add(int a, int b) {
		edge[++sub] = Edge(b, head[a]); head[a] = sub;
	}
	int siz[V], dep[V], fa[V], top[V], pos[V], pT;
	void dfs1(int u) {
		siz[u] = 1;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (v == fa[u]) continue;
			fa[v] = u; dep[v] = dep[u] + 1; dfs1(v); siz[u] += siz[v];
		}
	}
	void dfs2(int u, int path) {
		pos[u] = ++pT; top[u] = path;
		int k = 0;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
		}
		if (!k) return;
		dfs2(k, path);
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (dep[v] > dep[u] && v != k) dfs2(v, v);
		}
	}
	int lca(int x, int y) {
		while (top[x] ^ top[y]) {
			if (dep[top[x]] > dep[top[y]]) std::swap(x, y);
			y = fa[top[y]];
		}
		return dep[x] < dep[y] ? x : y;
	}
	inline int dist(int x, int y) {
		return dep[x] + dep[y] - 2 * dep[lca(x, y)];
	}

	int n, m, T, W;
	int ans;

	int query(int x, int y) {
		int r = 0;
		while (top[x] != top[y]) {
			if (dep[top[x]] > dep[top[y]]) std::swap(x, y);
			r |= SGT::query(1, 1, n, pos[top[y]], pos[y]);
			y = fa[top[y]];
		}
		if (x == y) return r;
		if (pos[x] > pos[y]) std::swap(x, y);
		return r | SGT::query(1, 1, n, pos[x] + 1, pos[y]);
	}
	void modify(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] > dep[top[y]]) std::swap(x, y);
			SGT::modify(1, 1, n, pos[top[y]], pos[y]);
			y = fa[top[y]];
		}
		if (x == y) return;
		if (pos[x] > pos[y]) std::swap(x, y);
		return SGT::modify(1, 1, n, pos[x] + 1, pos[y]);
	}

	inline int calc_cir_w(int m) {
		return (LL)pow[n - m] * ipow[n] % P;
	}
	int calc_cir_b(int m) {
		int res = 0;
		for (int j = 0; j <= m; j++) {
			int val = (LL)C(m, j) * pow[n - j] % P * ipow[n] % P;
			if (j & 1) res = (res - val + P) % P;
			else res = (res + val) % P;
		}
		return res;
	}
	inline void add(int &x, int y) {
		x += y; if (x < 0) x += P; if (x > P) x -= P;
	}

	void __main__() {

		Read(n); Read(m); Read(T); Read(W);

		Pre(n, T);
		init(n);
		int x, y;
		for (int i = 1; i <= m; i++) {
			Read(x); Read(y);
			int r_x = getf(x), r_y = getf(y);
			if (r_x != r_y) {
				f[r_x] = r_y; Add(x, y); Add(y, x);
			}
			qr.emplace_back(PI(x, y));
		}
		for (int i = 1; i <= n; i++)
			if (!pos[i]) {
				dfs1(i); dfs2(i, i);
			}

		int ans = n;
		if (!W) ans = (LL)pow[n - 1] * ipow[n] % P * n % P;
		int edge_w = (LL)pow[n - 2] * ipow[n] % P;
		int edge_b = (1 - (LL)2 * pow[n - 1] % P * ipow[n] % P + P + edge_w) % P;

		init(n);
		for (auto v : qr) {
			x = v.first; y = v.second;

			int r_x = getf(x), r_y = getf(y);
			if (r_x != r_y) {
				f[r_x] = r_y;

				if (W) add(ans, -(edge_b + edge_w) % P);
				else add(ans, -edge_w);
			}
			else if (!query(x, y)) {

				if (W) ans = (ans - (edge_w + edge_b) % P + P) % P;
				else ans = (ans - edge_w + P) % P;

				modify(x, y);
				int val = dist(x, y) + 1;
				if (W) add(ans, (calc_cir_w(val) + calc_cir_b(val)) % P);
				else add(ans, calc_cir_w(val));
			}

			Write(ans);
		}
		flush();
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	__g1n0st_workspace__::__main__();

	return 0;
}
