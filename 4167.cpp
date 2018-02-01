#include <bits/stdc++.h>
using namespace std;
const int V = 50010;
const int vB = 500;
const int INF = 0x7f7f7f7f;
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
int N, K, B, a[V], bel[V], bl[V], br[V];
int head[V], sub;
struct Edge {
	int to, nxt, v;
	Edge(int to = 0, int nxt = 0, int v = 0) : to(to), nxt(nxt), v(v) {}
} edge[V << 1];
void Add(int a, int b, int v) {
	//cout << a << ' ' << b << ' ' << v << endl;
	edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}

int v[V];
void Modify(int x, int val) {
	for (x; x <= N; x += x & -x) v[x] = min(v[x], val);
}
int Query(int x) {
	int r = INF;
	for (; x; x -= x & -x) r = min(r, v[x]);
	return r;
}
int s[vB], tot, indx[V][vB];
void Build(int x) {
	int L = bl[x], R = br[x]; tot = 0;
	for (int i = L; i <= R; i++) s[++tot] = a[i];
	sort(s + 1, s + 1 + tot);
	int p1 = 0, p2 = 1;
	for (int i = 1; i <= N; i++) {
		int &k = indx[i][x]; k = INF;
		while (p1 < tot && s[p1 + 1] < i) ++p1;
		while (p2 <= tot && s[p2] <= i) ++p2;
		if (p1) k = min(k, i - s[p1]);
		if (p2 != tot + 1) k = min(k, s[p2] - i);
	}
}
void Scan(int x, int L, int R, int &Now) {
	for (int i = L; i <= R; i++) {
		int val = abs(a[x] - a[i]);
		if (val && val < Now) {
			Now = val; int prev = Query(i);
			if (Now < prev) {
				Modify(i, Now); Add(i, x, Now);
			}
		}
	}
}
int f[V][1001];
int main() {
	//freopen("4167.in", "r", stdin);
	//freopen("4167.out", "w", stdout);
	Read(N); Read(K); B = sqrt(N);
	for (int i = 1; i <= N; i++) v[i] = INF;
	for (int i = 1; i <= N; i++) Read(a[i]);
	for (int i = 1; i <= N; i++) bel[i] = (i - 1) / B + 1;
	for (int i = 1; i <= N; i++) br[bel[i]] = i;
	for (int i = N; i; i--) bl[bel[i]] = i;
	B = bel[N];
	for (int i = 1; i <= B; i++) Build(i);
	for (int i = N; i; i--) {
		int Now = INF;
		Scan(i, i + 1, br[bel[i]], Now);
		for (int j = bel[i] + 1; j <= B; j++)
			if (indx[a[i]][j] < Now) Scan(i, bl[j], br[j], Now);
	}
	memset(f, 0x7f, sizeof f);
	f[0][0] = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= K; j++) {
			f[i][j] = f[i - 1][j];
			if (j) for (int k = head[i], v; k; k = edge[k].nxt) {
				v = edge[k].to;
				f[i][j] = min(f[i][j], f[v - 1][j - 1] + edge[k].v);
			}
		}
	printf("%d\n", f[N][K]);
	return 0;
}
