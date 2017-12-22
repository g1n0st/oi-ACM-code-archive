#include <bits/stdc++.h>
using namespace std;
const int V = 5010;
void Read(int &x) {
	scanf("%d", &x);
}
struct Node {
	int w, id;
	Node(int w = 0, int id = 0) : w(w), id(id) {}
	friend bool operator < (const Node &a, const Node &b) {
		if (a.w ^ b.w) return a.w < b.w;
		else return a.id < b.id;
	}
} v[V];
int N, M, a[V];
char g[V][V];
int main() {
	int i, j, tot = 0, minv = 1 << 30;
	Read(M); Read(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]); v[i] = Node(a[i], i); 
		tot += a[i]; minv = min(minv, a[i]);
	}
	if (tot > M * (M - 1)) {
		printf("no\n");
		return 0;
	}
	tot = M * (M - 1) - tot;
	if (M - N) {
		int p = tot - tot / (M - N) * (M - N);
		for (i = N + 1; i <= M; i++)
			if (p) v[i] = Node(tot / (M - N) + 1, i), p--;
			else v[i] = Node(tot / (M - N), i);
		if (v[N + 1].w > minv) {
			printf("no\n");
			return 0;
		}
	}
	sort(v + 1, v + 1 + M);
	tot = 0;
	for (i = 1; i <= M; i++) {
		tot += v[i].w;
		if (tot < i * (i - 1)) {
			printf("no\n");
			return 0;
		}
	}
	for (i = 1; i <= M; i++) g[i][i] = 'X';
	for (i = M; i; i--) {
		sort(v + 1, v + i + 1);
		tot = v[i].w;
		for (j = 1; j < i; j++) {
			if (tot > 1) {
				tot -= 2;
				g[v[i].id][v[j].id] = 'W'; g[v[j].id][v[i].id] = 'L';
			}
			else if (tot) {
				tot--; v[j].w--;
				g[v[i].id][v[j].id] = 'D'; g[v[j].id][v[i].id] = 'D';
			}
			else {
				v[j].w -= 2;
				g[v[i].id][v[j].id] = 'L'; g[v[j].id][v[i].id] = 'W';
			}
		}
	}
	printf("yes\n");
	for (i = 1; i <= M; i++)
		printf("%s\n", g[i] + 1);
	return 0;
}
