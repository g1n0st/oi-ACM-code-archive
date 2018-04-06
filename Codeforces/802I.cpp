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
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get());
}
LL Ans;
namespace SAM {
	int fa[V << 1], len[V << 1], val[V << 1], c[V << 1][26];
	int rt, lst, pT;
	void init() {
		for (int i = 1; i <= pT; i++) {
			fa[i] = len[i] = val[i] = 0;
			for (int j = 0; j < 26; j++) c[i][j] = 0;
		}
		rt = lst = pT = 1;
	}
	void extend(int x) {
		int cur = ++pT; 
		len[cur] = len[lst] + 1; val[cur] = 1;
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
		lst = cur;
	}
	int q[V << 1], id[V << 1];
	void work(int n) {
		for (int i = 1; i <= n; i++) q[i] = 0;
		for (int i = 1; i <= pT; i++) q[len[i]]++;
		for (int i = 1; i <= pT; i++) q[i] += q[i - 1];
		for (int i = pT; i; i--) id[q[len[i]]--] = i;
		for (int i = pT; i; i--) {
			int t = id[i];
			Ans += (LL)val[t] * val[t] * (len[t] - len[fa[t]]);
			val[fa[t]] += val[t];
		}
	}
}
int T, n;
char s[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T);
	while (T--) {
		Ans = 0;
		Read(s + 1, n); SAM::init();
		for (int i = 1; i <= n; i++) SAM::extend(s[i] - 'a');
		SAM::work(n);
		cout << Ans << endl;
	}
	return 0;
}
