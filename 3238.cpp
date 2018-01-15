#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 500010 * 2;
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
	int v[V], q[V], sum[V];
	int val[V], len[V], fa[V], c[V][26], pT, lst, rt;
	void Init() {
		lst = rt = ++pT;
	}
	void Extend(int x) {
		int cur = ++pT;
		len[cur] = len[lst] + 1; val[cur] = sum[cur] = 1;
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
	LL Work(int n) {
		int i, j, t; LL r = 0;
		for (i = 1; i <= pT; i++) v[len[i]]++;
		for (i = 1; i <= n; i++) v[i] += v[i - 1];
		for (i = pT; i; i--) q[v[len[i]]--] = i;
		for (i = pT; i; i--) {
			t = q[i];
			val[fa[t]] += val[t];
		}
		for (i = pT; i; i--) {
			t = q[i];
			r += 1LL * len[fa[t]] * sum[fa[t]] * val[t];
			sum[fa[t]] += val[t];
		}
		return r;
	}
}
char s[V]; int n;
int main() {
	int i, j;
	Read(s, n); SAM::Init();
	for (i = n - 1; ~i; i--) SAM::Extend(s[i] - 'a');
	LL t = 1LL * (n + 1) * n * (n - 1) / 2 - SAM::Work(n) * 2;
	printf("%lld\n", t);
	return 0;
}
