#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

int n, m, K, a[N], b[N];
char s[10];
inline int Deco(char c) {
	if (c == '+') return 1;
	if (c == '-') return -1;
	return 0;
}
struct Wp {
	int v[10];
	Wp() {
		memset(v, 0, sizeof v);
	}
	friend Wp operator + (const Wp &a, const Wp &b) {
		Wp r;
		for (int i = 1; i <= K; i++) r.v[i] = a.v[i] + b.v[i];
		return r;
	}
	friend bool operator < (const Wp &a, const Wp &b) {
		for (int i = 1; i <= K; i++)
			if (a.v[i] != b.v[i]) return a.v[i] > b.v[i];
		return 0;
	}
	void print() {
		for (int i = 1; i <= K; i++) printf("%d ", v[i] + 1000);
	}
} wp[N];
namespace S1 {
	int IN(int s, int x) {
		return (s >> (x - 1)) & 1;
	}
	void main() {
		Wp ans;
		for (int i = 0; i < (1 << n); i++) {
			int flg = 1;
			for (int j = 1; j <= m; j++)
				if (IN(i, a[j]) && !IN(i, b[j])) {
					flg = 0; break;
				}
			if (!flg) continue;
			Wp cur;
			for (int j = 1; j <= n; j++)
				if (IN(i, j)) cur = cur + wp[j];
			if (cur < ans) ans = cur;
		}
		ans.print();
	}
}
namespace S2 {
	void main() {
		sort(wp + 1, wp + 1 + n);
		Wp ans;
		for (int i = 1; i <= n; i++) {
			Wp cur = ans + wp[i];
			if (cur < ans) ans = cur;
		}
		ans.print();
	}
}
int deg[N], dd[N], head[N], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[N];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
namespace S3 {
	Wp s[N]; int tot;
	void dfs(int u, Wp now) {
		s[++tot] = now;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; dfs(v, wp[v] + now);
		}
	}
	void main(int rt) {
		s[++tot] = Wp();
		dfs(rt, wp[rt]);
		sort(s + 1, s + 1 + tot);
		s[1].print();
	}
}
namespace S4 {
	Wp dfs(int u) {
		Wp cur = wp[u];
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; Wp nxt = dfs(v) + cur;
			if (nxt < cur) cur = nxt;
		}
		return cur;
	}
	void main(int rt) {
		Wp cur = dfs(rt), ze = Wp();
		if (ze < cur) cur = ze;
		cur.print();
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= K; j++) wp[i].v[j] = Deco(s[j]);
	}
	for (int i = 1; i <= m; i++) scanf("%d%d", &a[i], &b[i]);
	if (n <= 10) S1::main();
	else if (m == 0) S2::main();
	else if (m == n - 1) {
		for (int i = 1; i <= m; i++) {
			deg[a[i]]++; dd[b[i]]++; Add(b[i], a[i]);
		}
		int fl = 1, rt;
		for (int i = 1; i <= n; i++) {
			fl &= (dd[i] <= 1); if (!deg[i]) rt = i;
		}
		if (fl) S3::main(rt);
		else S4::main(rt);
	}
	return 0;
}
