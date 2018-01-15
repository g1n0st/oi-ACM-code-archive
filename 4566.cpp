#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 400010;
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
	for (; !(c >= 'a' && c <= 'z'); c = get());
	for (; c >= 'a' && c <= 'z'; s[len++] = c, c = get());
}
namespace SAM {
	int c[V][26], fa[V], len[V], val[V], pT, rt, lst;
	void Init() {
		lst = rt = ++pT;
	}
	void Extend(int x) {
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
	int v[V], q[V]; LL sum[V];
	void Pre(int n) {
		int i, j;
		for (i = 1; i <= pT; i++) v[len[i]]++;
		for (i = 1; i <= n; i++) v[i] += v[i - 1];
		for (i = pT; i; i--) q[v[len[i]]--] = i;
		for (i = pT; i; i--) {
			int t = q[i];
			val[fa[t]] += val[t];
		}
		for (i = 1; i <= pT; i++) {
			int t = q[i];
			sum[t] = sum[fa[t]] + 1LL * (len[t] - len[fa[t]]) * val[t];
		}
	}
	void Work(char *s, int n) {
		LL Ans = 0; int l = 0, p = rt;
		for (int i = 0; i < n; i++) {
			int x = s[i] - 'a';
			if (c[p][x]) p = c[p][x], l++;
			else {
				while (p && !c[p][x]) p = fa[p];
				if (!p) p = rt, l = 0;
				else l = len[p] + 1, p = c[p][x];
			}
			if (p ^ rt) {
				Ans += sum[fa[p]] + 1LL * (l - len[fa[p]]) * val[p];
			}
		}
		printf("%lld\n", Ans);
	}
};
char a[V], b[V];
int la, lb;
int main() {
	int i, j;
	Read(a, la); Read(b, lb); SAM::Init();
	for (i = 0; i < la; i++) SAM::Extend(a[i] - 'a');
	SAM::Pre(la); SAM::Work(b, lb);
	return 0;
}
