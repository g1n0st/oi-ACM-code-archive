#include <bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

using namespace __gnu_pbds;
using namespace std;


const int INF = 0x3f3f3f3f;
const int V = 262145;
const int M = 7000010;

typedef pair<int, int> PI;
typedef __gnu_pbds::priority_queue<PI, greater<PI>, pairing_heap_tag > heap;
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

heap::point_iterator id[V];
int head[V], sub;
int dis[V];
struct Edge {
	int to, nxt, v;
	Edge(void) {}
	Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
} edge[M];
inline void Add(int a, int b, int v) {
	edge[++sub] = Edge(b, head[a], v), head[a] = sub;
}

int n, m, C, K, S, T;
inline int dj(int S, int T) {
	for (int i = 0; i <= n; i++) dis[i] = INF;
	heap qu;
	dis[S] = 0; id[S] = qu.push(PI(0, S));
	while (!qu.empty()) {
		int x = qu.top().second; qu.pop();
		for (int i = head[x], v; i; i = edge[i].nxt) {
			v = edge[i].to;
			if (dis[v] > dis[x] + edge[i].v) {
				dis[v] = dis[x] + edge[i].v;
				if (id[v] != 0) qu.modify(id[v], PI(dis[v], v));
				else id[v] = qu.push(PI(dis[v], v));
			}
		}
	}
	return dis[T];
}

int main() {

	Read(n); Read(m); Read(C);
	for (K = 1; K <= n; K <<= 1);

	int u, v, w;
	for (int i = 1; i <= m; i++) {
		Read(u); Read(v); Read(w); Add(u, v, w);
	}
	for (int i = 1; i <= n; i++)
		for (int k = 1; k <= K; k <<= 1)
			Add(i, i ^ k, C * k), Add(i ^ k, i, C * k);

	Read(S); Read(T);
	cout << dj(S, T) << endl;
	return 0;
}
