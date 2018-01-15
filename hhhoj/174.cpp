#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pl;
const int V = 100010;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
LL Ans;
int N, P, a[V];
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V * 2];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int siz[V], son[V], rt, S, vis[V];
void gRt(int u, int fa) {
	siz[u] = 1; son[u] = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v] || v == fa) continue;
		gRt(v, u); siz[u] += siz[v]; son[u] = max(son[u], siz[v]);
	}
	son[u] = max(son[u], S - siz[u]);
	if (son[u] < son[rt]) rt = u;
}
void $(int &x, int y) {
	y = (y % P + P) % P;
	(x += y) %= P;
}
vector<pl> Qu, Qv;
void Dfs(int u, int fa, int mx, int s) {
	int t = s; $(t, a[rt]); $(t, -max(mx, a[rt]));
	if (!t) Ans++;
	Qv.emplace_back(pl(mx, s));
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v] || v == fa) continue;
		Dfs(v, u, max(mx, a[v]), (s + a[v]) % P);
	}
}
int lst[10000010];
void Calc(vector<pl> q, int w) {
	sort(q.begin(), q.end());
	for (auto b : q) {
		if (b.first < a[rt]) {
			Ans += w * lst[P - b.second];
		}
		else {
			int t = b.second; $(t, -b.first); $(t, a[rt]);
			Ans += w * lst[(P - t) % P];
		}
		lst[b.second]++;
	}
	for (auto b : q) lst[b.second]--;
}
void Solve(int x) {
	vis[x] = 1; Ans++; Qu.clear();
	for (int i = head[x], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v]) continue;
		Qv.clear();
		Dfs(v, 0, a[v], a[v] % P); Calc(Qv, -1);
		Qu.insert(Qu.end(), Qv.begin(), Qv.end());
	}
	Calc(Qu, 1);
	for (int i = head[x], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v]) continue;
		S = siz[v]; rt = 0; gRt(v, 0);
		Solve(rt);
	}
}
int main() {
	int i, j, x, y;
	Read(N); Read(P);
	for (i = 1; i < N; i++) {
		Read(x); Read(y);
		Add(x, y); Add(y, x);
	}
	for (i = 1; i <= N; i++) {
		Read(a[i]);
	}
	son[0] = S = N; gRt(1, 0);
	Solve(rt);
	printf("%lld\n", Ans);
	return 0;
}
