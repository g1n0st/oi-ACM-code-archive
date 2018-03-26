#include <bits/stdc++.h>
using namespace std;
const int oo = 1 << 30;
const int V = 300010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c; int f = 0;
	for (; !isdigit(c); c = get()) if (c == '-') f = 1;
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
	if (f) x = -x;
}
void Wt(int x) {
	printf("%d\n", x);
}
int head[V], sub;
struct Edge {
	int to, nxt, v;
	Edge() {}
	Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
} edge[V << 1];
void Add(int a, int b, int v) {
	if (a == b) return;
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
void edge_clear(int n) {
	for (int i = 1; i <= n; i++) head[i] = 0; sub = 0;
}

int st[V], ed[V], dis[V], dep[V], fa[V], pT, stb[21][V];
void dfs(int u, int fa) {
	st[u] = ++pT; stb[0][pT] = u;
	dep[u] = dep[fa] + 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue;
		dis[v] = dis[u] + edge[i].v;
		::fa[v] = u; dfs(v, u);
	}
	ed[u] = pT;
}
inline int comp_dep(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}
int lg2[V];
void rmq_init(int n) {
	for (int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; (1 << i) <= n; i++)
		for (int j = 1; j <= n - (1 << i) + 1; j++)
			stb[i][j] = comp_dep(stb[i - 1][j], stb[i - 1][j + (1 << i - 1)]);
}
int lca(int x, int y) {
	if (st[x] > st[y]) swap(x, y);
	if (ed[x] >= ed[y]) return x;
	int l = st[x], r = st[y], k = lg2[r - l + 1];
	return fa[comp_dep(stb[k][l], stb[k][r - (1 << k) + 1])];
}
inline int dist(int x, int y) {
	return x == y ? 0 : (dis[x] + dis[y] - (dis[lca(x, y)] << 1));
}

int s[V], top;
int Tim, key[V], link[V], sec[V], id[V];
inline bool cmp(const int &x, const int &y) {
	return st[x] < st[y];
}
struct Virtual_tree {
	int tot;
	vector<int> up, down, cot;
	void dfs1(int u) {
		if (key[cot[u]] == Tim) {
			down[u] = 0; sec[u] = -oo;
		}
		for (int i = head[u], v, w; i; i = edge[i].nxt) {
			v = edge[i].to;
			dfs1(v); w = edge[i].v + down[v];
			if (w > down[u]) {
				sec[u] = down[u]; down[u] = w; link[u] = v;
			}
			else
				sec[u] = max(sec[u], w);
		}
	}
	void dfs2(int u) {
		for (int i = head[u], v, w; i; i = edge[i].nxt) {
			v = edge[i].to; w = edge[i].v;
			if (up[u] != -oo) up[v] = max(up[v], up[u] + w);
			if (key[cot[u]] == Tim) up[v] = max(up[v], w);
			int val = (link[u] == v ? sec[u] : down[u]);
			if (val != -oo) up[v] = max(up[v], val + w);
			dfs2(v);
		}
	}
	void rebuild(int l, int r) {
		static int s[V], t, a[V], n; n = t = 0; ++Tim;
		for (int i = l; i <= r; i++) {
			a[++n] = ::s[i]; key[a[n]] = Tim;
		}
		sort(a + 1, a + 1 + n, cmp);
		n = unique(a + 1, a + 1 + n) - (a + 1);

		int tn = n;
		for (int i = 1; i < tn; i++) a[++n] = lca(a[i], a[i + 1]);
		sort(a + 1, a + 1 + n, cmp);
		n = unique(a + 1, a + 1 + n) - (a + 1);
		tot = n;
		cot = { 0 };
		for (int i = 1; i <= n; i++) {
			id[a[i]] = i; cot.emplace_back(a[i]);
		}
		for (int i = 2; i <= n; i++) {
			int f = lca(a[i], a[i - 1]);
			Add(id[f], id[a[i]], dis[a[i]] - dis[f]);
		}

		up.resize(tot + 1, -oo);
		down.resize(tot + 1, -oo);
		dfs1(1); dfs2(1);

		edge_clear(tot);
	}
	int query(int x) {
		int su, pr;
		int p = lower_bound(cot.begin() + 1, cot.end(), x, cmp) - cot.begin();
		pr = p == 1 ? 0 : cot[p - 1];
		su = p == cot.size() ? 0 : cot[p];
		pr = lca(pr, x); su = lca(su, x);
		int f = dep[su] > dep[pr] ? su : pr;
		f = lower_bound(cot.begin() + 1, cot.end(), f, cmp) - cot.begin();

		int res = -oo;
		if (down[f] != -oo) res = max(res, dist(cot[f], x) + down[f]);
		if (up[f] != -oo) res = max(res, up[f] + dis[x] - dis[cot[f]]);
		return res;
	}
	void clear() {
		up.clear(); down.clear();
	}
} tr[V << 1];

namespace Binary_Divide {
	int limit, is2[V << 2], del[V << 2];
	void init(int Q) {
		for (limit = 1; limit < Q; limit <<= 1);
		for (int i = 0; i < limit; i++) del[i] = 1;
		for (int i = 1; i <= limit; i <<= 1) is2[i] = 1;
	}
	void insert(int rt = 1, int l = 1, int r = limit) {
		if (r - l <= 1) return;
		int mid = (l + r) >> 1;
		if (top <= mid) insert(rt << 1, l, mid);
		else insert(rt << 1 | 1, mid + 1, r);
		if (!is2[rt] && del[rt - 1] && r == top) {
			tr[rt - 1].rebuild(l - (r - l + 1), l - 1);
			del[rt - 1] = 0;
			del[rt] = 1;
			tr[rt].clear();
		}
	}
	void remove(int rt = 1, int l = 1, int r = limit) {
		if (r - l <= 1) return;
		int mid = (l + r) >> 1;
		tr[rt].clear(); del[rt] = 1;
		if (top <= mid) remove(rt << 1, l, mid);
		else remove(rt << 1 | 1, mid + 1, r);
	}
	int query(int L, int R, int x, int rt = 1, int l = 1, int r = limit) {
		if (l >= L && r <= R && !del[rt]) {
			if (l == r) return dist(s[l], x);
			if (l + 1 == r) return max(dist(s[l], x), dist(s[l + 1], x));
			return tr[rt].query(x);
		}
		int mid = (l + r) >> 1, res = -oo;
		if (L <= mid) res = max(res, query(L, R, x, rt << 1, l, mid));
		if (mid < R) res = max(res, query(L, R, x, rt << 1 | 1, mid + 1, r));
		return res;
	}
}
int n, Q, lstAns;
inline void de_read(int &x, const int &p) {
	Read(x); x = (x ^ lstAns) % p + 1;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(Q);
	int u, v, w;
	for (int i = 1; i < n; i++) {
		Read(u); Read(v); Read(w);
		Add(u, v, w); Add(v, u, w);
	}
	dfs(1, 0);
	rmq_init(n);
	Binary_Divide::init(Q);
	edge_clear(n);
	int op;
	while (Q--) {
		Read(op);
		switch (op) {
		case 2:
			Binary_Divide::remove(); --top; break;
		case 1:
			de_read(u, n); s[++top] = u; Binary_Divide::insert(); break;
		default:
			de_read(u, top); de_read(v, top); de_read(w, n); if (u > v) swap(u, v);
			lstAns = Binary_Divide::query(u, v, w);
			Wt(lstAns); lstAns = abs(lstAns);
		}
	}
	return 0;
}
