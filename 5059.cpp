#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000100;
char get(void) {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, 100000, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
int n, tot, z[V], l[V], r[V], num[V], cnt[V], rt[V], Cnt;
struct Heap {
	int v, l, r, dep;
} h[V];
int makeHeap(int x) {
	++Cnt;
	h[Cnt].v = x, h[Cnt].l = h[Cnt].r = h[Cnt].dep = 0;
	return Cnt;
}
int Merge(int x, int y) {
	if (!x || !y) return x + y;
	if (h[x].v < h[y].v) swap(x, y);
	h[x].r = Merge(h[x].r, y);
	if (h[h[x].l].dep < h[h[x].r].dep) swap(h[x].l, h[x].r);
	h[x].dep = h[h[x].r].dep + 1;
	return x;
}
int Top(int x) {
	return h[x].v;
}
int Pop(int x) {
	return Merge(h[x].l, h[x].r);
}
int main(void) {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n);
	for (int i = 1; i <= n; i++) Read(z[i]);
	for (int i = 1; i <= n; i++) {
		++tot;
		rt[tot] = makeHeap(z[i]);
		l[tot] = r[tot] = i; cnt[tot] = num[tot] = 1;
		while (tot > 1 && Top(rt[tot]) < Top(rt[tot - 1])) {
			--tot;
			rt[tot] = Merge(rt[tot], rt[tot + 1]);
			r[tot] = r[tot + 1], cnt[tot] += cnt[tot + 1], num[tot] += num[tot + 1];
			for (; cnt[tot] * 2 > num[tot] + 1; --cnt[tot])
				rt[tot] = Pop(rt[tot]);
		}
	}
	LL ans = 0;
	for (int i = 1; i <= tot; i++) {
		int w = Top(rt[i]);
		for (int k = l[i]; k <= r[i]; k++) ans += abs(z[k] - w);
	}
	printf("%lld\n", ans);
	return 0;
}
