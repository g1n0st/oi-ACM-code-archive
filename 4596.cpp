#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const int V = 100010;
const int P = 1000000007;
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
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
const int N = 20;
LL a[N][N];
LL Gauss(int n) {
	LL Det = 1, f = 1;
	int i, j, k;
	for (i = 1; i < n; i++)
		for (j = 1; j < n; j++)
			(a[i][j] += P) %= P;
	for (i = 1; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			LL x = a[i][i], y = a[j][i];
			while (y) {
				LL t = x / y; x %= y; swap(x, y);
				for (k = i; k < n; k++) a[i][k] = (a[i][k] - (LL)a[j][k] * t % P + P) % P;
				for (k = i; k < n; k++) swap(a[i][k], a[j][k]);
				f = -f;
			}
		}
		if (!a[i][i]) return 0;
		Det = (LL)Det * a[i][i] % P;
	}
	if (f == -1) Det = (P - Det) % P;
	return Det;
}
void Add(int x, int y) {
	a[x][x]++; a[y][y]++;
	a[x][y]--; a[y][x]--;
}
int n;
vector<PI> G[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, x, y, t, s;
	Read(n);
	for (i = 1; i < n; i++) {
		Read(t); 
		for (j = 1; j <= t; j++) {
			Read(x); Read(y); G[i].push_back(PI(x, y));
		}
	}
	LL Ans = 0;
	for (s = 0; s < (1 << (n - 1)); s++) {
		t = 0;
		memset(a, 0, sizeof a);
		for (i = 0; i < n - 1; i++)
			if ((s >> i) & 1) {
				for (j = 0; j < G[i + 1].size(); j++)
					Add(G[i + 1][j].first, G[i + 1][j].second);
				t++;
			}
		t = n - 1 - t;
		LL v = Gauss(n);
		if (t & 1) (Ans += (P - v)) %= P;
		else 
			(Ans += v) %= P;
	}
	printf("%lld\n", Ans);
	return 0;
}
