#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 200010;
const int M = 720;
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
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !(c >= 'a' && c <= 'z'); c = get());
	for (; c >= 'a' && c <= 'z'; s[len++] = c, c = get()); s[len] = 0;
}
namespace SAM {
	int fa[V << 1], len[V << 1], c[V << 1][26], rt, lst, pT; LL val[V << 1];
	void Init() {
		rt = lst = ++pT;
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
	int v[V << 1], q[V << 1];
	void Work(int n) {
		int i, t;
		for (i = 1; i <= pT; i++) v[len[i]]++;
		for (i = 1; i <= n; i++) v[i] += v[i - 1];
		for (i = pT; i; i--) q[v[len[i]]--] = i;
		for (i = pT; i; i--) {
			t = q[i]; val[fa[t]] += val[t];
		}
	}
	int f[V][25];
	void Build() {
		int i, j, t;
		for (i = 1; i <= pT; i++) {
			t = q[i]; f[t][0] = fa[t];
			for (j = 1; j <= 20; j++) f[t][j] = f[f[t][j - 1]][j - 1];
		}
	}
	void Nxt(int &now, int &val, int x) {
		if (c[now][x]) {
			now = c[now][x]; val++;
			return;
		}
		while (now && !c[now][x]) now = fa[now];
		if (!now) {
			now = 1; val = 0;
		}
		else {
			val = len[now] + 1; now = c[now][x];
		}
	}
	LL Query(int now, int v) {
		if (len[now] < v) return 0;
		for (int i = 20; ~i; i--)
			if (len[f[now][i]] >= v) now = f[now][i];
		return val[now];
	}
}
int n, m, q, k;
char s[V];
struct No1 {
	int l, r;
} d[V];
struct No2 {
	int l, r, id;
} qr[V];

namespace Work1 {
	int bel[V];
	char ss[V][M];
	int cnt[M][M]; LL Ans[V];
	bool cmp(const No2 &x, const No2 &y) {
		return bel[x.l] < bel[y.l] ||
			(bel[x.l] == bel[y.l] && (bel[x.l] & 1 ? x.r < y.r : x.r > y.r));
	}
	void Modi(int op, int x) {
		cnt[d[op].l][d[op].r] += x;
	}
	void Solve() {
		int i, j, l; int sqM = sqrt(m);
		for (i = 1; i <= m; i++) bel[i] = (i - 1) / sqM + 1;
		for (i = 1; i <= q; i++) {
			Read(ss[i] + 1, l); Read(qr[i].l); Read(qr[i].r); qr[i].id = i;
			qr[i].l++; qr[i].r++;
		}
		sort(qr + 1, qr + 1 + q, cmp);
		int L = 1, R = 0;
		for (i = 1; i <= q; i++) {
			while (L < qr[i].l) Modi(L++, -1);
			while (R > qr[i].r) Modi(R--, -1);
			while (L > qr[i].l) Modi(--L, 1);
			while (R < qr[i].r) Modi(++R, 1);
			for (int S = 1; S <= k; S++) {
				int now = 1;
				for (int T = S; T <= k; T++) {
					now = SAM::c[now][ss[qr[i].id][T] - 'a'];
					if (!now) break;
					Ans[qr[i].id] += (LL)cnt[S][T] * SAM::val[now];
				}
			}
		}
		for (i = 1; i <= q; i++) printf("%lld\n", Ans[i]);
	}
}
namespace Work2 {
	vector<int> G[V];
	char w[V];
	void Solve() {
		int i, j, l, r;
		SAM::Build();
		for (i = 1; i <= q; i++) {
			Read(w + 1, l); Read(l); Read(r); l++; r++;
			for (j = l; j <= r; j++) G[d[j].r].emplace_back(d[j].r - d[j].l + 1);
			LL Ans = 0; int now = 1, val = 0;
			for (j = 1; j <= k; j++) {
				SAM::Nxt(now, val, w[j] - 'a');
				for (auto v : G[j]) {
					if (v > val) continue;
					Ans += SAM::Query(now, v);
				}
				G[j].clear();
			}
			printf("%lld\n", Ans);
		}
	}
}

void Init() {
	int i, j;
	Read(n); Read(m); Read(q); Read(k);
	Read(s + 1, n); SAM::Init();
	for (i = 1; i <= n; i++) SAM::Extend(s[i] - 'a');
	for (i = 1; i <= m; i++) {
		Read(d[i].l); Read(d[i].r); d[i].l++; d[i].r++;
	}
	SAM::Work(n);
}
int main() {
	Init();
	if (k < M)
		Work1::Solve();
	else
		Work2::Solve();
	return 0;
}
