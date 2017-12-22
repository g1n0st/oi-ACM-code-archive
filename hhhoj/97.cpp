#include <cstdio>
using namespace std;
const int V = 1000100;
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
struct Node {
	int w, t;
	Node(int w = 0, int t = 0) : w(w), t(t) {}
};
int gcd(int x, int y) {
	return !y ? x : gcd(y, x % y);
}
Node Pow(int x, int y, int p) {
	Node Ans = Node(1, 0);
	while (y) {
		if (y & 1) {
			if (1LL * Ans.w * x >= p) Ans.t = 1;
			Ans.w = 1LL * Ans.w * x % p;
		}
		y >>= 1;
		if (y) {
			if (1LL * x * x >= p) Ans.t = 1;
			x = 1LL * x * x % p;
		}
	}
	return Ans;
}
int T, N, M, a[V];
int pri[V], tot, phi[V], vis[V];
void Init(int n) {
	int i, j;
	phi[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; phi[i] = i - 1;
		}
		int	t;
		for (j = 1; j <= tot && (t = pri[j] * i) <= n; j++) {
			vis[t] = 1;
			if (!(i % pri[j])) {
				phi[t] = phi[i] * pri[j];
				break;
			}
			phi[t] = phi[i] * (pri[j] - 1);
		}
	}
}
Node Solve(int k, int m) {
	if (m == 1) return Node(0, 1);
	Node Ans;
	if (k == N) {
		Ans.w = a[k] % m;
		Ans.t = (a[k] >= m);
		return Ans;
	}
	Node p = Solve(k + 1, phi[m]);
	if (gcd(a[k], m) > 1 && p.t)
		return Pow(a[k], phi[m] + p.w, m);
	else
		return Pow(a[k], p.w, m);
}
int main() {
	int i, j; Init(V - 1);
	Read(T); Read(M);
	while (T--) {
		Read(N);
		for (i = 1; i <= N; i++) Read(a[i]);
		printf("%d\n", Solve(1, M).w);
	}
	return 0;
}
