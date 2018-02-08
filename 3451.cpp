#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long LL;
const db pi = acos(-1);
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
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
struct E {
	db x, y;
	E(db x = 0, db y = 0) : x(x), y(y) {}
	friend E operator + (const E &a, const E &b) {
		return E(a.x + b.x, a.y + b.y);
	}
	friend E operator - (const E &a, const E &b) {
		return E(a.x - b.x, a.y - b.y);
	}
	friend E operator * (const E &a, const E &b) {
		return E(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
	}
	friend E operator / (const E &a, db t) {
		return E(a.x / t, a.y / t);
	}
	LL real() {
		return (LL)(x + 0.1);
	}
};
namespace FFT {
	int n, L, R[V << 2];
	void Init(int m) {
		static int n1, L1;
		for (n1 = 1, L1 = 0; n1 <= m; n1 <<= 1, L1++); n1 <<= 1; L1++;
		if (n1 == n) return; n = n1; L = L1;
		for (int i = 0; i < n; i++)
			R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	}
	void fft(E *a, int f) {
		for (int i = 0; i < n; i++)
			if (i < R[i]) swap(a[i], a[R[i]]);
		for (int i = 1; i < n; i <<= 1) {
			E wn(cos(pi / i), f * sin(pi / i));
			for (int j = 0; j < n; j += (i << 1)) {
				E w(1, 0);
				for (int k = 0; k < i; k++, w = w * wn) {
					E x = a[j + k], y = w * a[i + j + k];
					a[j + k] = x + y; a[i + j + k] = x - y;
				}
			}
		}
		if (f == -1) for (int i = 0; i < n; i++) a[i] = a[i] / n;
	}
}
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V << 1];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
int N, w[V], tot, mx, lst[V]; LL res[V];
int S, rt, siz[V], son[V], vis[V];
void getroot(int u, int fa) {
	siz[u] = 1; son[u] = 0;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v] || v == fa) continue;
		getroot(v, u); siz[u] += siz[v]; son[u] = max(son[u], siz[v]);
	}
	son[u] = max(son[u], S - siz[u]);
	if (son[u] < son[rt]) rt = u;
}
void getdeep(int u, int fa, int d) {
	mx = max(mx, d); w[++tot] = d;
	for (int i = head[u], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v] || v == fa) continue; getdeep(v, u, d + 1);
	}
}
E a[V << 2], b[V << 2], c[V << 2];
void Solve(int x) {
	vis[x] = 1; mx = 0;
	for (int i = head[x], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v]) continue;
		tot = 0; getdeep(v, x, 1); FFT::Init(mx);
		for (int i = 0; i < FFT::n; i++) a[i] = E(lst[i]);
		for (int i = 0; i < FFT::n; i++) b[i] = E(0);
		for (int i = 1; i <= tot; i++) b[w[i]].x += 1, lst[w[i]]++;
		FFT::fft(a, 1); FFT::fft(b, 1);
		for (int i = 0; i < FFT::n; i++) c[i] = a[i] * b[i];
		FFT::fft(c, -1);
		for (int i = 0; i < FFT::n; i++) res[i] += c[i].real();
	}
	for (int i = 1; i <= mx; i++) res[i] += lst[i], lst[i] = 0;
	for (int i = head[x], v; i; i = edge[i].nxt) {
		v = edge[i].to; if (vis[v]) continue;
		S = siz[v]; rt = 0; getroot(v, 0); Solve(rt);
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); int x, y;
	for (int i = 1; i < N; i++) {
		Read(x); Read(y); x++; y++; Add(x, y); Add(y, x);
	}
	son[0] = S = N; getroot(1, 0); 
	Solve(rt);
	db ans = 0;
	for (int i = 1; i <= N; i++) ans += (db)res[i] / (i + 1);
	ans = ans * 2 + N;
	printf("%.4lf\n", ans);
	return 0;
}
