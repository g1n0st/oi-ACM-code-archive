#include <bits/stdc++.h>
using namespace std;
const int V = 1500000;
char str[V];
int n, w, k;
namespace SAM {
	int fa[V], c[V][26], len[V], val[V], pT, rt, lst;
	void Init() {
		rt = lst = ++pT;
	}
	void Extend(int x) {
		int cur = ++pT;
		len[cur] = len[lst] + 1; val[cur] = 1;
		int p = lst;
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) fa[cur] = rt;
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) fa[cur] = q;
			else {
				++pT; fa[pT] = fa[q]; len[pT] = len[p] + 1;
				memcpy(c[pT], c[q], sizeof c[q]);
				fa[q] = pT; fa[cur] = pT;
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
			}
		}
		lst = cur;
	}
	int v[V], q[V], sum[V];
	void Pre() {
		int i, j, t;
		for (i = 1; i <= pT; i++) v[len[i]]++;
		for (i = 1; i <= n; i++) v[i] += v[i - 1];
		for (i = pT; i; i--) q[v[len[i]]--] = i;
		for (i = pT; i; i--) {
			t = q[i];
			if (!w) val[t] = 1;
			else val[fa[t]] += val[t];
		}
		val[1] = 0;
		for (i = pT; i; i--) {
			t = q[i];
			sum[t] = val[t];
			for (j = 0; j < 26; j++) sum[t] += sum[c[t][j]];
		}
	}
	void Dfs(int u = rt, int K = k) {
		if (K <= val[u]) return; K -= val[u];
		for (int i = 0; i < 26; i++) {
			if (!c[u][i]) continue;
			if (K <= sum[c[u][i]]) {
				putchar('a' + i);
				Dfs(c[u][i], K);
				return;
			}
			K -= sum[c[u][i]];
		}
	}
}
int main() {
	int i, j;
	scanf("%s%d%d", str + 1, &w, &k);
	n = strlen(str + 1);
	SAM::Init();
	for (i = 1; i <= n; i++) SAM::Extend(str[i] - 'a');
	SAM::Pre();
	if (k > SAM::sum[1]) printf("-1");
	else SAM::Dfs();
	return 0;
}
