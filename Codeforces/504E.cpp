#include <bits/stdc++.h>
using namespace std;
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
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get());
}

char s[V];
int n, Q;

namespace SAM {
	int fa[V << 2], len[V << 2], c[V << 2][27], pT, lst, rt;
	void init() {
		lst = rt = ++pT;
	}
	void reset() {
		lst = rt;
	}
	int extend(int x) {
		int cur = ++pT; len[cur] = len[lst] + 1;
		int p = lst;
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) fa[cur] = rt;
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) fa[cur] = q;
			else {
				++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[cur] = fa[q] = pT;
			}
		}
		return lst = cur;
	}
	vector<int> G[V << 2];
	int top[V << 2], siz[V << 2], dep[V << 2];
	void dfs1(int u) {
		siz[u] = 1;
		for (auto v : G[u]) {
			dep[v] = dep[u] + 1; 
			dfs1(v); siz[u] += siz[v];
		}
	}
	void dfs2(int u, int path) {
		top[u] = path; int k = 0;
		for (auto v : G[u]) if (siz[v] > siz[k]) k = v;
		if (!k) return; dfs2(k, path);
		for (auto v : G[u]) if (v != k) dfs2(v, v);
	}
	int lcp(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] > dep[top[y]]) swap(x, y);
			y = fa[top[y]];
		}
		return len[dep[x] < dep[y] ? x : y];
	}
	void work() {
		for (int i = 2; i <= pT; i++) G[fa[i]].emplace_back(i);
		dfs1(rt); dfs2(rt, rt);
	}
}

vector<int> G[V];

int siz[V], fa[V], dep[V], top[V], pos[V], id[V], pT;
int P[V][2]; // 0 z 1 f
void dfs1(int u) {
	siz[u] = 1;
	for (auto v : G[u]) {
		if (v == fa[u]) continue;
		fa[v] = u; dep[v] = dep[u] + 1;
		dfs1(v); siz[u] += siz[v];
	}
}
void dfs2(int u, int path) {
	top[u] = path; id[pos[u] = ++pT] = u;
	int k = 0;
	for (auto v : G[u]) 
		if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	if (!k) {
		SAM::reset();
		for (int i = pos[u]; i >= pos[path]; i--)
			P[i][1] = SAM::extend(s[id[i]] - 'a');
		SAM::reset();
		for (int i = pos[path]; i <= pos[u]; i++)
			P[i][0] = SAM::extend(s[id[i]] - 'a');
		return;
	}
	dfs2(k, path);
	for (auto v : G[u]) 
		if (dep[v] > dep[u] && v != k) dfs2(v, v);
}

const int M = 200;
struct Ab {
	int d, x, len;
	Ab() {}
	Ab(int d, int x, int len) :
		d(d), x(pos[x]), len(len) {}
} s1[M], s2[M], tmp1[M], tmp2[M];
int t1, t2;

void Pre(int x, int y, int &t, Ab *s) {
	t = 0; int tt1 = 0, tt2 = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) {
			tmp1[++tt1] = Ab(0, x, dep[x] - dep[top[x]] + 1);
			x = fa[top[x]];
		} else {
			tmp2[++tt2] = Ab(1, top[y], dep[y] - dep[top[y]] + 1);
			y = fa[top[y]];
		}
	}
	if (dep[x] > dep[y]) tmp1[++tt1] = Ab(0, x, dep[x] - dep[y] + 1);
	else tmp2[++tt2] = Ab(1, x, dep[y] - dep[x] + 1);
	for (int i = 1; i <= tt1; i++) s[++t] = tmp1[i];
	for (int i = tt2; i; i--) s[++t] = tmp2[i];
}
const int f[2] = {-1, 1};
int Work() {
	int r = 0;
	int i = 1, j = 1, p = 0, q = 0;
	while (i <= t1 && j <= t2) {
		int l = min(s1[i].len - p, s2[j].len - q);
		int val = SAM::lcp(
		P[s1[i].x + f[s1[i].d] * p][s1[i].d],
		P[s2[j].x + f[s2[j].d] * q][s2[j].d]
		);
		val = min(l, val);
		r += val; p += val; q += val;
		if (val != l) break;
		if (p == s1[i].len) p = 0, i++;
		if (q == s2[j].len) q = 0, j++;
	}
	return r;
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(s + 1, n);
	SAM::init();
	int x, y, a, b;
	for (int i = 1; i < n; i++) {
		Read(x); Read(y);
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	dfs1(1); dfs2(1, 1);
	SAM::work();
	Read(Q);
	while (Q--) {
		Read(x); Read(y); Read(a); Read(b);
		Pre(x, y, t1, s1); Pre(a, b, t2, s2);
		printf("%d\n", Work());
	}
	return 0;
}
