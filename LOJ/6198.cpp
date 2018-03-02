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
void Read(char *s, int len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get()); s[len] = 0;
}
namespace Trie {
	const int N = V * 100;
	int rt[N], c[N][2], pT;
	void ins(int x, int v) {
		if (!rt[x]) rt[x] = ++pT; int p = rt[x];
		for (int i = 20; ~i; i--) {
			int q = (v >> i) & 1; if (!c[p][q]) c[p][q] = ++pT;
			p = c[p][q];
		}
	}
	int find(int x, int v) {
		int r = 0, p = rt[x];
		for (int i = 20; ~i; i--) {
			int q = !((v >> i) & 1); 
			if (c[p][q]) r += (1 << i); else q ^= 1;
			p = c[p][q];
		}
		return r;
	}
}
char s[V];
int n, a[V], p[V], ans;
vector<int> S[V << 1];
namespace SAM {
	const int N = V * 2;
	int c[N][26], fa[N], len[N], rt, pT, lst;
	void init() {
		rt = lst = ++pT;
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
				fa[q] = fa[cur] = pT;
			}
		}
		return lst = cur;
	}
	int q[N], id[N];
	void Work(int n) {
		for (int i = 1; i <= pT; i++) q[len[i]]++;
		for (int i = 1; i <= n; i++) q[i] += q[i - 1];
		for (int i = pT; i; i--) id[q[len[i]]--] = i;
		for (int i = pT; i > 1; i--) {
			int t = id[i], f = fa[t];
			if (S[t].size() > S[f].size()) {
				swap(S[t], S[f]); swap(Trie::rt[t], Trie::rt[f]);
			}
			for (auto e : S[t]) {
				S[f].emplace_back(e); Trie::ins(f, e); ans = max(ans, len[f] + Trie::find(f, e));
			}
		}
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(s + 1, n); SAM::init();
	for (int i = n; i; i--) p[i] = SAM::extend(s[i] - 'a');
	for (int i = 1; i <= n; i++) {
		Read(a[i]); S[p[i]].emplace_back(a[i]); Trie::ins(p[i], a[i]);
	}
	SAM::Work(n);
	cout << ans << endl;
	return 0;
}
