#include <bits/stdc++.h>
using namespace std;
const int V = 100100;
typedef long long LL;
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
int T, A, B, C, D, K;
int pri[V], tot, vis[V], mul[V], sum[V];
void Init(int n) {
	int i, j;
	mul[1] = 1;
	for (i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++tot] = i; mul[i] = -1;
		}
		for (j = 1; j <= tot && i * pri[j] <= n; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j]) mul[i * pri[j]] = -mul[i];
			else {
				mul[i * pri[j]] = 0; break;
			}
		}
	}
	for (i = 1; i <= n; i++) sum[i] = sum[i - 1] + mul[i];
}
int Solve(int n, int m) {
	n /= K; m /= K;
	if (n > m) swap(n, m); if (n == 0) return 0;
	int Ret = 0;
	for (int i = 1, nxt; i <= n; i = nxt + 1) {
		nxt = min(n / (n / i), m / (m / i));
		Ret += (n / i) * (m / i) * (sum[nxt] - sum[i - 1]);
	}
	return Ret;
}
int main() {
	Init(100000);
	Read(T);
	while (T--) {
		Read(A); Read(B); Read(C); Read(D); Read(K);
		int Ans = Solve(B, D) - Solve(A - 1, D) - Solve(B, C - 1) + Solve(A - 1, C - 1);
		printf("%d\n", Ans);
	}
	return 0;
}
