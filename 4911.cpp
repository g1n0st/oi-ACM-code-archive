#include <bits/stdc++.h>
using namespace std;

const int L = 100000;
char get() {
	static char buf[L], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, L, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
void Read(char &x) {
	x = get(); while (!isupper(x)) x = get();
}

const int N = 30005;
const int M = 128;
const int P = 10007;
const int INV2 = (P + 1) / 2;

void FWT(int *a, int n) {
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += (i << 1))
			for (int k = 0; k < i; k++) {
				int x = a[j + k], y = a[i + j + k];
				a[j + k] = (x + y) % P; a[i + j + k] = (x - y + P) % P;
			}
}
void UFWT(int *a, int n) {
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += (i << 1))
			for (int k = 0; k < i; k++) {
				int x = a[j + k], y = a[i + j + k];
				a[j + k] = (x + y) * INV2 % P; a[i + j + k] = (x - y + P) * INV2 % P;
			}
}

int n, K, a[N];
int jd[M][M], inv[P];

void Pre(int k) {
	for (int i = 0; i < k; i++) {
		jd[i][i] = 1; FWT(jd[i], k);
	}
	inv[1] = 1;
	for (int i = 2; i < P; i++)
		inv[i] = (P - P / i) * inv[P % i] % P;
}

struct Val {
	int x, y;
	Val(int v = 0) {
		if (v) x = v, y = 0; else x = 0, y = 1;
	}
	Val & operator *= (int v) {
		if (v) x = x * v % P; else y++; return *this;
	}
	Val & operator /= (int v) {
		if (v) x = x * inv[v] % P; else y--; return *this;
	}
	int val() {
		return y ? 0 : x;
	}
} base[N][M];

int head[N], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[N << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}

vector<int> p[N], lh;
int dep[N], siz[N], fa[N], top[N], pos[N];
void dfs1(int u) {
	siz[u] = 1;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (v == fa[u]) continue;
		fa[v] = u; dep[v] = dep[u] + 1; dfs1(v); siz[u] += siz[v];
	}
}
void dfs2(int u, int path) {
	top[u] = path; p[path].push_back(u); pos[u] = p[path].size() - 1;
	int k = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && siz[v] > siz[k]) k = v;
	}
	if (!k) return; dfs2(k, path);
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (dep[v] > dep[u] && v ^ k) dfs2(v, v);
	}
}
bool cmp(int x, int y) {
	return dep[x] > dep[y];
}

namespace SGT {
	const int V = 75000;
	int pT, ls[V], rs[V];
	int lval[V][M], rval[V][M], sum[V][M], val[V][M];
	void pushUp(int x) {
		int l = ls[x], r = rs[x];
		for (int i = 0; i < K; i++) {
			val[x][i] = (val[l][i] + val[r][i] + rval[l][i] * lval[r][i]) % P;
			lval[x][i] = (lval[l][i] + lval[r][i] * sum[l][i]) % P;
			rval[x][i] = (rval[r][i] + rval[l][i] * sum[r][i]) % P;
			sum[x][i] = sum[l][i] * sum[r][i] % P;
		}
	}
	void setVal(int x, int p) {
		for (int i = 0; i < K; i++)
			val[x][i] = lval[x][i] = rval[x][i] = sum[x][i] = base[p][i].val();
	}
	namespace func {
		int rt[N];
		void build(int &x, int l, int r, int t) {
			x = ++pT;
			if (l == r) return setVal(x, p[t][l]);
			int mid = (l + r) >> 1;
			build(ls[x], l, mid, t); build(rs[x], mid + 1, r, t);
			pushUp(x);
		}
		void modify(int x, int l, int r, int pos, int t) {
			if (l == r) return setVal(x, p[t][l]);
			int mid = (l + r) >> 1;
			if (pos <= mid) modify(ls[x], l, mid, pos, t);
			else modify(rs[x], mid + 1, r, pos, t);
			pushUp(x);
		}
	}
} using namespace SGT::func;

int ans[M], tmp[M];
void ADD(int f, int r) {
	if (f) for (int i = 0; i < K; i++)
		base[f][i] *= (SGT::lval[r][i] + jd[0][i]) % P;
	for (int i = 0; i < K; i++) (ans[i] += SGT::val[r][i]) %= P;
}
void DEL(int f, int r) {
	if (f) for (int i = 0; i < K; i++)
		base[f][i] /= (SGT::lval[r][i] + jd[0][i]) % P;
	for (int i = 0; i < K; i++) (ans[i] += P - SGT::val[r][i]) %= P;
}
void Modify(int x) {
	int t = top[x];
	DEL(fa[t], rt[t]); modify(rt[t], 0, p[t].size() - 1, pos[x], t); ADD(fa[t], rt[t]);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K); Pre(K);
	int x, y;
	for (int i = 1; i <= n; i++) {
		Read(x); a[i] = x;
		for (int j = 0; j < K; j++) base[i][j] = jd[x][j];
	}
	for (int i = 1; i < n; i++) {
		Read(x); Read(y); Add(x, y); Add(y, x);
	}
	dfs1(1); dfs2(1, 1);
	for (int i = 1; i <= n; i++) if (top[i] == i) lh.push_back(i);
	sort(lh.begin(), lh.end(), cmp);
	for (int i = 0; i < lh.size(); i++) {
		int x = lh[i]; build(rt[x], 0, p[x].size() - 1, x);
		ADD(fa[x], rt[x]);
	}
	int Q; Read(Q); char op;
	while (Q--) {
		Read(op); Read(x);
		switch (op) {
		case 'Q':
			for (int i = 0; i < K; i++) tmp[i] = ans[i];
			UFWT(tmp, K); printf("%d\n", tmp[x]); break;
		default:
			Read(y);
			for (int i = 0; i < K; i++) base[x][i] /= jd[a[x]][i];
			a[x] = y;
			for (int i = 0; i < K; i++) base[x][i] *= jd[a[x]][i];
			while (x) {
				Modify(x); x = fa[top[x]];
			}
		}
	}
	return 0;
}
