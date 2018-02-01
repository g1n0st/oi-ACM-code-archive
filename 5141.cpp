#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 1000000007;
const int V = 100100;
void Read(int &x) {
	scanf("%d", &x);
}
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}

int c[V], N, K; LL f[V][4];
void Dfs(int u, int fa) {
	for (int i = 1; i <= 3; i++)
		if (!c[u] || c[u] == i) f[u][i] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa) continue; Dfs(v, u);
		(f[u][1] *= f[v][2] + f[v][3]) %= P;
		(f[u][2] *= f[v][1] + f[v][3]) %= P;
		(f[u][3] *= f[v][1] + f[v][2]) %= P;
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(K);
	int x, y;
	for (int i = 1; i < N; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	while (K--) {
		Read(x); Read(y); c[x] = y;
	}
	Dfs(1, 0);
	int Ans = 0;
	(Ans += f[1][1]) %= P; (Ans += f[1][2]) %= P; (Ans += f[1][3]) %= P;
	cout << Ans << endl;
	return 0;
}
