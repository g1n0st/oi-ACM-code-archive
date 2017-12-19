#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const int V = 1000010;
typedef long long LL;
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
	while (c > '9' || c < '0') c = get();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0'; c = get();
	}
}
LL Rd() {
	return (1LL * rand()) << 32 | rand();
}
LL v[V], mrk[V], Ans, cnt[V];
int bel[V], l[V], r[V], a[V], lst[V], pre[V], N, B;
void Solve(int l, int r) {
	static int i, j;
	for (i = l; i <= r; i++) {
		for (j = l; j <= pre[i]; j++)
			mrk[j] ^= v[a[i]];
		for (j = l; j <= i; j++) Ans += (!mrk[j]);
	}
	vector<int> g; g.emplace_back(0); g.emplace_back (l - 1);
	for (i = l; i <= r; i++) g.emplace_back(pre[i]);
	sort(g.begin(), g.end());
	g.erase(unique(g.begin(), g.end()), g.end());
	for (i = 1; i < g.size() && g[i] < l; i++) {
		int x = g[i - 1] + 1, y = g[i];
		LL s = 0;
		for (j = l; j <= r; j++) {
			if (pre[j] >= y) s ^= v[a[j]];
			cnt[j - l] = s;
		}
		sort(cnt, cnt + r - l + 1);
		for (j = x; j <= y; j++) {
			Ans += upper_bound(cnt, cnt + r - l + 1, mrk[j]) - cnt;
			Ans -= lower_bound(cnt, cnt + r - l + 1, mrk[j]) - cnt;
			mrk[j] ^= s;
		}
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j; Read(N); B = sqrt(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]); if (!v[a[i]]) v[a[i]] = Rd();
		bel[i] = (i - 1) / B + 1;
		if (!l[bel[i]]) l[bel[i]] = i; r[bel[i]] = i;
		pre[i] = lst[a[i]]; lst[a[i]] = i;
	}
	B = bel[N];
	for (i = 1; i <= B; i++) Solve(l[i], r[i]);
	printf("%lld\n", Ans);
	return 0;
}
