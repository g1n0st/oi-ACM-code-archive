#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 300110;
const int P = 1000000007;
int Max(int a, int b) {
	return a > b ? a : b;
}
int Min(int a, int b) {
	return a < b ? a : b;
}
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
		x = x * 10 + c - '0';
		c = get();
	}
}
 
void $(int &x, int y) {
	(x += y) %= P;
}
 
struct Mat {
	int a[2][2];
	Mat() {
		memset(a, 0, sizeof a);
	}
	Mat(int f1, int f2) {
		a[0][0] = f1; a[1][1] = f2;
		a[0][1] = a[1][0] = 0;
	}
	int * operator [] (const int x) {
		return a[x];
	}
	friend Mat operator + (Mat x, Mat y) {
		Mat z; static int i, j;
		for (i = 0; i < 2; i++)
			for (j = 0; j < 2; j++)
				$(z.a[i][j], x[i][j] + y[i][j]);
		return z;
	}
	friend Mat operator * (Mat x, Mat y) {
		Mat z; static int i, j, k;
		for (i = 0; i < 2; i++)
			for (j = 0; j < 2; j++)
				for (k = 0; k < 2; k++)
					$(z.a[i][j], (LL)x[i][k] * y[k][j] % P);
		return z;
	}
} w[V];
 
void InitMat(int n) {
	int i, j;
	w[1].a[0][0] = 0; w[1].a[1][0] = w[1].a[0][1] = w[1].a[1][1] = 1;
	for (i = 2; i <= n; i++) w[i] = w[i - 1] * w[1];
}
 
int T, N, M;
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]), head[a] = sub;
}
int siz[V], son[V], root, S, rt[V][2];
bool vis[V];
 
namespace Q {
#define Maxw (V * 300)
	int f1[Maxw], f2[Maxw];
	int ls[Maxw], rs[Maxw], sz;
	void Modify(int &o, int l, int r, int L, int R, int A, int B) {
		if (!o) o = ++sz;
		if (l >= L && r <= R) {
			$(f1[o], A); $(f2[o], B);
			return;
		}
		int Mid = (l + r) >> 1;
		if (L <= Mid) Modify(ls[o], l, Mid, L, R, A, B);
		if (Mid < R) Modify(rs[o], Mid + 1, r, L, R, A, B);
	}
	int F1, F2;
	void Query(int o, int l, int r, int v) {
		$(F1, f1[o]); $(F2, f2[o]);
		if (!o || l == r) return;
		int Mid = (l + r) >> 1;
		if (v <= Mid) Query(ls[o], l, Mid, v);
		else Query(rs[o], Mid + 1, r, v);
	}
	Mat Que(int o, int l, int r, int v) {
		F1 = 0; F2 = 0;
		Query(o, l, r, v);
		return Mat(F1, F2);
	}
#undef Maxw
};
int Mulx(Mat x, int y) {
	if (!y) return x.a[0][0];
	Mat mt = x * w[y];
	return (mt[0][0] + mt[1][0]) % P;
}
 
void getRt(int u, int fa) {
	siz[u] = 1;
	son[u] = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (v == fa || vis[v]) continue;
		getRt(v, u);
		siz[u] += siz[v];
		son[u] = Max(son[u], siz[v]);
	}
	son[u] = Max(son[u], S - siz[u]);
	if (son[u] < son[root]) root = u;
}
int p[V][25], dis[V][25], MxDep[V];
void Divide(int u, int fa, int dep) {
	p[u][++*p[u]] = root; dis[u][++*dis[u]] = dep;
	MxDep[root] = Max(MxDep[root], dep);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (v == fa || vis[v]) continue;
		Divide(v, u, dep + 1);
	}
}
void Solve(int x) {
	vis[x] = 1;
	Divide(x, 0, 0);
	for (int i = head[x], v; i; i = edge[i].nxt) {
		v = edge[i].to;
		if (vis[v]) continue;
		S = siz[v];
		root = 0;
		getRt(v, 0);
		Solve(root);
	}
}
void Modify(int x, int d, int A, int B) {
	Q::Modify(rt[x][0], 0, MxDep[x], 0, d, A, B);
	int dist, u, fu;
	for (int i = *p[x]; i > 1; i--) {
		dist = dis[x][i - 1]; u = p[x][i]; fu = p[x][i - 1];
		if (dist > d) continue;
		int AA = Mulx(Mat(A, B), dist), BB = Mulx(Mat(A, B), dist + 1);
		Q::Modify(rt[u][1], 0, MxDep[fu], 0, Min(MxDep[fu], d - dist), AA, BB);
		Q::Modify(rt[fu][0], 0, MxDep[fu], 0, Min(MxDep[fu], d - dist), AA, BB);
	}
}
int Ask(int x) {
	int dist, u, fu; int Ret = 0;
	$(Ret, Mulx(Q::Que(rt[x][0], 0, MxDep[x], 0), 0));
	for (int i = *p[x]; i > 1; i--) {
		dist = dis[x][i - 1]; u = p[x][i]; fu = p[x][i - 1];
		$(Ret, Mulx(Q::Que(rt[fu][0], 0, MxDep[fu], Min(dist, MxDep[fu])), dist));
		$(Ret, P - Mulx(Q::Que(rt[u][1], 0, MxDep[fu], Min(dist, MxDep[fu])), dist));
	}
	return Ret;
}
void Clear() {
	int i, j;
	for (i = 0; i <= N + 100; i++) head[i] = 0;
	for (i = 0; i <= N + 100; i++) rt[i][0] = rt[i][1] = 0;
	for (i = 0; i <= Q::sz + 100; i++) Q::f1[i] = Q::f2[i] = Q::ls[i] = Q::rs[i] = 0;
	for (i = 0; i <= N + 100; i++) siz[i] = son[i] = vis[i] = 0;
	for (i = 0; i <= N + 100; i++) dis[i][0] = p[i][0] = MxDep[i] = 0;
	memset(dis, 0, sizeof dis);
	memset(p, 0, sizeof p);
	sub = Q::sz = root = S = 0;
}
void SolveP() {
	int i, j, x, y;
	Clear();
	Read(N); Read(M);
	for (i = 1; i < N; i++) {
		Read(x); Read(y);
		Add(x, y); Add(y, x);
	}
	S = son[0] = N;
	getRt(1, 0);
	Solve(root);
	int op, v, k, a, b;
	while (M--) {
		Read(op); Read(v);
		if (op & 1) {
			Read(k); Read(a); Read(b);
			Modify(v, k, (int)a, (int)b);
		} else {
			printf("%d\n", Ask(v));
		}
	}
}
int main(void) {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	InitMat(300000);
	Read(T); while (T--) SolveP();
	return 0;
}
