#include <bits/stdc++.h>
using namespace std;
const int V = 1000010;
typedef pair<int, int>pl;
int Max(int a, int b) {
	return a > b ? a : b;
}
int Min(int a, int b) {
	return a < b ? a : b;
}
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0;
	static char c;
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = get();
	}
}
int N, M, T, a[V], b[V];
int v[V], pos[V], tot;
int vis[100], p[100], pp[100], mx;
vector<int> G[V];
pl a1[V], a2[V][2];
void Dfs(int x) {
	if (x == tot + 1) {
		int now = 0;
		for (int i = 1; i <= tot; i++)
			if (v[i] != v[p[i]]) now++;
		if (now >= mx) {
			mx = now;
			for (int i = 1; i <= tot; i++) pp[i] = p[i];
		}
		return ;
	}
	for (int i = 1; i <= tot; i++)
		if (!vis[i]) {
			vis[i] = 1;
			p[x] = i;
			Dfs(x + 1);
			vis[i] = 0;
		}
}
void Solve() {
	int i, j;
	for (i = 1; i <= M; i++) G[i].clear();
	mx = M = tot = 0;
 
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]);
		G[a[i]].push_back(i);
		M = Max(M, a[i]);
	}
	int n1 = 0, n2 = 0;
	for (i = 1; i <= M; i++) {
		if (G[i].size() == 1) {
			n1++;
			a1[n1] = pl(i, G[i][0]);
		}
		if (G[i].size() == 2) {
			n2++;
			a2[n2][0] = pl(i, G[i][0]);
			a2[n2][1] = pl(i, G[i][1]);
		}
	}
	int p1 = Min(3, n1), p2 = Min(2, n2);
	if (n1 - p1 == 1) p1--;
	if (n2 - p2 == 1) p2++;
	//p1 = p2 = 0;
	for (i = 1, j = n1; i <= p1; i++, j--) ++tot, v[tot] = a1[j].first, pos[tot] = a1[j].second;
	for (i = 1, j = n2; i <= p2; i++, j--) {
		++tot, v[tot] = a2[j][0].first, pos[tot] = a2[j][0].second;
		++tot, v[tot] = a2[j][1].first, pos[tot] = a2[j][1].second;
	}
 
	n1 -= p1;
	n2 -= p2;
	for (i = 1; i <= n1; i++) {
		j = (i + 1);
		if (i == n1) j = 1;
		b[a1[j].second] = a1[i].first;
	}
	for (i = 1; i <= n2; i++) {
		j = (i + 1);
		if (i == n2) j = 1;
		b[a2[j][0].second] = a2[i][0].first;
		b[a2[j][1].second] = a2[i][1].first;
	}
	Dfs(1);
	for (i = 1; i <= tot; i++) b[pos[i]] = v[pp[i]];
	if (N == 1) printf("0\n");
	else printf("%d\n", n1 + n2 * 2 + mx);
	for (i = 1; i <= N; i++) printf("%d%c", b[i], i == N ? '\n' : ' ');
}
int main(void) {
	int i, j;
	//freopen("in.txt", "r", stdin);
	Read(T);
	while (T--) Solve();
	return 0;
}
