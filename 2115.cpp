#include <bits/stdc++.h>
using namespace std;
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
template<class T>
void Read(T &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int N, M, vis[V];
LL w[V], p[70];
vector<LL> cir;
int head[V], sub;
struct Edge {
	int to, nxt; LL v;
	Edge() {}
	Edge(int to, int nxt, LL v) : to(to), nxt(nxt), v(v) {}
} edge[V * 10];
void Add(int a, int b, LL v) {
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
void Dfs(int u) {
	vis[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (!vis[v]) {
			w[v] = w[u] ^ edge[i].v; Dfs(v);
		}
		else cir.push_back(w[v] ^ w[u] ^ edge[i].v);
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, u, v; LL w;
	Read(N); Read(M);
	for (i = 1; i <= M; i++) {
		Read(u); Read(v); Read(w); 
		Add(u, v, w); Add(v, u, w);
	}
	Dfs(1);
	for (i = 0; i < cir.size(); i++)
		for (j = 62; ~j; j--) {
			if (!(cir[i] >> j)) continue;
			if (!p[j]) {
				p[j] = cir[i]; break;
			}
			cir[i] ^= p[j];
		}
	LL Ans = ::w[N];
	for (i = 62; ~i; i--) if ((Ans ^ p[i]) > Ans) Ans ^= p[i];
	printf("%lld\n", Ans);
	return 0;
}
