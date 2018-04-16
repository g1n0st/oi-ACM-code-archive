#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long LL;

const int V = 500010;

char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T> void Read(T &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}

int n, fa[V], siz[V], val[V << 2];

int head[V], sub, deg[V];
struct Edge {
	int to, nxt;
	Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub; deg[b]++;
}

int f[V];
inline int getf(int x) {
	return x == f[x] ? x : f[x] = getf(f[x]);
}

LL sum, w[V];

struct Node {
	int id; LL siz, w;
	Node() {}
	Node(int id, LL w, LL siz) : id(id), w(w), siz(siz) {}
};

struct cmp {
	inline bool operator () (const Node &l, const Node &r) {
		return l.w * r.siz > r.w * l.siz;
	}
};
typedef __gnu_pbds::priority_queue<Node, cmp, pairing_heap_tag> heap;

heap Q;
heap::point_iterator p[V];

bool judge() {
	queue<int> q; q.push(0);
	int tot = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop(); ++tot;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (!--deg[v]) q.push(v);
		}
	}
	return tot == n + 1;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	Read(n);
	for (int i = 1; i <= n; i++) {
		Read(fa[i]); Add(fa[i], i);
	}

	if (!judge()) {
		puts("-1"); return 0;
	}

	for (int i = 0; i <= n; i++) {
		f[i] = i; siz[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		Read(w[i]); sum += w[i]; p[i] = Q.push(Node(i, w[i], siz[i]));
	}

	LL ans = 0;
	for (int i = 1; i <= n; i++) {
		int x = Q.top().id, y = getf(fa[x]); Q.pop();
		
		ans += (LL)w[x] * siz[y];

		siz[y] += siz[x]; f[x] = y; w[y] += w[x];

		if (y) Q.modify(p[y], Node(y, w[y], siz[y]));

	}

	cout << ans << endl;

	return 0;
}
