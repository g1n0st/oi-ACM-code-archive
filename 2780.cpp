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
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get()); s[len] = 0;
}
namespace SAM {
	int vis[V], si[V];
	int len[V], fa[V], c[V][26], pT, lst, rt;
	void Init() {
		rt = lst = ++pT;
	}
	void reset() {
		lst = rt;
	}
	void Extend(int x, int id) {
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
				vis[pT] = vis[q]; si[pT] = si[q];
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[q] = fa[cur] = pT;
			}
		}
		lst = cur;
		while (cur && vis[cur] ^ id) {
			vis[cur] = id; si[cur]++; cur = fa[cur];
		}
	}
	void Work(char *s, int l) {
		int p = rt;
		for (int i = 1; i <= l; i++) p = c[p][s[i] - 'a'];
		printf("%d\n", si[p]);
	}
}
int n, m, L;
char s[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); SAM::Init();
	for (int i = 1; i <= n; i++) {
		SAM::reset(); Read(s + 1, L);
		for (int j = 1; j <= L; j++) SAM::Extend(s[j] - 'a', i);
	}
	for (int i = 1; i <= m; i++) {
		Read(s + 1, L); SAM::Work(s, L);
	}
	return 0;
}
