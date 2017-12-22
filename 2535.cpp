#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
void Read(int &x) {
	scanf("%d", &x);
}
struct Node {
	int w, id;
	Node(int w = 0, int id = 0) : w(w), id(id) {}
	friend bool operator < (const Node &a, const Node &b) {
		return a.w > b.w;
	}
};
int tmp[V], deg[V];
int head[V], sub;
struct Edge {
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[V];
void Add(int a, int b) {
	edge[++sub] = Edge(b, head[a]); head[a] = sub; tmp[b]++;
}
int N, M, c[V], a[V];
void Work1() {
	int i, j;
	priority_queue<Node> qu;
	memcpy(deg, tmp, sizeof tmp);
	for (i = 1; i <= N; i++)
		if (!deg[i]) qu.push(Node(c[i], i));
	int tot = 0;
	while (!qu.empty()) {
		int u = qu.top().id; qu.pop();
		a[++tot] = u;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to;
			if (!--deg[v]) qu.push(Node(c[v], v));
		}
	}
	reverse(a + 1, a + N + 1);
}
void Work2(int x) {
	int i, j;
	priority_queue<Node> qu;
	memcpy(deg, tmp, sizeof tmp);
	for (i = 1; i <= N; i++)
		if (!deg[i]) qu.push(Node(c[i], i));
	int p = 0;
	while (!qu.empty()) {
		int u = qu.top().id; qu.pop();
		if (u == x) continue;
		if (c[u] > p + 1) break;
		++p;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to;
			if (!--deg[v]) qu.push(Node(c[v], v));
		}
	}
	a[x] = N - p;
}
int main() {
	int i, j, u, v;
	Read(N); Read(M);
	for (i = 1; i <= N; i++) {
		Read(c[i]); c[i] = N - c[i] + 1;
	}
	for (i = 1; i <= M; i++) {
		Read(u); Read(v); Add(v, u);
	}
	Work1();
	for (i = 1; i <= N; i++) printf("%d%c", a[i], i == N ? '\n' : ' ');
	for (i = 1; i <= N; i++) Work2(i);
	for (i = 1; i <= N; i++) printf("%d%c", a[i], i == N ? '\n' : ' ');
	return 0;
}
