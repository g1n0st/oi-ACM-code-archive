#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PI;

const int V = 500010;
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
int n, K, w[V];

int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}

int dep[V], siz[V], fa[V], pos[V], top[V], id[V], pT;
void dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		dep[v] = dep[u] + 1; fa[v] = u; 
		dfs1(v); siz[u] += siz[v];
	}
}
void dfs2(int u, int path) {
	id[pos[u] = ++pT] = u; 
	top[u] = path;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; 
		if (siz[v] > siz[k]) k = v;
	}
	if (!k) return; dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; 
		if (v ^ k) dfs2(v, v);
	}
}
int lca(int x, int y) {
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}
int lstt(int x, int t) {
	while (top[x] ^ top[t]) {
		if (fa[top[x]] == t) return top[x];
		x = fa[top[x]];
	}
	return id[pos[t] + 1];
}

int val[V << 2];
int cmp(int x, int y) {
	return w[x] < w[y] ? x : y;
}
void build(int o, int l, int r) {
	if (l == r) {
		val[o] = id[l]; return ;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	val[o] = cmp(val[o << 1], val[o << 1 | 1]);
}
int query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return val[o];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(o << 1, l, mid, L, R);
	if (mid < L) return query(o << 1 | 1, mid + 1, r, L, R);
	return cmp(
		query(o << 1, l, mid, L, mid),
		query(o << 1 | 1, mid + 1, r, mid + 1, R)
	);
}

int query(int x, int y) {
	int r = 0;
	while (top[x] ^ top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		r = cmp(r, query(1, 1, n, pos[top[y]], pos[y]));
		y = fa[top[y]];
	}
	if (pos[x] > pos[y]) swap(x, y);
	r = cmp(r, query(1, 1, n, pos[x], pos[y]));
	return r;
}

struct Abcd{
	int l_t, l_e, p, w;
	Abcd() {}
	Abcd(int l_t, int l_e, int p, int w) :
		l_t(l_t), l_e(l_e), p(p), w(w) {}
	friend bool operator < (const Abcd &x, const Abcd &y) {
		return x.w > y.w;
	}
};
priority_queue<Abcd> q;

vector<PI> G[V];
void join(int x, int l_t, int l_e) {
	G[x].emplace_back(PI(l_t, l_e));
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K);
	int x, y, z;
	w[0] = 1 << 30;
	for (int i = 1; i <= n; i++) Read(w[i]);
	for (int i = 2; i <= n; i++) {
		Read(x); Add(x, i);
	}
	dfs1(1); dfs2(1, 1); build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		Read(x); Read(y); Read(z);
		if (dep[x] > dep[y]) swap(x, y);
		if (dep[x] > dep[z]) swap(x, z);
		if (dep[y] > dep[z]) swap(y, z);

		int xy = lca(x, y), xz = lca(x, z), yz = lca(y, z);

		if (xy == xz && yz == xz) {
			if (xy == x) {
				join(i, x, y); join(i, lstt(z, x), z);
			} else {
				join(i, xy, x); join(i, lstt(y, xy), y); join(i, lstt(z, xy), z);
			}
		}
		else if (xy == x && xz == x) {
			if (yz == y) join(i, x, z);
			else {
				join(i, x, y); join(i, lstt(z, yz), z);
			}
		}
		else {
			if (xy == yz) {
				swap(x, y); swap(xz, yz);
			}
			if (yz == xz) {
				swap(x, z); swap(xy, yz);
			}
			join(i, xy, x);
			if (dep[y] > dep[z]) swap(y, z);
			join(i, lstt(z, xz), z);
			if (yz != y) join(i, lstt(y, yz), y);
		}
		q.push(Abcd(i, i, i, w[i]));
	}
	while (K--) {
		printf("%d\n", q.top().w);
		
		Abcd t = q.top(); q.pop();

		if (t.l_t != t.p) {
			int tmp = fa[t.p];
			int pp = query(tmp, t.l_t);
			q.push(Abcd(t.l_t, tmp, pp, t.w - w[t.p] + w[pp]));
		}

		if (t.l_e != t.p) {
			int tmp = lstt(t.l_e, t.p);
			int pp = query(tmp, t.l_e);
			q.push(Abcd(tmp, t.l_e, pp, t.w - w[t.p] + w[pp]));
		}

		for (auto v : G[t.p]) {
			int pp = query(v.first, v.second);
			q.push(Abcd(v.first, v.second, pp, t.w + w[pp]));
		}
	}
	return 0;
}
