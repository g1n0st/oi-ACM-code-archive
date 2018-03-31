#include <bits/stdc++.h>
using namespace std;
void Read(int &x) {
	scanf("%d", &x);
}
const int N = 601, o = 300;

int n, a[N], b[N], vis[N][N];
void dfs(int x, int y) {
	if (x < 0 || y < 0 || x >= N || y >= N) return;
	if (vis[x][y]) return ;
	vis[x][y] = 1;
	for (int i = 1; i <= n; i++) {
		dfs(x + a[i], y + b[i]);
		dfs(x - a[i], y - b[i]);
	}
}
int sqr(int x) {
	return x * x;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) {
		Read(a[i]); Read(b[i]);
	}
	dfs(o, o);
	int mn = 1e9, X, Y, XX, YY;
	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++) {
			if (i == o && j == o) continue;
			if (!vis[i][j]) continue;
			if (sqr(i - o) + sqr(j - o) < mn) {
				mn = sqr(i - o) + sqr(j - o); X = i; Y = j;
			}
		}
	X -= o; Y -= o;
	mn = 1e9;
	for (int i = -o; i <= o; i++)
		for (int j = -o; j <= o; j++) 
			if (vis[i + o][j + o]) {
				int tmp = X * j - Y * i; tmp = abs(tmp);
				if (!tmp) continue;
				if (tmp < mn) {
					mn = tmp; XX = i, YY = j;
				}	
		}
	cout << X << ' ' << Y << endl << XX << ' ' << YY << endl;
	return 0;
}
