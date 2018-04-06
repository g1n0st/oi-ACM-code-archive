#include <bits/stdc++.h>
using namespace std;

const int N = 2110;

int cnt, pcnt, n;
int ls[N], rs[N], ps[N];
int del[N], lc[N], rc[N];

void NewNode(int u) {
	int a = ++cnt, b = ++pcnt;
	if (ps[u]) {
		if (ls[ps[u]] == u) ls[ps[u]] = a;
		else rs[ps[u]] = a;
	}
	//    a
	//    /\
	//   /  \
	//  u    b
	ps[a] = ps[u]; ls[a] = u; rs[a] = b; 
	ps[u] = ps[b] = a; lc[b] = rc[b] = b;
	lc[a] = lc[ls[a]]; rc[a] = rc[rs[a]];
}
int S, S_le, rt, siz[N], son[N];
void dfs1(int u, int fa) {
	S++; S_le += (u <= n);
	int v[3] = {ls[u], rs[u], ps[u]};
	for (int i = 0; i < 3; i++) {
		if (v[i] && v[i] != fa && !del[v[i]]) dfs1(v[i], u);
	}
}
void dfs2(int u, int fa) {
	siz[u] = (u <= n); son[u] = 0;
	int v[3] = {ls[u], rs[u], ps[u]};
	for (int i = 0; i < 3; i++) {
		if (!v[i] || v[i] == fa || del[v[i]]) continue;
		dfs2(v[i], u);
		siz[u] += siz[v[i]];
		son[u] = max(son[u], siz[v[i]]);
	}
	son[u] = max(son[u], S_le - siz[u]);
	if (son[u] < son[rt]) rt = u;
}
void Divide(int u) {
	auto Ask = [&](int x, int y, int z) {
		printf("%d %d %d\n", x, y, z); // X ->(x,y) Y->(y,z), Z->(x,z)
		fflush(stdout);
		char s[10];
		scanf("%s", s);
		return s[0] - 'X' + 1;
	};
	S = S_le = 0;
	dfs1(u, 0);
	if (S == 1) {
		NewNode(u); return ;
	}
	rt = 0; dfs2(u, 0);
	while ((!ls[rt] || del[ls[rt]]) && (!rs[rt] || del[rs[rt]])) rt = ps[rt];
	int res = Ask(lc[ls[rt]], rc[rs[rt]], pcnt + 1);
	if (res == 1) {
		//   /\
		//  /\ x
		// ls rs
		del[ls[rt]] = del[rs[rt]] = 1; Divide(rt); 
	} else if (res == 2) {
		//  /\
		// ls rs
		//    /x
		del[rt] = 1; Divide(rs[rt]);
	} else {
		//  /\
		// ls rs
		// /x 
		del[rt] = 1; Divide(ls[rt]);
	}
}
int main() {
	scanf("%d", &n);
	cnt = n; pcnt = 1; lc[1] = rc[1] = 1;
	son[0] = n;
	for (int i = 2; i <= n; i++) {
		memset(del, 0, sizeof del);
		Divide(1);
	}
	printf("-1\n");
	for (int i = 1; i <= cnt; i++)
		printf("%d ", ps[i] ? ps[i] : -1);
	return 0;
}
