#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
typedef long long LL;
const int V = 200100;
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

int fa[V], v[V], mv[V], N, vis[V], cir[V], tot;
bool Chk(int x) {
	int i, j; tot = 1;
	for (i = x; !vis[fa[i]]; vis[i] = x, i = fa[i], ++tot);
	return (fa[i] == x);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	int i, j;
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(fa[i]); Read(v[i]);
	}
	if (Chk(1) && tot == N) {
		printf("0\n"); return 0;
	}
	memset(vis, 0, sizeof vis);
	for (i = 1; i <= N; i++) {
		if (!vis[i]) {
			for (j = i; j && !vis[j]; j = fa[j]) vis[j] = i;
			if (vis[j] == i)
				for (; !cir[j]; j = fa[j]) cir[j] = 1;
		}
		if (!cir[i]) mv[fa[i]] = max(mv[fa[i]], v[i]);
	}
	memset(vis, 0, sizeof vis);
	LL Ans = 0;
	for (i = 1; i <= N; i++) {
		if (cir[i]) {
			if (vis[i]) continue;
			LL Mn = 1LL << 60, tmp; int ct = 0;
			for (j = i; !vis[j]; vis[j] = 1, j = fa[j]) {
				tmp = v[j] - mv[fa[j]];
				Mn = min(Mn, tmp);
				Ans += (ct |= tmp < 0, tmp < 0) ? tmp : 0;
			}
			if (!ct) Ans += Mn;
		}
		else Ans += v[i] - mv[i];
	}
	printf("%lld\n", Ans);
	return 0;
}
