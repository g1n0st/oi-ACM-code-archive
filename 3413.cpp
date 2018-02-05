#include <bits/stdc++.h>
using namespace std;
const int V = 200010;
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
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); s[len++] = c, c = get());
}
namespace SGT {
	const int N = V * 30;
	int rt[V], ls[N], rs[N], sum[N], pT;
	void Add(int &x, int y, int l, int r, int p) {
		x = ++pT; ls[x] = ls[y]; rs[x] = rs[y]; sum[x] = sum[y] + 1;
		if (l == r) return;
		int Mid = (l + r) >> 1;
		if (p <= Mid) Add(ls[x], ls[y], l, Mid, p); else Add(rs[x], rs[y], Mid + 1, r, p);
	}
	int Qur(int x, int l, int r, int L, int R) {
		if (!x) return 0;
		if (l == L && r == R) return sum[x];
		int Mid = (l + r) >> 1;
		if (R <= Mid) return Qur(ls[x], l, Mid, L, R);
		if (Mid < L) return Qur(rs[x], Mid + 1, r, L, R);
		return Qur(ls[x], l, Mid, L, Mid) + Qur(rs[x], Mid + 1, r, Mid + 1, R);
	}
} using SGT::rt;
int N, M, L, pos[V], st[V], ed[V], pT, mn[V], id[V];
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
void Cha(int x, int p) {
	SGT::Add(rt[x], rt[x - 1], 1, N + 100, p);
}
int Qur(int x, int y, int r) {
	return SGT::Qur(rt[y], 1, N + 100, 1, r) - SGT::Qur(rt[x - 1], 1, N + 100, 1, r);
}
namespace SAM {
	int fa[V], len[V], c[V][12], pT, lst, rt;
	void Init() {
		lst = rt = ++pT;
	}
	int Extend(int x) {
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
				fa[q] = fa[cur] = pT;
			}
		}
		return lst = cur;
	}
	void Work() {
		for (int i = 1; i <= pT; i++) Add(fa[i], i);
	}
	int cmp(char *s, int l, int &cl, int &p) {
		p = rt; cl = 0; int flg = 1;
		for (int i = l; i; i--) {
			int x = s[i] - '0';
			if (!c[p][x]) {
				while (p && !c[p][x]) p = fa[p], cl = len[p];
				if (!p) p = rt;
				else {
					++cl; p = c[p][x];
				}
				flg = 0;
			}
			else {
				++cl; p = c[p][x];
			}
		}
		return flg;
	}
}
void Dfs(int u) {
	st[u] = ++pT; id[u] = u;
	if (mn[u] < INF) Cha(st[u], mn[u]);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; Dfs(v);
		if (mn[v] < mn[u]) {
			id[u] = id[v]; mn[u] = mn[v];
		}
	}
	ed[u] = pT;
}
char s[V];
using SAM::fa; using SAM::len;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(s + 1, N); SAM::Init();
	for (int i = N; i; i--) pos[i] = SAM::Extend(s[i] - '0');
	SAM::Work(); memset(mn, 0x3f, sizeof mn);
	for (int i = 1; i <= N; i++) mn[pos[i]] = i;
	Dfs(SAM::rt);
	Read(M);
	while (M--) {
		Read(s + 1, L); int cl, Mn, p, ans = 0; 
		Mn = SAM::cmp(s, L, cl, p) ? mn[p] : (N + 1);
		if (p ^ SAM::rt) {
			ans += (cl - len[fa[p]]) * Qur(st[p], ed[p], Mn);
			p = fa[p];
		}
		while (p ^ SAM::rt) {
			ans += (len[p] - len[fa[p]]) * Qur(st[p], ed[p], Mn);
			p = fa[p];
		}
		ans += Mn - 1;
		printf("%d\n", ans);
	}
	return 0;
}
