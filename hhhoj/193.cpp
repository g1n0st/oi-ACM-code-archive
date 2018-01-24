#include <bits/stdc++.h>
using namespace std;
const int V = 1000100;
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
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
void Read(char *s, int &len) {
	len = 0; char c = get();
	for (; c == ' ' || c == '\n'; c = get());
	for (; !(c == ' ' || c == '\n' || c == EOF); s[len++] = c, c = get()); s[len] = 0;
}

struct Node {
	int id, l, r;
	Node(int id = 0, int l = 0, int r = 0) :id(id), l(l), r(r) {}
};
int M, Rev, tar[V], len[V];
char s[V];
deque<char> S;
vector<char> q[V];
vector<Node> qur[V << 1];
int Rt[V << 1], Ans[V];

namespace SGT {
	int ls[V * 100], rs[V * 100], v[V * 100], pT;
	void Add(int &x, int l, int r, int p) {
		if (!x) x = ++pT; v[x]++;
		if (l == r) return;
		int Mid = (l + r) >> 1;
		if (p <= Mid) Add(ls[x], l, Mid, p); else Add(rs[x], Mid + 1, r, p);
	}
	int Merge(int x, int y) {
		if (!x || !y) return x + y;
		v[x] += v[y];
		ls[x] = Merge(ls[x], ls[y]); rs[x] = Merge(rs[x], rs[y]);
		return x;
	}
	int Query(int x, int l, int r, int L, int R) {
		if (!x) return 0;
		if (l == L && r == R) return v[x];
		int Mid = (l + r) >> 1;
		if (R <= Mid) return Query(ls[x], l, Mid, L, R);
		if (Mid < L) return Query(rs[x], Mid + 1, r, L, R);
		return Query(ls[x], l, Mid, L, Mid) + Query(rs[x], Mid + 1, r, Mid + 1, R);
	}
}
namespace SAM {
	int fa[V << 1], c[V << 1][26], len[V << 1], lst, rt, pT;
	void Init() {
		rt = lst = ++pT;
	}
	void Extend(int x) {
		int cur = ++pT;
		len[cur] = len[lst] + 1;
		int p = lst;
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) fa[cur] = rt;
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) fa[cur] = q;
			else {
				++pT; fa[pT] = fa[q]; len[pT] = len[p] + 1;
				memcpy(c[pT], c[q], sizeof c[q]);
				fa[q] = fa[cur] = pT;
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
			}
		}
		lst = cur;
	}
	int q[V], id[V];
	void Work(int n) {
		int i, t;
		for (i = 1; i <= pT; i++) q[len[i]]++;
		for (i = 1; i <= n; i++) q[i] += q[i - 1];
		for (i = pT; i; i--) id[q[len[i]]--] = i;
		for (i = pT; i; i--) {
			t = id[i];
			for (auto v : qur[t]) Ans[v.id] = SGT::Query(Rt[t], 1, n, v.l, v.r);
			Rt[fa[t]] = SGT::Merge(Rt[fa[t]], Rt[t]);
		}
	}
}
void Init() {
	int i, j, L;
	Read(M);
	for (i = 1; i <= M; i++) {
		Read(s + 1, L);
		switch (s[1]) {
		case '+':
			if (Rev) for (j = 2; j <= L; j++) S.emplace_front(s[j]);
			else for (j = 2; j <= L; j++) S.emplace_back(s[j]);
			tar[i] = 1;  len[i] = L - 1; break;
		case '?':
			for (j = 2; j <= L; j++) q[i].emplace_back(s[j]);
			tar[i] = 2; break;
		default:
			tar[i] = 3; Rev ^= 1;
		}
	}
	SAM::Init();
	for (i = 0; i < S.size(); i++) {
		SAM::Extend(S[i] - 'a'); SGT::Add(Rt[SAM::lst], 1, S.size(), i + 1);
	}
}
int main() {
	int i, j; Init();
	int L = 1, R = S.size();
	for (i = M; i; i--) {
		switch (tar[i]) {
		case 1:
			if (Rev) L += len[i]; else R -= len[i]; break;
		case 3: Rev ^= 1; break;
		default:
			if (Rev) reverse(q[i].begin(), q[i].end());
			int r = SAM::rt;
			for (auto v : q[i]) {
				if (!r) break; r = SAM::c[r][v - 'a'];
			}
			if (!r) continue;
			if ((R - L + 1) < q[i].size()) continue;
			qur[r].emplace_back(Node(i, L + q[i].size() - 1, R));
		}
	}

	SAM::Work(S.size());
	for (i = 1; i <= M; i++)
		if (tar[i] == 2) printf("%d\n", Ans[i]);
	return 0;
}
