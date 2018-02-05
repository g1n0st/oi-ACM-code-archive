#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 800010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get());
}
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
LL ans[V];
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
namespace SAM {
	int c[V][26], len[V], fa[V], bel[V], rt, lst, pT;
	void Init() {
		rt = lst = ++pT;
	}
	void reset() {
		lst = 1;
	}
	void Extend(int x, int id) {
		int cur = ++pT;
		len[cur] = len[lst] + 1; bel[cur] = id;
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
		lst = cur;
	}
	int id[V], q[V], B[V];
	void Dfs(int u) {
		B[u] = bel[u];
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; Dfs(v);
		}
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (B[v] == -1) {
				B[u] = -1; break;
			}
			if (!B[v]) continue;
			if (!B[u]) B[u] = B[v];
			else if (B[u] ^ B[v]) {
				B[u] = -1; break;
			}
		}
	}
	void Work() {
		for (int i = 2; i <= pT; i++) Add(fa[i], i);
		Dfs(rt);
		for (int i = 1; i <= pT; i++)
			if (B[i] >= 1) ans[B[i]] += len[i] - len[fa[i]];
	}
}
int N, L;
char s[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	Read(N); SAM::Init();
	for (int i = 1; i <= N; i++) {
		Read(s + 1, L); SAM::reset();
		for (int j = 1; j <= L; j++) SAM::Extend(s[j] - 'a', i);
	}
	SAM::Work();
	for (int i = 1; i <= N; i++) printf("%lld\n", ans[i]);
	return 0;
}
