#include <bits/stdc++.h>
using  namespace std;
typedef long long LL;
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
	for (; islower(c); s[len++] = c, c = get());
}

int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int mx[V], siz[V], vis[V], S, rt;
void getRoot(int u, int fa) {
	siz[u] = 1; mx[u] = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v] || v == fa) continue;
		getRoot(v, u); siz[u] += siz[v]; mx[u] = max(mx[u], siz[v]);
	}
	mx[u] = max(mx[u], S - siz[u]);
	if (mx[u] < mx[rt]) rt = u;
}
int n, cnt[1 << 21]; char s[V];
LL ans[V];
void dfs(int u, int fa, int now, int f) {
	cnt[now ^= (1 << s[u])] += f;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v] || v == fa) continue; dfs(v, u, now, f);
	}
}
LL cal(int u, int fa, int now) {
	now ^= (1 << s[u]);
	LL r = cnt[now];
	for (int i = 0; i < 20; i++) r += cnt[now ^ (1 << i)];
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v] || v == fa) continue; r += cal(v, u, now);
	}
	ans[u] += r;
	return r;
}
void Solve(int u) {
	vis[u] = 1; dfs(u, 0, 0, 1); LL r = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v]) continue;
		dfs(v, u, 1 << s[u], -1); r += cal(v, u, 0); dfs(v, u, 1 << s[u], 1);
	}
	r += cnt[0];
	for (int i = 0; i < 20; i++) r += cnt[1 << i];
	ans[u] += (r + 1) / 2;
	dfs(u, 0, 0, -1);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v]) continue;
		S = siz[v]; rt = 0; getRoot(v, u); Solve(rt);
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	int x, y;
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	Read(s + 1, n); for (int i = 1; i <= n; i++) s[i] -= 'a';
	mx[0] = S = n; getRoot(1, 0); Solve(rt);
	for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);
	return 0;
}
