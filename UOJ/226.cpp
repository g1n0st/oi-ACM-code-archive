#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 10000010;
const int N = 10010;
const int P = 998244353;
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
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
int n, m;
int fac[V], inv[V];
int C(int a, int b) {
	return (LL)fac[a] * inv[b] % P * inv[a - b] % P;
}
void Pre(int n) {
	fac[0] = 1; for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % P;
	inv[n] = Ksm(fac[n], P - 2); for (int i = n - 1; ~i; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % P;
}

int head[N], sub;
struct Edge {
	int to, nxt, v;
	Edge() {}
	Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v){}
} edge[N << 1];
void Add(int a, int b, int v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
int rt, num, p, f[N], fa[N], w[N], deg[N];
int getf(int x) {
	return x == f[x] ? x : getf(f[x]);
}
void dfs(int u) {
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; w[v] = edge[i].v; dfs(v);
	}
}
int Work() {
	static int ins[N];
	for (int i = 1; i <= n; i++) if (deg[i] & 1) return 0;
	dfs(rt);
	int res = 0;
	if (p) {
		vector<int> val;
		for (; p; p = fa[p]) {
			ins[p] = 1; if (fa[p]) val.emplace_back(w[p]);
		}
		val.emplace_back(num);
		int mn = *min_element(val.begin(), val.end());
		for (int i = -mn; i <= mn; i += 2) {
			int sum = 0, now = 1, co = 1;
			for (auto x : val) {
				int rea = (i + x) >> 1;
				sum = ((LL)sum * (x - rea) % P + now) % P;
				now = (LL)now * rea % P;
				co = (LL)co * C(x, rea) % P;
			}
			res = (res + (LL)sum * co % P) % P;
		}
	} else res = 1;
	for (int i = 1; i <= n; i++) res = (LL)res * fac[(deg[i] >> 1) - 1] % P;
	for (int i = 1; i <= n; i++) if (!ins[i] && fa[i]) res = (LL)res * C(w[i], w[i] >> 1) % P * (w[i] >> 1) % P;
	return res;
}
int main() {
	//freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	Read(n); Read(m); Pre(V - 1);
	for (int i = 1; i <= n; i++) f[i] = i;
	int x, y, z, u, v, cnt = 0; rt = 1;
	for (int i = 1; i <= m; i++) {
		Read(x); Read(y); Read(z); u = getf(x); v = getf(y);
		deg[x] += z; deg[y] += z;
		if (u == v) {
			rt = x; p = y; num = z; continue;
		}
		f[u] = v; ++cnt;
		Add(x, y, z); Add(y, x, z);
	}
	if (cnt != n - 1) puts("0");
	else printf("%d\n", Work());
	return 0;
}
