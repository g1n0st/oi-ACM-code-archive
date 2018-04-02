#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5001010;

const LL INF = 1LL << 60;
int n, fa[N], dep[N], sz[N], deg[N];
int a[N], b[N], nxt[N];
LL f[N], sum[N];

void Min(LL &x, LL y) {
	x = min(x, y);
}
const int V = (N << 1) + 20;
char buf[V], *p, c;
inline char get() {
	return *p++;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	p = buf; fread(buf, 1, V, stdin);
	while (1) {
		c = get(); if (c < '0' || c > '9') break;
		n = n * 10 + c - '0';
	}
	int v = 0, tot = 0;
	for (int i = 0; i < n * 2; i++) {
		if (get() == '(') {
			tot++;
			fa[tot] = v; deg[v]++;
			dep[tot] = dep[v] + 1;
			v = tot;
		}
		else
			v = fa[v];
	}
	
	for (int i = n; i >= 2; i--) {
		if (!deg[i]) {
			sz[i] = 1; a[i] = sum[i] = dep[i];
		}
		int y = fa[i], x;
		for (x = i; x && dep[x] <= a[y]; x = nxt[x]) b[x] = y;
		for (; nxt[y] && dep[nxt[y]] <= a[i]; nxt[y] = nxt[nxt[y]]) b[nxt[y]] = y;
		if (a[i] > a[y]) {
			nxt[y] = x;
			a[y] = a[i];
		}
		sum[y] += sum[i]; sz[y] += sz[i];
	}
	
	LL ans = INF;
	for (int i = 2; i <= n; i++) {
		f[i] = INF;
		if (b[i]) Min(f[i],
			f[b[i]] + sum[b[i]] - sum[i] - (LL)(sz[b[i]] - sz[i]) * dep[b[i]]
		);
		if (deg[fa[i]] == 1) Min(f[i], f[fa[i]] + 1);
	}
	for (int i = 1; i <= n; i++)
		if (!deg[i]) ans = min(ans, f[i]);
	
	cout << ans << endl;
	return 0;
}
