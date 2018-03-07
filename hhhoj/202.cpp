#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 300010;
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
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1]; int val[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int n, K, m, vis[V], To[V], pT, fa[V];
int inS[V];
void dfs(int u) {
	vis[u] = 1; inS[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		if (!vis[v]) {
			To[v] = i; fa[v] = u; dfs(v);
		}
		else if (inS[v]) {
			val[i] += (1 << pT);
			for (int p = u; p != v; p = fa[p])
				val[To[p]] += (1 << pT);
			++pT;
		}
	}
	inS[u] = 0;
	//vis[u] = 2;
}
struct Xor {
	int p[12];
	bool Add(int x) {
		for (int i = 11; ~i; i--) {
			if (!(x >> i)) continue;
			if (!p[i]) {
				p[i] = x; return 0;
			}
			x ^= p[i];
		}
		return 1;
	}
} nul;
int Tot[1 << 15], s[V], t;
LL Ans;
void Work(int now, Xor jd, LL pre) {
	if (now == t + 1) {
		//for (int i = 1; i <= t; i++) cout << c[i] << ' '; cout << endl << pre << endl;
		(Ans += pre) %= P; return;
	}
	Work(now + 1, jd, pre);
	if (jd.Add(s[now])) return;
	Work(now + 1, jd, pre * Tot[s[now]] % P);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K); m = n - 1 + K;
	int x, y;
	for (int i = 1; i <= m; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	dfs(1);
	for (int i = 1; i <= sub; i++)
		if (val[i]) {
			if (!Tot[val[i]]) s[++t] = val[i];
			Tot[val[i]]++;
		}
	Work(1, nul, 1);
	cout << Ans << endl;
	return 0;
}
