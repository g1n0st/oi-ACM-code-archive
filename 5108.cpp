#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
struct Node {
	int p, v;
	friend bool operator < (const Node &a, const Node &b) {
		return a.p < b.p;
	}
} v[V];
LL f[V][2];
int n, m;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m);
	for (int i = 1; i <= m; i++) {
		Read(v[i].p); Read(v[i].v);
	}
	sort(v + 1, v + 1 + m);
	for (int i = 0; i <= 30; i++) f[i][1] = 1LL << 60;
	for (int i = 1; i <= m; i++) {
		int x = v[i].p - v[i - 1].p - 1, val = v[i].v;
		if (x)
			for (int j = 0; j <= 30; j++) {
				LL pre = min(f[j][0], f[j][1]);
				f[j][0] = pre; f[j][1] = pre + 1;
			}
		for (int j = 0; j <= 30; j++) {
			LL f0 = f[j][0], f1 = f[j][1];
			if ((val >> j) & 1) {
				f[j][0] = f1; f[j][1] = f0 + 1;
			}
			else {
				f[j][0] = f0; f[j][1] = f1 + 1;
			}
		}
	}
	LL ans = 0;
	for (int i = 0; i <= 30; i++)
		ans += min(f[i][0], f[i][1]) << i;
	cout << ans << endl;
	return 0;
}
