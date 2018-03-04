#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 300010;
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
int n, a[V];
int s[V], t, pre[V], suf[V];
int L1[V], L2[V], R1[V], R2[V];
int find1(int x) {
	int l = 1, r = t, mid, ans = 0;
	while (l <= r) {
		mid = (l + r) >> 1; if (a[s[mid]] >= x) r = (ans = mid) - 1;
		else l = mid + 1;
	}
	return ans;
}
int find2(int x) {
	int l = 1, r = t, mid, ans = 0;
	while (l <= r) {
		mid = (l + r) >> 1; if (a[s[mid]] <= x) r = (ans = mid) - 1;
		else l = mid + 1;
	}
	return ans;
}
namespace ST {
	int a[V];
	void add(int x) {
		for (; x <= n; x += x & -x) a[x]++;
	}
	int query(int x) {
		int r = 0;
		for (; x; x -= x & -x) r += a[x];
		return r;
	}
}
namespace SGT {
	int mx[V << 2], tag[V << 2];
	void pushDown(int o) {
		if (tag[o]) {
			tag[o << 1] += tag[o]; tag[o << 1 | 1] += tag[o];
			mx[o << 1] += tag[o]; mx[o << 1 | 1] += tag[o]; tag[o] = 0;
		}
	}
	void pushUp(int o) {
		mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
	}
	void Modify(int o, int l, int r, int L, int R, int v) {
		if (L > R) return;
		if (l >= L && r <= R) {
			mx[o] += v; tag[o] += v; return;
		}
		int mid = (l + r) >> 1; pushDown(o);
		if (L <= mid) Modify(o << 1, l, mid, L, R, v);
		if (mid < R) Modify(o << 1 | 1, mid + 1, r, L, R, v);
		pushUp(o);
	}
}
LL ans;
struct Node {
	int l, r, v;
	Node(int l = 0, int r = 0, int v = 0) : l(l), r(r), v(v) {}	
};
vector<Node> G[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) Read(a[i]);
	for (int i = n; i; i--) {
		ans += ST::query(a[i]); ST::add(a[i]);
	}
	for (int i = 1; i <= n; i++) {
		pre[i] = max(pre[i - 1], a[i]); if (pre[i] == a[i]) s[++t] = i;
	}
	int t1 = 0;
	for (int i = 1; i <= n; i++) {
		L1[i] = s[find1(a[i])]; L2[i] = i - 1;
	}
	t = 0; suf[n + 1] = 1 << 30;
	for (int i = n; i; i--) {
		suf[i] = min(suf[i + 1], a[i]); if (suf[i] == a[i]) s[++t] = i;
	}
	t1 = 0;
	for (int i = n; i; i--) {
		R1[i] = i + 1; R2[i] = s[find2(a[i])];
	}
	int tot = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int tmp = 0;
			for (int k = 1; k <= n; k++)
				if (i >= L1[k] && i <= L2[k] && j >= R1[k] && j <= R2[k]) tmp++;
			tot = max(tot, tmp);
		}
	int mX = 0;
	for (int i = 1; i <= n; i++) {
		if (R1[i] > R2[i]) continue;
		G[R1[i]].emplace_back(Node(L1[i], L2[i], 1));
		G[R2[i] + 1].emplace_back(Node(L1[i], L2[i], -1));
	}
	for (int i = 1; i <= n; i++) {
		for (auto e : G[i]) SGT::Modify(1, 1, n, e.l, e.r, e.v);
		mX = max(mX, SGT::mx[1]);
	}
	cout << ans - 2 * mX << endl;
	return 0;
}
