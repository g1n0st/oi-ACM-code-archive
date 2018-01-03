#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000050;
void Read(LL &x) {
	scanf("%lld", &x);
}
LL T, N, K, P;
LL y[V], tot;
void Add(LL &x, LL y) {
	(x += y) %= P;
}
LL Pow(LL x, LL y) {
	LL Ret = 1;
	while (y) {
		if (y & 1) Ret = (Ret * x) % P;
		y >>= 1;
		if (y) x = (x * x) % P;
	}
	return Ret;
}
struct Mat {
	LL a[2][2];
	Mat() {
		memset(a, 0, sizeof a);
	}
	friend Mat operator + (const Mat a, const Mat b) {
		Mat c;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				Add(c.a[i][j], a.a[i][j] + b.a[i][j]);
		return c;
	}
	friend Mat operator * (const Mat a, const Mat b) {
		Mat c;
		for (int k = 0; k < 2; k++)
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					Add(c.a[i][j], a.a[i][k] * b.a[k][j]);
		return c;
	}
} fibw;
Mat Pow(Mat x, LL y) {
	Mat Ret = x; y--;
	while (y) {
		if (y & 1) Ret = Ret * x;
		y >>= 1;
		if (y) x = x * x;
	}
	return Ret;
}
LL Calc(LL x) {
	Mat Ans;
	Ans.a[0][0] = Ans.a[1][1] = x; Ans.a[1][0] = Ans.a[0][1] = 0;
	Ans = Ans + fibw;
	Ans = Pow(Ans, N);
	return Ans.a[0][0] * Pow(Pow(x, N), P - 2) % P;
}
void Init(LL x) {
	for (int i = 2; i <= sqrt(x); i++) {
		if (x % i) continue;
		y[++tot] = i; if (x / i > i) y[++tot] = (x / i);
	}
}
bool Judge(int x) {
	for (int i = 1; i <= tot; i++)
		if (Pow(x, y[i]) == 1) return 0;
	return 1;
}
int GtG() {
	Init(P - 1);
	for (int g = 2;; g++)
		if (Judge(g)) return g;
}
void Solve() {
	int i, j;
	Read(N); Read(K); Read(P);
	fibw.a[0][0] = fibw.a[1][0] = fibw.a[0][1] = 1; fibw.a[1][1] = 0;
	LL g = GtG(); LL w = Pow(g, (P - 1) / K);
	LL Now = Pow(Pow(w, K - 1), P - 2);
	LL Ans = Calc(Now);
	for (int i = K - 2; ~i; i--) {
		Now = (Now * w) % P; Add(Ans, Calc(Now));
	}
	Ans = Ans * Pow(K, P - 2) % P;
	cout << Ans << endl;
}
int main() {
	Read(T);
	while (T--) Solve();
	return 0;
}
