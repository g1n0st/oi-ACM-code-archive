#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T>
void Read(T &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
namespace GE {
	const LL oo = 1 << 30;
	struct Node {
		LL s, a; int id;
		friend bool operator < (const Node &a, const Node &b) {
			return a.a < b.a;
		}
	} v[V], qu[V];
	LL meeting(Node &a, Node &b) {
		if (a.a == b.a) return (b.s > a.s || (b.s == a.s && b.id > a.id)) ? -1 : oo;
		LL ans = (a.s - b.s) / (b.a - a.a) + (!((a.s - b.s) % (b.a - a.a) == 0 && b.id > a.id));
		if (ans < 0) return -1; if (ans > oo) return oo;
		return ans;
	}
	LL t[V], tot;
	void Work(int n) {
		sort(v + 1, v + 1 + n);
		int tail = 0; LL c1, c2;
		for (int i = 1; i <= n; i++) {
			while (tail > 0) {
				c1 = meeting(qu[tail], v[i]);
				if (c1 <= 0) { tail--; continue; }
				if (tail > 1) {
					c2 = t[tail - 2];
					if (c2 >= c1) {
						tail--; continue;
					}
				}
				break;
			}
			qu[++tail] = v[i];
			if (tail > 1) t[tail - 2] = c1;
		}
		tot = tail - 1;
	}
}
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V * 2];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int fa[V], siz[V], dep[V], pos[V], top[V], id[V], pT;
void Dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; dep[v] = dep[u] + 1; Dfs1(v); siz[u] += siz[v];
	}
}
void Dfs2(int u, int path) {
	id[pos[u] = ++pT] = u; top[u] = path; int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return; Dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (dep[v] > dep[u] && v != k) Dfs2(v, v);
	}
}
int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}
int dist(int x, int y) {
	int dis = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) swap(x, y);
		dis += pos[y] - pos[top[y]] + 1; y = fa[top[y]];
	}
	if (dep[x] > dep[y]) swap(x, y); dis += dep[y] - dep[x];
	return dis;
}
int Move(int x, int m) {
	while (m) {
		if (dep[x] - dep[top[x]] + 1 <= m) m -= dep[x] - dep[top[x]] + 1, x = fa[top[x]];
		else return id[pos[x] - m];
	}
	return x;
}
int Move(int x, int y, int m) {
	int dis = dist(x, y);
	m = min(m, dis);
	if (!m) return x; if (m == dis) return y;
	int l = lca(x, y), dis1 = dist(l, x);
	if (m <= dis1) return Move(x, m);
	else return Move(y, dis - m);
}
struct Node {
	int id, t;
	friend bool operator < (const Node &a, const Node &b) {
		return a.t < b.t;
	}
} q[V];
int N, M, Ans[V];
void Solve() {
	int p = 1, Now = 0, qi = 1, vi = 0;
	while (qi <= M) {
		if (GE::t[vi] < q[qi].t && vi < GE::tot) {
			p = Move(p, GE::qu[vi + 1].id, GE::t[vi] - Now); Now = GE::t[vi++];
		} else {
			p = Move(p, GE::qu[vi + 1].id, q[qi].t - Now);
			Ans[q[qi].id] = p; Now = q[qi++].t;
		}
	}
}
int main() {
	int i, j, x, y;
	Read(N); Read(M);
	for (i = 1; i <= N; i++) {
		Read(GE::v[i].s); GE::v[i].id = i;
	}
	for (i = 1; i <= N; i++) {
		Read(GE::v[i].a);
	}
	for (i = 1; i < N; i++) {
		Read(x); Read(y); ++x; ++y;
		Add(x, y); Add(y, x);
	}
	for (i = 1; i <= M; i++) {
		Read(q[i].t); q[i].id = i;
	}
	sort(q + 1, q + 1 + M);
	GE::Work(N); Dfs1(1); Dfs2(1, 1); 
	Solve();
	for (i = 1; i <= M; i++) printf("%d\n", Ans[i] - 1);
	return 0;
}
