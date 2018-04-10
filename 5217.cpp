#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PI;
const int INF = 1 << 30;
const double pi = acos(-1);
const int V = 1500000;

struct E {
	double x, y;
	E(double x = 0, double y = 0) : x(x), y(y) {}
	friend E operator + (const E &a, const E &b) {
		return E(a.x + b.x, a.y + b.y);
	}
	friend E operator - (const E &a, const E &b) {
		return E(a.x - b.x, a.y - b.y);
	}
	friend E operator * (const E &a, const E &b) {
		return E(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
	}
	void operator /= (double f) {
		x /= f; y /= f;
	}
};
namespace FFT {
	int L, n, R[V];
	void init(int m) {
		for (n = 1; n <= m; n <<= 1, L++);
		for (int i = 0; i < n; i++)
			R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	}
	void fft(E *a, int f) {
		for (int i = 0; i < n; i++)
			if (i < R[i]) swap(a[i], a[R[i]]);
		for (int i = 1; i < n; i <<= 1) {
			E wn(cos(pi / i), f * sin(pi / i));
			for (int j = 0; j < n; j += (i << 1)) {
				E w(1, 0);
				for (int k = 0; k < i; k++, w = w * wn) {
					E x = a[j + k], y = w * a[i + j + k];
					a[j + k] = x + y; a[i + j + k] = x - y;
				}
			}
		}
		if (f == -1) for (int i = 0; i < n; i++) a[i] /= n;
	}
}

const int N = 710;
char M[N][N];
int n, m, vis[N][N];
E a[V], b[V];
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { 1, -1, 0, 0 };
void bfs(int x, int y) {
	queue<PI> q;
	q.push(PI(x, y));
	vis[x][y] = 0;
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop();
		a[(x - 1) * m + y - 1] = E(1);
		for (int i = 0; i < 4; i++) {
			int xx = x + dx[i], yy = y + dy[i];
			if (vis[xx][yy]) {
				vis[xx][yy] = 0;
				q.push(PI(xx, yy));
			}
		}
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", M[i] + 1);
	int x1 = INF, y1 = INF, x2 = 0, y2 = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (M[i][j] == 'o') {
				x1 = min(x1, i); y1 = min(y1, j);
				x2 = max(x2, i); y2 = max(y2, j);
			}
			else if (M[i][j] == '#') {
				a[n * m - (i - 1) * m - j] = E(1);
			}
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (M[i][j] == 'o') b[(i - x1) * m + j - y1] = E(1);
	FFT::init(2 * n * m);
	FFT::fft(a, 1); FFT::fft(b, 1);
	for (int i = 0; i < FFT::n; i++) a[i] = a[i] * b[i];
	FFT::fft(a, -1);
	for (int i = 1; i <= n - (x2 - x1); i++) {
		for (int j = 1; j <= m - (y2 - y1); j++) {
			if ((int)(a[n * m - (i - 1) * m - j].x + 0.1) == 0) vis[i][j] = 1;
		}
	}
	for (int i = 0; i < FFT::n; i++) a[i] = E();
	bfs(x1, y1);
	FFT::fft(a, 1);
	for (int i = 0; i < FFT::n; i++) a[i] = a[i] * b[i];
	FFT::fft(a, -1);
	int ans = 0;
	for (int i = 0; i < n * m; i++) 
		if ((int)(a[i].x + 0.1) > 0) ans++;

	cout << ans << endl;
	return 0;
}
