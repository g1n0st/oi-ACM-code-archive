#include <bits/stdc++.h>
using namespace std;
const int V = 2000010;
char dis() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = dis());
	for (; isdigit(c); x = x * 10 + c - '0', c = dis());
}
vector<int> g[V];
int sz, pT;
int n, Q, p[V], in[V], win[V], f[V], vis[V], w[V], be[V];
int dfs(int u) {
	win[u] = 0;
	for (auto v : g[u]) {
		if (in[v]) continue; if (!dfs(v)) win[u] = 1;
	}
	return win[u];
}
int dis(int u, int v) {
	return w[u] < w[v] ? w[v] - w[u] - 1 : pT - w[u] + w[v] - 1;
}
#define GJGHFD {puts("1"); continue;}
#define LJN {puts("0"); continue;}
#define	DRAW {puts("2"); continue;}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(Q); int x;
	for (int i = 1; i <= n; i++) {
		Read(x); g[x].emplace_back(i); p[i] = x;
	}
	int t = 1;
	for (int i = 1; i <= n; i++, t = p[t]);
	for (; !in[t]; t = p[t]) in[t] = 1, sz++;
	for (int i = 1; i <= n; i++) {
		if (in[i]) dfs(i);
	}
	memset(f, 0x3f, sizeof f);
	for (; sz; --sz, w[t] = pT++, t = p[t]) {
		if (win[t]) {
			f[t] = 0; be[t] = t;
			for (int now(p[t]), cnt = 1; !win[now] && now ^ t; now = p[now]) {
				be[now] = t; f[now] = cnt++;
			}
		}
	}
	int u, v;
	while (Q--) {
		Read(u); Read(v);
		// in chain
		if (!in[1]) if (win[1]) GJGHFD else LJN // in chain before
		if ((w[v] < w[u] && (w[1] < w[v] || w[1] > w[u])) ||
			((w[v] > w[u]) && (w[1] > w[u] && w[1] < w[v])) || (u == v && u != 1)) { // in chain last
			if (f[1] <= dis(u, 1) && (f[1] & 1)) LJN
			if (f[1] > dis(u, 1) && !(dis(u, 1) & 1)) LJN
			GJGHFD
		}
		if (u == v && u == 1) { // cycle in start
			if (f[1] <= dis(1, 1) && (f[1] & 1)) DRAW
			if (f[1] > dis(1, 1) && !(dis(1, 1) & 1)) DRAW;
		}
		// in cycle
		if (p[u] == v) { // totally cycle
			if (f[1] == 0x3f3f3f3f) DRAW
			if (f[1] & 1) LJN
			else GJGHFD
		}
		if ((f[v] && f[u] && be[u] == be[v] && f[u] > f[v]) || !be[u]) {
			if (f[v] <= dis(u, v) && (f[v] & 1)) DRAW
			if (dis(u, v) < f[v] && !(dis(u, v) & 1)) DRAW
			if ((pT - dis(1, v) - 1) & 1) LJN
			else GJGHFD
		}
		if (dis(u, v) <= f[v] && !(dis(u, v) & 1) || f[v] <= dis(u, v) && (f[v] & 1)) {
			if (f[1] < pT - dis(1, v) - 1) {
				if (f[1] & 1) LJN else GJGHFD
			}
			if ((pT - dis(1, v) + f[u]) & 1) LJN else GJGHFD
		}
		int d = min(pT - dis(1, v) - 1, f[1]);
		if (d & 1) LJN else GJGHFD
	}
	return 0;
}
