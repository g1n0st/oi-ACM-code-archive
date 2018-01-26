#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 300010;
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
int pos[V];
namespace SAM {
	int len[V << 1], fa[V << 1], c[V << 1][26], val[V << 1], lst, rt, pT;
	void Init() {
		lst = rt = ++pT;
	}
	int Extend(int x) {
		int cur = ++pT; len[cur] = len[lst] + 1; val[cur] = 1;
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
	int q[V << 1], id[V << 1], f[V << 1][21];
	void Work(int n) {
		int i, j, t;
		for (i = 1; i <= pT; i++) q[len[i]]++;
		for (i = 1; i <= n; i++) q[i] += q[i - 1];
		for (i = pT; i; i--) id[q[len[i]]--] = i;
		for (i = pT; i; i--) {
			t = id[i]; val[fa[t]] += val[t];
		}
		for (i = 1; i <= pT; i++) f[i][0] = fa[i];
		for (j = 1; j <= 20; j++)
			for (i = 1; i <= pT; i++)
				f[i][j] = f[f[i][j - 1]][j - 1];
	}
	LL Match(int x, int y) {
		int p = pos[y], l = y - x + 1;
		for (int i = 20; ~i; i--)
			if (len[f[p][i]] >= l) p = f[p][i];
		return (LL)l * val[p];
	}
}
void Manacher(char *str, int len) {
	static char s[V]; static int p[V << 1], id[V << 1];
	int i, j;
	for (s[0] = '$', s[1] = '#', i = 1; i <= len; i++) {
		s[i << 1] = str[i]; s[i << 1 | 1] = '#'; id[i << 1] = i;
	}
	len = len << 1 | 1;
	int mx = 1, pos = 1;
	LL Ans = 0;
	for (int i = 1; i <= len; i++) {
		p[i] = min(p[2 * pos - i], mx - i);
		while (s[i + p[i]] == s[i - p[i]]) {
			if (i + p[i] >= mx && s[i + p[i]] != '#')
				Ans = max(Ans, SAM::Match(id[i - p[i]], id[i + p[i]]));
			p[i]++;
		}
		if (i + p[i] > mx) {
			mx = i + p[i]; pos = i;
		}
	}
	cout << Ans << endl;
}
char s[V]; int N;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	int i, j;
	Read(s + 1, N); SAM::Init();
	for (i = 1; i <= N; i++) pos[i] = SAM::Extend(s[i] - 'a');
	SAM::Work(N); Manacher(s, N);
	return 0;
}
