#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 110;
const int V = 20000100;
const int P = 20170408;
void Read(int &x) {
	scanf("%d", &x);
}
int vis[V], pri[V / 10], tot;
void Pre(int n) {
	vis[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) pri[++tot] = i;
		for (int j = 1; j <= tot && pri[j] * i <= n; j++) {
			vis[pri[j] * i] = 1;
			if (!(i % pri[j])) break;
		}
	}
}
int n, m, p;
int c1[N], c2[N], a1[N], a2[N];
void getVal(int *r, int *a, int *b) {
	static int g[N];
	for (int i = 0; i < p; i++) g[i] = 0;
	for (int i = 0; i < p; i++)
		for (int j = 0; j < p; j++)
			(g[(i + j) % p] += ((LL)a[i] * b[j]) % P) %= P;
	for (int i = 0; i < p; i++) r[i] = g[i];
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Read(p); Pre(m);
	for (int i = 1; i <= m; i++) c1[i % p]++;
	for (int i = 1; i <= m; i++)  if (vis[i]) c2[i % p]++;
	a1[0] = a2[0] = 1;
	while (n) {
		if (n & 1) getVal(a1, a1, c1), getVal(a2, a2, c2);
		n >>= 1; if (n) getVal(c1, c1, c1), getVal(c2, c2, c2);
	}
	cout << (a1[0] + P - a2[0]) % P << endl;
	return 0;
}
