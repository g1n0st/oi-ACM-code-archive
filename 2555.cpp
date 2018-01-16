#include <bits/stdc++.h>
using namespace std;
const int V = 1200010;
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
	for (; !(c >= 'A' && c <= 'Z'); c = get());
	for (; c >= 'A' && c < 'Z'; s[len++] = c, c = get());
}
void Read(int &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}

namespace LCT {
#define ls ch[x][0]
#define rs ch[x][1]
	int val[V], ch[V][2], fa[V], add[V];
	int which(int x) { return ch[fa[x]][1] == x; }
	int isRt(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
	void Add(int x, int v) { add[x] += v, val[x] += v; }
	void pushDown(int x) {
		if (add[x]) {
			if (ls) Add(ls, add[x]);
			if (rs) Add(rs, add[x]);
			add[x] = 0;
		}
	}
	void relax(int x) { if (!isRt(x)) relax(fa[x]); pushDown(x); }
	void rotate(int x) {
		int y = fa[x], z = fa[y], nx = which(x), ny = which(y), isrt = isRt(y);
		fa[ch[x][!nx]] = y, ch[y][nx] = ch[x][!nx];
		fa[x] = z; if (!isrt) ch[z][ny] = x;
		fa[y] = x, ch[x][!nx] = y;
	}
	void splay(int x) {
		relax(x);
		while (!isRt(x)) {
			int y = fa[x];
			if (isRt(y)) rotate(x);
			else if (which(x) == which(y)) rotate(y), rotate(x);
			else rotate(x), rotate(x);
		}
	}
	void access(int x) {
		for (int p = 0; x; x = fa[x])
			splay(x), rs = p, p = x;
	}
	void link(int x, int f) {
		fa[x] = f, access(f), splay(f), Add(f, val[x]);
	}
	void cut(int x) {
		access(x), splay(x), Add(ls, -val[x]);
		fa[ls] = 0, ls = 0;
	}
#undef ls  
#undef rs  
}

namespace SAM {
	int len[V], fa[V], c[V][26], rt, lst, pT;
	void Init() {
		rt = lst = ++pT;
	}
	void link(int p, int f) {
		fa[p] = f, LCT::link(p, f);
	}
	void Extend(int x) {
		int cur = ++pT; len[cur] = len[lst] + 1; LCT::val[cur] = 1;
		int p = lst;
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) link(cur, rt);
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) link(cur, q);
			else {
				++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				link(pT, fa[q]); LCT::cut(q);
				link(q, pT); link(cur, pT);
			}
		}
		lst = cur;
	}
	int Work(char *s, int len) {
		int p = rt;
		for (int i = 0; i < len; i++) {
			if (!c[p][s[i] - 'A']) return 0;
			p = c[p][s[i] - 'A'];
		}
		LCT::splay(p); return LCT::val[p];
	}
}
void DecodeWithMask(int mask, char *s, int length) {
	for (int i = 0; i < length; ++i) {
		mask = (mask * 131 + i) % length;
		swap(s[i], s[mask]);
	}
}
char s[V], op[10];
int M, N, L;
int main() {
	int i, j;
	Read(M); Read(s + 1, N); SAM::Init();
	for (i = 1; i <= N; i++) SAM::Extend(s[i] - 'A');
	int mask = 0, lstAns;
	while (M--) {
		Read(op, L); Read(s, N);
		DecodeWithMask(mask, s, N);
		if (op[0] == 'Q') {
			lstAns = SAM::Work(s, N);
			mask ^= lstAns;
			printf("%d\n", lstAns);
		}
		else {
			for (i = 0; i < N; i++) SAM::Extend(s[i] - 'A');
		}
	}
	return 0;
}
