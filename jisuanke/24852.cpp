#include <bits/stdc++.h>
using namespace std;
const int V = 200010;
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
int Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get()) if (c == EOF) return 0;
	for (; islower(c); s[len++] = c, c = get());
	return 1;
}
char s[V];
int n, Q;
namespace Trie {
	int s[V << 6][2], rt[V << 6], siz[V << 6], pT;
	void init() {
		pT = 0;
	}
	int NewNode() {
		++pT;
		s[pT][0] = s[pT][1] = 0;
		siz[pT] = 1;
		return pT;
	}
	void Insert(int &u, int val, int d) {
		if (!u) u = NewNode();
		if (~d) {
			Insert(s[u][(val >> d) & 1], val, d - 1);
			siz[u] = siz[s[u][0]] + siz[s[u][1]];
		}
	}
	int GetAns(int u) {
		int Ret = 0;
		for (int i = 20; ~i; i--) {
			Ret <<= 1;
			if (siz[s[u][0]] < (1 << i)) u = s[u][0];
			else Ret |= 1, u = s[u][1];
		}
		return Ret;
	}
}
namespace SAM {
	int len[V], c[V][26], fa[V], rt, lst, pT;
	int New(int x) {
		for (int i = 0; i < 26; i++) c[x][i] = 0;
		len[x] = fa[x] = 0; return x;
	}
	void init() {
		rt = lst = pT = New(1);
	}
	void extend(int x) {
		int cur = New(++pT); len[cur] = len[lst] + 1;
		int p = lst;
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) fa[cur] = rt;
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) fa[cur] = q;
			else {
				New(++pT); len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[cur] = fa[q] = pT;
			}
		}
		lst = cur;
	}
	int sg[V];
	int dfs(int u) {
		if (~sg[u]) return sg[u];
		int tsg = 0;
		for (int i = 0, v; i < 26; i++) {
			v = c[u][i]; if (!v) continue;
			dfs(v); Trie::Insert(Trie::rt[u], sg[v], 20);
		}
		return sg[u] = Trie::GetAns(Trie::rt[u]);
	}
	void Work() {
		Trie::init();
		for (int i = 1; i <= pT; i++) sg[i] = -1, Trie::rt[i] = 0;
		dfs(rt);
	}
	int Calc(char *s, int len) {
		int p = rt;
		for (int i = 1; i <= len; i++) p = c[p][s[i] - 'a'];
		return sg[p];
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	while (Read(s + 1, n)) {
		SAM::init();
		for (int i = 1; i <= n; i++) SAM::extend(s[i] - 'a');
		SAM::Work();
		Read(Q); int SG = 0;
		while (Q--) {
			Read(s + 1, n); SG ^= SAM::Calc(s, n);
		}
		puts(SG ? "Alice" : "Bob");
	}
	return 0;
}
