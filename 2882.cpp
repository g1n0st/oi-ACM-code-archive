#include <bits/stdc++.h>
using namespace std;
const int V = 1200100;
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
		x = x * 10 + c - '0'; c = get();
	}
}
namespace SAM {
	struct Node {
		int fa, len;
		map<int, int> c;
	} v[V];
	int tot, lst, rt;
	void Init() {
		rt = lst = ++tot;
	}
	void Extend(int x) {
		int cur;
		v[cur = ++tot].len = v[lst].len + 1;
		int p, q;
		for (p = lst; p && !v[p].c.count(x); p = v[p].fa) v[p].c[x] = cur;
		if (!p) v[cur].fa = 1;
		else {
			q = v[p].c[x];
			if (v[p].len + 1 == v[q].len) v[cur].fa = q;
			else {
				v[++tot].len = v[p].len + 1; v[tot].fa = v[q].fa;
				v[tot].c = v[q].c;
				for (; p && v[p].c[x] == q; p = v[p].fa) v[p].c[x] = tot;
				v[q].fa = v[cur].fa = tot;
			}
		}
		lst = cur;
	}
}
int N, a[V];
int main() {
	int i, j;
	Read(N); SAM::Init();
	for (i = 1; i <= N; i++) Read(a[i]);
	for (i = 1; i <= N; i++) SAM::Extend(a[i]);
	for (i = 1; i <= N; i++) SAM::Extend(a[i]);
	int p = SAM::rt;
	for (i = 1; i <= N; i++) {
		pair<int, int> x = *SAM::v[p].c.begin();
		if (i == N) {
			printf("%d\n", x.first); break;
		} else {
			printf("%d ", x.first); p = x.second;
		}
	}
	return 0;
}
