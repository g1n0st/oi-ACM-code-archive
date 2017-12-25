#include <bits/stdc++.h>
using namespace std;
const int V = 300010;
const int P = 19260817;
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
		x = x * 10 + c - '0';
		c = get();
	}
}
void $(int &x, int y) {
	(x += y) %= P;
}
int N, a[V], b[V];
struct bt {
	int a[V];
	int lowbit(int x) {
		return x & (-x);
	}
	void Add(int x, int v) {
		while (x <= N) {
			$(a[x], v);
			x += lowbit(x);
		}
	}
	int Query(int x) {
		int Ret = 0;
		while (x) {
			$(Ret, a[x]);
			x -= lowbit(x);
		}
		return Ret;
	}
	int Query(int l, int r) {
		int Ret = 0;
		$(Ret, Query(r));
		$(Ret, P - Query(l - 1));
		return Ret;
	}
} t[2];
vector<int> q;
int main() {
	int i, j;
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]); q.push_back(a[i]);
	}
	sort(q.begin(), q.end());
	q.erase(unique(q.begin(), q.end()), q.end());
	for (i = 1; i <= N; i++) 
		b[i] = lower_bound(q.begin(), q.end(), a[i]) - q.begin() + 1;
	for (i = 1; i <= N; i++) t[1].Add(b[i], a[i]);
	int Ans = 0;
	for (i = 1; i <= N; i++) {
		t[1].Add(b[i], P - a[i]);
		$(Ans, 1LL * a[i] * t[0].Query(1, b[i] - 1) % P * t[1].Query(b[i] + 1, N) % P);
		t[0].Add(b[i], a[i]);
	}
	printf("%d\n", Ans);
	return 0;
}
