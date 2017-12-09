#include <iostream>
#include <set>
#include <cstdio>
using namespace std;
typedef long long LL;
const int V = 800100;
char get(void) {
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
		x = x * 10 + c - '0';
		c = get();
	}
}
char GetC(void) {
	char c = get();
	while (c > 'Z' || c < 'A') c = get();
}
void Write(LL x) {
	if (!x) {
		puts("0");
		return;
	}
	static int s[100], t;
	while (x) {
		s[++t] = x % 10;
		x /= 10;
	}
	while (t) putchar('0' + s[t--]);
	putchar('\n');
}
namespace Bit {
	int N;
	LL t[V];
	int lowbit(int x) {
		return x & (-x);
	}
	void Modify(int x, int v) {
		while (x <= N) {
			t[x] += v;
			x += lowbit(x);
		}
	}
	LL Query(int x) {
		LL Ret = 0;
		while (x) {
			Ret += t[x];
			x -= lowbit(x);
		}
		return Ret;
	}
};
struct Node {
	int x, y, op, v;
	Node() {}
	Node(int op, int x, int y, int v) : op(op), x(x), y(y), v(v) {}
} tmp[V], p[V];
LL Ans[V];
int N, Q, cntQ, cntP, lst[V], a[V];
set<int> S[V];
void Modify(int pos, int x) {
	if (a[pos] == x) return;
	set<int>::iterator it = S[a[pos]].find(pos);
	int l = 0, r = 0, Now = *it;
	// before modify
	if (it != S[a[pos]].begin()) {
		--it; l = *it;
		p[++cntP] = Node(0, Now, l, l - Now);
		++it;
	}
	++it;
	if (it != S[a[pos]].end()) {
		r = *it;
		p[++cntP] = Node(0, r, Now, Now - r);
	}
	if (l && r) p[++cntP] = Node(0, r, l, r - l);
	S[a[pos]].erase(pos);
	// after modify
	a[pos] = x;
	it = S[x].insert(pos).first;
	l = 0; r = 0; Now = *it;
	if (it != S[x].begin()) {
		--it; l = *it;
		p[++cntP] = Node(0, Now, l, Now - l);
		++it;
	}
	++it;
	if (it != S[x].end()) {
		r = *it;
		p[++cntP] = Node(0, r, Now, r - Now);
	}
	if (l && r) p[++cntP] = Node(0, r, l, l - r);
}
void Work(int l, int r) {
	if (l == r) return;
	int Mid = (l + r) >> 1;
	Work(l, Mid); Work(Mid + 1, r);
	for (int i = l; i <= r; i++) tmp[i] = p[i];
	int p1 = l, p2 = Mid + 1, top = l;
	while (p1 <= Mid || p2 <= r) {
		if (p2 > r || (p1 <= Mid && tmp[p1].x <= tmp[p2].x)) {
			p[top++] = tmp[p1];
			if (!tmp[p1].op)
				Bit::Modify(N - tmp[p1].y + 1, tmp[p1].v);
			p1++;
		}
		else {
			p[top++] = tmp[p2];
			if (tmp[p2].op)
				Ans[tmp[p2].v] += Bit::Query(N - tmp[p2].y + 1);
			p2++;
		}
	}
	for (int i = l; i <= Mid; i++)
		if (!tmp[i].op)
			Bit::Modify(N - tmp[i].y + 1, -tmp[i].v);
}
int main(void) {
	int i, j;
	Read(N); Read(Q); Bit::N = N;
	for (i = 1; i <= N; i++) {
		Read(a[i]);
		S[a[i]].insert(i);
		if (lst[a[i]]) p[++cntP] = Node(0, i, lst[a[i]], i - lst[a[i]]);
		lst[a[i]] = i;
	}
	int x, y; char op;
	for (i = 1; i <= Q; i++) {
		op = GetC(); Read(x); Read(y);
		if (op == 'M') Modify(x, y);
		else p[++cntP] = Node(1, y, x, ++cntQ);
	}
	Work(1, cntP);
	for (i = 1; i <= cntQ; i++) Write(Ans[i]);
	return 0;
}
