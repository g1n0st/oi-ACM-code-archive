#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 1000000007;
const int V = 1000010;
int X, A, B, C, mx, p[V], bg, len;
int f[V], g[V];
void Pre(int f[]) {
	LL L, R; scanf("%lld%lld\n", &L, &R);
	for (int i = 1; i <= mx; i++) {
		f[i] = f[i - 1];
		if (p[i] < bg) (f[i] += (p[i] >= L && p[i] <= R)) %= P;
		else {
			if (R >= p[i]) f[i] = (f[i] + ((R - p[i]) / len + 1) % P) % P;
			if (L > p[i]) f[i] = (f[i] + P - ((L - p[i] - 1) / len + 1) % P) % P;
		}
	}
}
int ans;
void Solve() {
	static double det[V];
	for (int i = 3; i <= mx + 1; i++)
		det[i] = (i + sqrt((LL)i * i - 4)) / 2.0;
	for (int i = 1; i <= mx; i++) {
		int fl = (f[i] - f[i - 1] + P) % P, fr = (g[i] - g[i - 1] + P) % P;
		if (!fl && !fr) continue;
		ans = (ans + (LL)fl * fr * 2 % P) % P;
		for (int L = i + 1, R, k; L <= mx; L = R + 1) {
			k = ((LL)i * i + (LL)L * L - 1) / ((LL)i * L) + 1;
			R = min(mx, (int)ceil(i * det[k]));
			while (R < mx && ((LL)i * i + (LL)R * R - 1) / ((LL)i * R) + 1 <= k) R++;
			while (((LL)i * i + (LL)R * R - 1) / ((LL)i * R) + 1 > k) R--;
			ans = (ans + ((((LL)f[R] - f[L - 1] + P) * fr + ((LL)g[R] - g[L - 1] + P) * fl) % P * k % P)) % P;
		}
	}
	cout << ans << endl;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d%d%d%d", &A, &B, &C, &X);
	for (int i = 1; ; i++) {
		mx = max(mx, X = ((LL)A * X + B) % C + 1);
		if (p[X]) {
			bg = p[X]; len = i - bg; break;
		} p[X] = i;
	}
	Pre(f); Pre(g);
	Solve();
	return 0;
}
