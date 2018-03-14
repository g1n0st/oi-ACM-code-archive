#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 998244353;
void Read(int &x) {
	scanf("%d", &x);
}
const int V = 1000010;
int n, K, ans;
template<int R> struct Mat {
	int a[R][R];
	Mat() {
		memset(a, 0, sizeof a);
	}
	friend Mat operator + (const Mat a, const Mat b) {
		Mat r;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < R; j++)
				r.a[i][j] = (a.a[i][j] + b.a[i][j]) % P;
		return r;
	}
	friend Mat operator * (const Mat a, const Mat b) {
		Mat r;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < R; j++)
				for (int k = 0; k < R; k++)
					r.a[i][j] = (r.a[i][j] + (LL)a.a[i][k] * b.a[k][j] % P) % P;
		return r;
	}
};
template<const int R> Mat<R> Ksm(Mat<R> x, int y) {
	Mat<R> r = x; y--;
	while (y) {
		if (y & 1) r = r * x;
		y >>= 1; if (y) x = x * x;
	}
	return r;
}
typedef Mat<2> M2;
typedef Mat<8> M8;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(K);
	if (n & 1) {
		/*
		f[1][0] = 1;
		for (int i = 2; i <= n; i++) {
			f[i][0] = f[i - 1][1];
			f[i][1] = (LL)f[i - 1][0] * (K - 1) % P;
			f[i][1] = (f[i][1] + (LL)f[i - 1][1] * (K - 2) % P) % P;
		}
		cout << (LL)f[n][1] * K % P << endl; */
		M2 a; a.a[1][0] = 1; a.a[0][0] = 0; a.a[0][1] = K - 1; a.a[1][1] = K - 2;
		a = Ksm(a, n - 1);
		ans = (LL)a.a[0][1] * K % P;
	}
	else {
		M8 det, ans;
		int a00 = (K - 3 + (LL)(K - 4) * (K - 4)) % P,
			k23 = (LL)(K - 2) * (K - 3) % P, k33 = (LL)(K - 3) * (K - 3) % P;
		int m[8][8] = {
			{a00, 1, 1, K - 3, K - 3, K - 3, K - 3, 0}, 
			{k23, 0, 1, K - 2, 0, 0, K - 2, 0},
			{k23, 1, 0, 0, K - 2, K - 2, 0, 0},
			{k33, 1, 0, 0, K - 2, K - 3, K - 2, 0},
			{k33, 0, 1, K - 2, 0, K - 2, K - 3, 0},
			{k33, 0, 1, K - 3, K - 2, 0, K - 2, 0},
			{k33, 1, 0, K - 2, K - 3, K - 2, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0}
		};
		ans.a[0][1] = (LL)K * (K - 1) % P;

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) det.a[i][j] = m[i][j];
		ans = ans * Ksm(det, n / 2);
		::ans = ans.a[0][2];
	}
	cout << ans << endl;
	return 0;
}
