#include <bits/stdc++.h>
typedef long long LL;
const int P = 1000000007;
using namespace std;
void Read(int &x) {
	scanf("%d", &x);
}
const int N = 410;
int n, Q, a[N], id[N], rk[N];
bool cmp(int x, int y) {
	return a[x] < a[y];
}
int cnt[N], tc[N][N];
LL f[2][N][N], sum[N][N];
void Work(int L, int R, int x) {
	for (int i = L; i <= R; i++)
		for (int j = L; j <= R; j++)
			f[0][i][j] = f[1][i][j] = 0;
	f[0][L][R] = 1; int cur = 0, pre = 1;
	LL now;
	for (int k = 1; k <= Q; k++) {
		cur ^= 1; pre ^= 1;
		for (int i = L; i <= R; i++) {
			now = 0;
			for (int j = R; j >= i; j--) {
				f[cur][i][j] = now; 
				now = (now + f[pre][i][j] * (n - j)) % P;
			}
		}
		for (int j = L; j <= R; j++) {
			now = 0;
			for (int i = L; i <= j; i++) {
				f[cur][i][j] = (f[cur][i][j] + now) % P;
				now = (now + f[pre][i][j] * (i - 1));
			}
		}
		for (int i = L; i <= R; i++)
			for (int j = i; j <= R; j++)
				f[cur][i][j] = (f[cur][i][j] + f[pre][i][j] * tc[i][j]) % P;
	}
	for (int i = L; i <= R; i++) {
		now = 0;
		for (int j = R; j >= i; j--) {
			now += f[cur][i][j];
			sum[j][rk[x]] = (now + sum[j][rk[x]]) % P;
		}
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(Q);
	for (int i = 1; i <= n; i++) Read(a[i]);
	for (int i = 1; i <= n; i++) id[i] = i;
	sort(id + 1, id + 1 + n, cmp);
	for (int i = 1; i <= n; i++) rk[id[i]] = i;
	for (int i = 1; i <= n; i++) cnt[i] = i * (i + 1) / 2;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			tc[i][j] = cnt[j - i + 1] + cnt[n - j] + cnt[i - 1];
	for (int i = 1; i <= n; i++) {
		int L = i, R = i;
		while (L && a[i] >= a[L]) L--;
		while (R <= n && a[i] >= a[R]) R++;
		Work(L + 1, R - 1, i);
	}
	for (int i = 1; i <= n; i++) {
		int ans(0);
		for (int j = 1; j <= n; j++) {
			if (!sum[i][j]) continue;
			for (int k = 1; k < j; k++) sum[i][j] = (sum[i][j] + P - sum[i][k]) % P;
			ans = (ans + (LL)a[id[j]] * sum[i][j] % P) % P;
		}
		printf("%d%c", ans, i == n ? '\n' : ' ');
	}
	return 0;
}
