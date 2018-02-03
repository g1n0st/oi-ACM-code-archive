#include <bits/stdc++.h>
typedef long long LL;
const int V = 10000005;
using namespace std;
LL Ksc(LL x, LL y, LL p) {
	LL r = 0;
	while (y) {
		if (y & 1) r = (r + x) % p;
		y >>= 1; if (y) x = (x + x) % p;
	}
	return r;
}
LL Ksm(LL x, LL y, LL p) {
	LL r = 1;
	while (y) {
		if (y & 1) r = Ksc(r, x, p);
		y >>= 1; if (y) x = Ksc(x, x, p);
	}
	return r;
}
int vis[V], tot; LL p[V];
void Pre(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) p[++tot] = i;
		for (int j = 1; j <= tot && p[j] * i <= n; j++) {
			vis[i * p[j]] = 1; if (!(i % p[j])) break;
		}
	}
}
namespace Miller_Rabin {
	const int M_TIME = 10;
	bool witness(LL a, LL x) {
		LL j = 0, t = x - 1;
		while (!(t & 1LL)) t >>= 1, j++;
		LL tmp = Ksm(a, t, x), lst = tmp;
		while (j--) {
			tmp = Ksc(tmp, tmp, x);
			if (tmp == 1LL && lst != 1LL && lst != x - 1) return 0;
			lst = tmp;
		}
		return tmp == 1LL;
	}
	bool MRtest(LL x) {
		if (x == 2) return 1;
		if (x <= 1LL || !(x & 1LL)) return 0;
		for (int i = 0; i < M_TIME; i++)
			if (!witness(rand() % (x - 1) + 1, x)) return 0;
		return 1;
	}
}
using Miller_Rabin::MRtest;
vector<LL> Ans;
void Solve(LL fi, LL n, int lst) {
	if (fi + 1 > p[tot] && MRtest(fi + 1)) Ans.push_back(n * (fi + 1));
	for (int i = lst; i; i--)
		if (fi % (p[i] - 1) == 0) {
			LL t1 = fi / (p[i] - 1), t2 = n, t3 = 1LL;
			while (t1 % t3 == 0) {
				t2 *= p[i];
				Solve(t1 / t3, t2, i - 1);
				t3 *= p[i];
			}
		}
	if (fi == 1LL) {
		Ans.push_back(n);
		return;
	}
}
LL fi; int K;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Pre(V);
	cin >> fi >> K;
	Solve(fi, 1LL, tot);
	sort(Ans.begin(), Ans.end());
	for (int i = 0; i < K; i++)
		printf("%lld%c", Ans[i], i == (K - 1) ? '\n' : ' ');
	return 0;
}
