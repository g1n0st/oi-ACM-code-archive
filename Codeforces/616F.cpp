#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000010;
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
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get()); s[len] = 0;
}
LL Ans;
int M, n, a[V], len[V];
char s[V];

int head[V], sub, son[V];
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
namespace SAM {
	LL val[V];
	int c[V][26], fa[V], len[V], pT, rt, lst;
	void init() {
		rt = lst = ++pT;
	}
	void reset() {
		lst = rt;
	}
	void extend(int x, int y) {
		int p = lst, q = c[p][x];
		if (q) {
			if (len[q] == len[p] + 1) {
				lst = q; val[q] += y;
			}
			else {
				++pT; len[pT] = len[p] + 1; 
				fa[pT] = fa[q]; val[pT] += y;
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[q] = pT;
				lst = pT;
			}
		}
		else {
			int cur = ++pT; len[cur] = len[lst] + 1; val[cur] = y;
			while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
			if (!p) fa[cur] = rt;
			else {
				q = c[p][x];
				if (len[q] == len[p] + 1) fa[cur] = q;
				else {
					++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
					memcpy(c[pT], c[q], sizeof c[q]);
					while (c[p][x] == q) c[p][x] = pT, p = fa[p];
					fa[q] = fa[cur] = pT;
				}
			}
			lst = cur;
		}
	}
	void dfs(int u) {
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; dfs(v); val[u] += val[v];
		}
		Ans = max(Ans, len[u] * val[u]);
	}
	void work() {
		for (int i = 2; i <= pT; i++) Add(fa[i], i);
		dfs(rt);
	}
}
string S;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(M); SAM::init();
	for (int i = 1; i <= M; i++) {
		Read(s, n); S += s; len[i] = n;
	}
	for (int i = 1; i <= M; i++) Read(a[i]);
	int cur = 0;
	for (int i = 1; i <= M; i++) {
		SAM::reset();
		for (int j = cur; j < cur + len[i]; j++) SAM::extend(S[j] - 'a', a[i]);
		cur += len[i];
	}
	SAM::work();
	cout << Ans << endl;
	return 0;
}
