#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

void Read(int &x) {
	scanf("%d", &x);
}

const int N = 20;
const int INF = 1 << 30;

map<LL, int> M;
LL ED;
int n, m, A[N][N], B[N][N], pos[N];

LL cal() {
	LL r = 0;
	for (int i = 1; i <= n; i++) r = r * (m + 1) + pos[i];
	return r;
}
int dfs(LL now, int p) {
	if (M.find(now) != M.end()) return M[now];
	if (now == ED) return 0;
	LL nxt;
	int val = p ? INF : -INF;
	for (int i = 1; i <= n; i++) 
		if (pos[i - 1] > pos[i]) {
			pos[i]++;
			nxt = cal();
			if (p) val = min(val, dfs(nxt, p ^ 1) - B[i][pos[i]]);
			else   val = max(val, dfs(nxt, p ^ 1) + A[i][pos[i]]);
			pos[i]--;
	}
	return M[now] = val;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			Read(A[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			Read(B[i][j]);

	pos[0] = m;
	for (int i = 1; i <= n; i++) ED = ED * (m + 1) + m;
	
	cout << dfs(0, 0) << endl;
	return 0;
}
