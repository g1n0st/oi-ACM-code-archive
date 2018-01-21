#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(LL &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !(c >= 'A' && c <= 'Z'); c = get());
	for (; c >= 'A' && c <= 'Z'; s[len++] = c, c = get());
}
struct Mat {
	LL a[4][4];
	Mat(LL x = 0) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) a[i][j] = x;
	}
	friend Mat operator * (Mat a, Mat b) {
		Mat r(1e18);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++)
					r.a[i][j] = min(r.a[i][j], a.a[i][k] + b.a[k][j]);
		return r;
	}
};
Mat Mulx(Mat x, LL y) {
	Mat r;
	while (y) {
		if (y & 1) r = r * x;
		y >>= 1;
		if (y) x = x * x;
	}
	return r;
}
namespace SAM {
	int fa[V << 1], c[V << 1][4], len[V << 1], lst, pT, rt;
	void Init() {
		rt = lst = ++pT;
	}
	void Extend(int x) {
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
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[q] = fa[cur] = pT;
			}
		}
		lst = cur;
	}
	int vis[V << 1]; LL mu[V << 1][4];
	void Dfs(int u) {
		if (vis[u]) return; vis[u] = 1;
		for (int i = 0; i < 4; i++)
			if (c[u][i]) Dfs(c[u][i]), mu[u][i] = 1e18;
		for (int i = 0; i < 4; i++) {
			if (!c[u][i]) mu[u][i] = 1;
			else for (int j = 0; j < 4; j++)
				mu[u][j] = min(mu[u][j], mu[c[u][i]][j] + 1);
		}
	}
}
char s[V];
int N; LL M;
Mat v;
void Init() {
	int i, j;
	Read(M); Read(s + 1, N); SAM::Init();
	for (i = 1; i <= N; i++) SAM::Extend(s[i] - 'A');
	SAM::Dfs(SAM::rt);
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			v.a[i][j] = SAM::mu[SAM::c[1][i]][j];
}
bool Check(LL t) {
	Mat x = Mulx(v, t); LL Mx = 1e18;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			Mx = min(Mx, x.a[i][j]);
	return Mx >= M;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Init();
	LL L = 1, R = M, Mid, Ans = M + 1;
	while (L <= R) {
		Mid = (L + R) >> 1;
		if (Check(Mid)) R = (Ans = Mid) - 1;
		else L = Mid + 1;
	}
	if (Ans == M + 1) printf("0\n");
	else printf("%lld\n", Ans);
	return 0;
}
