#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PI;
typedef pair<PI, PI> PII;
typedef long double DB;
const int V = 100010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(LL &x) {
	x = 0; static char c; int f = 0;
	for (; !(c >= '0' && c <= '9'); c = get()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get()); if (f) x = -x;
}
LL N;
struct Li {
	LL A, B, C;
} li[V];
LL gcd(LL a, LL b) {
	return !b ? a : gcd(b, a % b);
}
vector<PII> G;
void Work(Li u, Li v) {
	LL D = u.A * v.B - v.A * u.B;
	if (!D) return;
	LL X = u.B * v.C - v.B * u.C;
	LL Y = v.A * u.C - u.A * v.C;
	LL g1 = gcd(D, X), g2 = gcd(D, Y);
	G.emplace_back(PII(PI(X / g1, D / g1), PI(Y / g2, D / g2)));
}
int C(PI a, PI b, LL P) {
	return a.first % P * b.second % P == a.second % P * b.first % P;
}
int C(PII a, PII b, LL P) {
	return C(a.first, b.first, P) && C(a.second, b.second, P);
}
int C(PII a, PII b) {
	return C(a, b, 23333333) && C(a, b, 593119681) && C(a, b, 1000000007);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(li[i].A); Read(li[i].B); Read(li[i].C);
	}
	for (i = 1; i <= N; i++)
		for (j = i + 1; j <= N; j++)
			Work(li[i], li[j]);
	sort(G.begin(), G.end());
	int t = 0, Mx = 0, Ti = 0;
	for (j = 0; j < G.size(); j++) {
		if (!j || C(G[j], G[j - 1])) t++;
		else t = 1;
		if (t > Mx) Mx = t, Ti = 1;
		else if (t == Mx) Ti++;
	}
	for (i = 1; i; i++)
		if (i * (i - 1) / 2 == Mx) {
			printf("%d %d\n", i, Ti);
			return 0;
		}
	return 0;
}
