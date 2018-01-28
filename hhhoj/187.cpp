#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
typedef pair<int, int> PI;
typedef pair<PI, PI> PII;
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
	for (; !((c >= 'a' && c <= 'z') || c == '-'); c = get());
	for (; ((c >= 'a' && c <= 'z') || c == '-'); s[len++] = c, c = get());
}
int Ans = 0;
namespace SAM {
	int c[V][26], fa[V], len[V], pT, rt, lst;
	void Init() {
		for (int i = 0; i <= pT; i++) {
			memset(c[i], 0, sizeof c[i]);
			fa[i] = len[i] = 0;
		} pT = 0;
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
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) link(cur, rt);
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) link(cur, q);
			else {
				++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				 link(pT, fa[q]); cut(q);  link(q, pT); link(cur, pT);
			}
		}
		lst = cur;
	}
}
char s[V], f[V];
int L, pre[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, top = 0;
	Read(s + 1, L); 
	for (int i = 1; i <= L; i++) {
		if (s[i] != '-') f[++top] = s[i];
		else {
			f[top] = 0; top--;
		}
		SAM::Init(); Ans = 0;
		for (int j = 1; j <= top; j++) SAM::Extend(f[j] - 'a');
		printf("%d\n", Ans);
	}
	return 0;
}
