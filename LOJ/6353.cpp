#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PI;
typedef long long LL;

const int V = 1000010;
const int P = 1000000007;

double lnf[V]; int fac[V], inv[V];
inline int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (LL)r * x % P;
		y >>= 1; if (y) x = (LL)x * x % P;
	}
	return r;
}
void Pre(int n) {
	for (int i = 1; i <= n; i++) lnf[i] = lnf[i - 1] + log(i);
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % P;
	inv[n] = Ksm(fac[n], P - 2);
	for (int i = n - 1; ~i; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % P;
}
inline double lnC(int n, int k) {
	return lnf[n] - lnf[n - k] - lnf[k];
}
inline int C(int n, int k) {
	return (LL)fac[n] * inv[k] % P * inv[n - k] % P;
}

struct Node {
	int n, K; double val;
	Node() {
	}
	Node(int n, int K, double val) : n(n), K(K), val(val) {}
	friend bool operator < (const Node &a, const Node &b) {
		return a.val < b.val;
	}
};
priority_queue<Node> q;
map<PI, int> exist;

int n, K;

inline void Push(int n, int K) {
	if (n < 0 || K < 0 || K > n) return;
	PI key = PI(n, K);
	if (exist.count(key)) return;
	exist[key] = 1;
	q.push(Node(n, K, lnC(n, K)));
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	cin >> n >> K; Pre(n);

	int ans = 0; Push(n, n / 2);
	while (K--) {
		Node u = q.top(); q.pop();
		ans = (ans + C(u.n, u.K)) % P;
		Push(u.n, u.K - 1); Push(u.n, u.K + 1); Push(u.n - 1, u.K); Push(u.n - 1, u.K - 1);
	}

	cout << ans << endl;

	return 0;
}
