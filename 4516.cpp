#include <bits/stdc++.h>
using namespace std;
const int V = 200010;
typedef long long LL;
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
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
LL Ans = 0;
namespace SAM {
	map<int, int> c[V];
	int fa[V], len[V], pT, rt, lst;
	void Init() {
		lst = rt = ++pT;
	}
	void cut(int x) {
		Ans -= len[x] - len[fa[x]];
		fa[x] = 0;
	}
	void link(int x, int y) {
		Ans += len[x] - len[y];
		fa[x] = y;
	}
	void Extend(int x) {
		int cur = ++pT;
		len[cur] = len[lst] + 1;
		int p = lst;
		while (p && !c[p].count(x)) c[p][x] = cur, p = fa[p];
		if (!p) link(cur, rt);
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) link(cur, q);
			else {
				++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
				c[pT] = c[q];
				while (c[p].count(x) && c[p][x] == q) c[p][x] = pT, p = fa[p];
				link(pT, fa[q]); cut(q);  link(q, pT); link(cur, pT);
			}
		}
		lst = cur;
	}
}
int N;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); SAM::Init();
	for (int i = 1, x; i <= N; i++) {
		Read(x); SAM::Extend(x); printf("%lld\n", Ans);
	}
	return 0;
}
