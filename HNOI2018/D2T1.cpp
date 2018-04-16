#include <bits/stdc++.h>
using namespace std;

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

queue<int> q;
vector<int> G[V];

int n, m, Q, tot, s[V], t;
int L[V], R[V];
int bel[V], a[V], deg[V];
inline void Add(int x, int y) {
	G[x].emplace_back(y); deg[y]++;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(n); Read(m); Read(Q);
	int x, y;
	for (int i = 1; i <= m; i++) {
		Read(x); Read(y); a[x] = y;
	}
	bel[1] = L[1] = R[1] = tot = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i - 1]) {
			++tot; L[tot] = i;
			if (a[i - 1] >= i) Add(tot - 1, tot);
			else Add(tot, tot - 1);
		}
		R[bel[i] = tot] = i;
	}

	for (int i = 1; i <= tot; i++) if (!deg[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front(); s[++t] = u; q.pop();
		for (auto v : G[u]) {
			if (!--deg[v]) q.push(v);
		}
	}

	for (int i = 1; i <= tot; i++) {
		int u = s[i];
		while (1) {
			while (u < tot && a[R[u]] >= L[u] && a[R[u]] <= R[u]) R[u] = R[bel[R[u] + 1]];
			while (u > 1 && a[L[u] - 1] >= L[u] && a[L[u] - 1] <= R[u]) L[u] = L[bel[L[u] - 1]];
			if ((u == tot || a[R[u]] < L[u] || a[R[u]] > R[u]) &&
				(u == 1 || a[L[u] - 1] < L[u] || a[L[u] - 1] > R[u])) break;
		}
	}
	while (Q--) {
		Read(x); Read(y);
		if (y >= L[bel[x]] && y <= R[bel[x]])
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
