#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, int> PI;
const int V = 100010;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(int &x) {
	x = 0; static char c; int f = 0;
	for (; !isdigit(c); c = get()) if (c == '-') f ^= 1;
	for (; isdigit(c); x = x * 10 + c - '0', c = get()); if (f) x = -x;
}
namespace SGT {
	const int N = V * 100;
	int ls[N], rs[N], rt[N], pT; PI val[N]; LL tag[N];
	void Build(int &x, int l, int r) {
		x = ++pT; val[x] = PI(0, l);
		if (l == r) return;
		int Mid = (l + r) >> 1;
		Build(ls[x], l, Mid); Build(rs[x], Mid + 1, r);
	}
	void Add(int &x, int w) {
		int y = ++pT; ls[y] = ls[x]; rs[y] = rs[x];
		val[y] = val[x]; val[y].first += w; tag[y] = tag[x] + w; x = y;

	}
	void Cha(int &x, int y, int l, int r, int L, int R, int w) {
		x = ++pT; val[x] = val[y]; tag[x] = tag[y]; ls[x] = ls[y]; rs[x] = rs[y];
		if (l == L && r == R) return Add(x, w);
		int Mid = (l + r) >> 1;
		if (R <= Mid) Cha(ls[x], ls[y], l, Mid, L, R, w);
		else if (Mid < L) Cha(rs[x], rs[y], Mid + 1, r, L, R, w);
		else {
			Cha(ls[x], ls[y], l, Mid, L, Mid, w); Cha(rs[x], rs[y], Mid + 1, r, Mid + 1, R, w);
		}
		val[x] = max(val[ls[x]], val[rs[x]]); val[x].first += tag[x];
	}
	PI Qur(int x, int l, int r, int L, int R) {
		if (l == L && r == R) return val[x];
		int Mid = (l + r) >> 1; PI ret;
		if (R <= Mid) ret = Qur(ls[x], l, Mid, L, R);
		else if (Mid < L) ret = Qur(rs[x], Mid + 1, r, L, R);
		else ret = max(Qur(ls[x], l, Mid, L, Mid), Qur(rs[x], Mid + 1, r, Mid + 1, R));
		ret.first += tag[x]; return ret;
	}
}
using SGT::Qur; using SGT::Cha; using SGT::rt; using SGT::Build;
int N, M, a[V], pre[V]; PI b[V];
struct Node {
	int id, l, r, y; LL x;
	Node() {}
	Node(int id, int l, int r, int y, LL x) : id(id), l(l), r(r), y(y), x(x) {}
	friend bool operator < (Node a, Node b) {
		return a.x < b.x || a.x == b.x && a.id < b.id;
	}
};
priority_queue<Node>q;
int cnt;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("a.txt", "w", stdout);
	Read(N); Read(M);
	for (int i = 1; i <= N; i++) {
		Read(a[i]); b[i] = PI(a[i], i);
	}
	sort(b + 1, b + 1 + N);
	for (int i = 1; i <= N; i++)
		if (i > 1 && b[i].first == b[i - 1].first) pre[b[i].second] = b[i - 1].second;
	Build(rt[0], 1, N);
	for (int i = 1; i <= N; i++) {
		cnt++;
		Cha(rt[i], rt[i - 1], 1, N, pre[i] + 1, i, a[i]);
		PI t = Qur(rt[i], 1, N, 1, i);
		q.push(Node(i, 1, i, t.second, t.first));
	}
	for (int i = 1; i <= M; i++) {
		Node u = q.top(); q.pop();
		if (i == M) printf("%lld\n", u.x);
		else {
			if (u.y > u.l) {
				PI t = Qur(rt[u.id], 1, N, u.l, u.y - 1);
				q.push(Node(u.id, u.l, u.y - 1, t.second, t.first));
			}
			if (u.y < u.r) {
				PI t = Qur(rt[u.id], 1, N, u.y + 1, u.r);
				q.push(Node(u.id, u.y + 1, u.r, t.second, t.first));
			}
		}
	}
	return 0;
}
