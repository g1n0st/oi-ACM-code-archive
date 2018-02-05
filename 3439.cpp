#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
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
	for (; islower(c); s[len++] = c, c = get()); s[len] = 0;
}
char s[V];
int N, M, tot, st[V], ed[V];
int head[V], sub, nxt[V];
namespace SGT {
	const int L = V * 50;
	int sum[L], ls[L], rs[L], rt[L], pT, lst;
	void Upd(int &x, int y, int l, int r, int p) {
		x = ++pT; ls[x] = ls[y]; rs[x] = rs[y]; sum[x] = sum[y] + 1;
		if (l == r) return; int Mid = (l + r) >> 1;
		if (p <= Mid) Upd(ls[x], ls[y], l, Mid, p);
		else Upd(rs[x], rs[y], Mid + 1, r, p);
	}
	int Query(int x, int y, int l, int r, int k) {
		if (sum[y] - sum[x] < k) return -1;
		if (l == r) return l;
		int Mid = (l + r) >> 1, lsum = sum[ls[y]] - sum[ls[x]];
		if (k <= lsum) return Query(ls[x], ls[y], l, Mid, k);
		else Query(rs[x], rs[y], Mid + 1, r, k - lsum);
	}
	void Upd(int x) {
		++lst; Upd(rt[lst], rt[lst - 1], 1, N, x);
	}
}
namespace Trie {
	int pT, c[V][26], rt;
	void Init() {
		rt = ++pT;
	}
	void Insert(char *s, int l) {
		int p = rt;
		for (int i = 1; i <= l; i++) {
			int x = s[i] - 'a';
			if (!c[p][x]) c[p][x] = ++pT;
			p = c[p][x];
		}
		nxt[++sub] = head[p]; head[p] = sub;
	}
	void Dfs(int u) {
		for (int i = head[u]; i; i = nxt[i]) st[i] = SGT::lst;
		for (int i = head[u]; i; i = nxt[i]) SGT::Upd(i);
		for (int i = 0; i < 26; i++) if (c[u][i]) Dfs(c[u][i]);
		for (int i = head[u]; i; i = nxt[i]) ed[i] = SGT::lst;
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Trie::Init();
	for (int i = 1, L; i <= N; i++) {
		Read(s + 1, L); reverse(s + 1, s + 1 + L); Trie::Insert(s, L);
	}
	Trie::Dfs(Trie::rt); using SGT::rt;
	for (int i = 1, k; i <= N; i++) {
		Read(k); printf("%d\n", SGT::Query(rt[st[i]], rt[ed[i]], 1, N, k));
	}
	return 0;
}
