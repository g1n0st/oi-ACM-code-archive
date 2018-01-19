#include <bits/stdc++.h>
using namespace std;
const int V = 5000010;
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
	len = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; s[len++] = c, c = get());
}

namespace SAM {
	int len[V], fa[V], c[V][3], pT, lst, rt;
	void Init() {
		rt = lst = ++pT;
	}
	void Extend(int x) {
		int cur = ++pT; len[cur] = len[lst] + 1;
		int p = lst;
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) fa[cur] = rt;
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) fa[cur] = q;
			else {
				++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[q] = fa[cur] = pT;
			}
		}
		lst = cur;
	}
	int mat[V];
	void Work(char *s, int n) {
		int p = rt;
		for (int i = 1; i <= n; i++) {
			int x = s[i] - '0';
			if (c[p][x]) {
				mat[i] = mat[i - 1] + 1;
				p = c[p][x];
			}
			else {
				while (p && !c[p][x]) p = fa[p];
				if (!p) {
					p = rt; mat[i] = 0;
				}
				else {
					mat[i] = len[p] + 1; p = c[p][x];
				}
			}
		}
	}
}
int N, M, L, f[V];
char s[V];
void Init() {
	int i, j;
	Read(N); Read(M); SAM::Init();
	for (i = 1; i <= M; i++) {
		Read(s + 1, L);
		for (j = 1; j <= L; j++) SAM::Extend(s[j] - '0');
		SAM::Extend(2);
	}
}
struct DQ {
	int v[V], p[V], H, T;
	void Init() {
		H = 1; T = 0;
	}
	void Push(int val, int pos) {
		while (H <= T && v[T] < val) --T;
		v[++T] = val; p[T] = pos;
	}
	void Pop(int lim) {
		while (H <= T && p[H] < lim) ++H;
	}
	int top() {
		return v[H];
	}
	int empty() {
		return !(H <= T);
	}
} q;
int Check(int x) {
	int i, j;
	for (i = 0; i <= L; i++) f[i] = 0;
	q.Init();
	for (i = 1; i <= L; i++) {
		f[i] = f[i - 1];
		if (i - x >= 0) q.Push(f[i - x] - (i - x), i - x);
		q.Pop(i - SAM::mat[i]);
		if (!q.empty()) f[i] = max(f[i], q.top() + i);
	}
	return f[L] >= L * 0.9 - 1e-8;
}
void Solve() {
	Read(s + 1, ::L); SAM::Work(s, ::L);
	int L = 0, R = ::L, Mid, Ans = 0;
	while (L <= R) {
		if (Check(Mid = L + R >> 1)) L = (Ans = Mid) + 1;
		else R = Mid - 1;
	}
	printf("%d\n", Ans);
}
int main() {
	Init();
	while (N--) Solve();
}
