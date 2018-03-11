#include <bits/stdc++.h>
using namespace std;

const int N = 25;
const int V = 1 << 8 | 1;

struct PI {
	int x, y;
	PI(int x = 0, int y = 0) : x(x), y(y) {}
};
typedef pair<PI, PI> PPI;

const int sx[] = { 0, 1, 0, -1 };
const int sy[] = { 1, 0, -1, 0 };

PI bomb[N], reward[N], ori;
char mp[N][N];
int n, m, f[N][N][V][V], R, B, val[N], sum[V];

bool cov(int x1, int x2, int x) {
	return (x1 == x - 1) && (x2 == x);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> n >> m;
	bomb[1].x = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cin >> mp[i][j];
			if (isdigit(mp[i][j])) {
				reward[mp[i][j] - '0'] = PI(i, j); ++R;
			} else if (mp[i][j] == 'S') ori = PI(i, j);
			else if (mp[i][j] == 'B') bomb[++B] = PI(i, j);
		}

	for (int i = 1; i <= R; i++) cin >> val[i];
	for (int i = 1; i < (1 << R); i++)
		for (int j = 1; j <= R; j++)
			if ((i >> (j - 1)) & 1) sum[i] += val[j];

	memset(f, 0x3f, sizeof f); f[ori.x][ori.y][0][0] = 0;
	queue<PPI> qu; qu.push(PPI(ori, PI(0, 0)));
	while (!qu.empty()) {
		int lx = qu.front().first.x, ly = qu.front().first.y,
			lr = qu.front().second.x, lb = qu.front().second.y; qu.pop();
		for (int k = 0; k < 4; k++) {
			int nx = lx + sx[k], ny = ly + sy[k], nr = lr, nb = lb;
			if (mp[nx][ny] != '.' && mp[nx][ny] != 'S') continue;
			for (int i = 1; i <= R; i++) {
				if (ny <= reward[i].y) continue;
				if (cov(lx, nx, reward[i].x)) nr ^= (1 << (i - 1));
				if (cov(nx, lx, reward[i].x)) nr ^= (1 << (i - 1));
			}
			for (int i = 1; i <= B; i++) {
				if (ny <= bomb[i].y) continue;
				if (cov(lx, nx, bomb[i].x)) nb ^= (1 << (i - 1));
				if (cov(nx, lx, bomb[i].x)) nb ^= (1 << (i - 1));
			}
			if (f[nx][ny][nr][nb] > f[lx][ly][lr][lb] + 1) {
				f[nx][ny][nr][nb] = f[lx][ly][lr][lb] + 1; qu.push(PPI(PI(nx, ny), PI(nr, nb)));
			}
		}
	}
	int ans = 0;
	for (int i = 1; i < (1 << R); i++) ans = max(ans, sum[i] - f[ori.x][ori.y][i][0]);

	cout << ans << endl;
	return 0;
}
