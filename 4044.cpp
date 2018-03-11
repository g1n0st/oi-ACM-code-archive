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
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !isupper(c); c = get());
	for (; isupper(c); s[len++] = c, c = get());
}
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
int Trans(char c) {
	switch (c) {
		case 'A': return 0; case 'T': return 1; case 'G': return 2; case 'C': return 3;
	}
}
char s[V];
int T, n, f[V];
namespace PAM {
	int c[V][4], fa[V], len[V], half[V], pT, lst;
	void ini() {
		fa[0] = fa[1] = half[0] = half[1] = 1;
		f[0] = 1; f[1] = -1; len[1] = -1;
	}
	void init() {
		for (int i = 0; i <= pT; i++)
			half[i] = c[i][0] = c[i][1] = c[i][2] = c[i][3] = 0;
		lst = 0; pT = 1;
	}
	int extend(int x, int v) {
		int p = lst;
		while (s[x - len[p] - 1] ^ v) p = fa[p];
		if (!c[p][v]) {
			++pT; int q = fa[p]; len[pT] = len[p] + 2;
			while (s[x - len[q] - 1] ^ v) q = fa[q];
			fa[pT] = c[q][v]; q = half[p];
			while (len[c[q][v]] > (len[pT] >> 1) || s[x - len[q] - 1] ^ v) q = fa[q];
			half[pT] = c[q][v]; c[p][v] = pT;
			f[pT] = len[pT] & 1 ? len[pT] : min(f[p] + 1, f[half[pT]] + (len[pT] >> 1) - len[half[pT]] + 1);
		}
		return lst = c[p][v];
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T); PAM::ini();
	while (T--) {
		Read(s + 1, n);
		int ans = 0x3f3f3f3f;
		s[0] = -1; for (int i = 1; i <= n; i++) s[i] = Trans(s[i]);
		for (int i = 1; i <= n; i++) {
			int p = PAM::extend(i, s[i]);
			ans = min(ans, n - PAM::len[p] + f[p]);
		}
		printf("%d\n", ans);
		if (T) PAM::init();
	}
	return 0;
}
