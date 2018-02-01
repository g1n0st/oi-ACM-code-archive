#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
typedef long long LL;
const int vB = 400;
LL gcd(LL x, LL y) {
	return !y ? x : gcd(y, x % y);
}
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
template<class T>
void Read(T &x) {
	x = 0; static char c;
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
void Re(char &x) {
	x = get(); while (!isupper(x)) x = get();
}
int N, B, M, bl[V], br[V], bel[V], a[V], px[V], pg[V];
map<int, int> pos[vB];
void Build(int x) {
	int L = bl[x], R = br[x];
	pos[x].clear();
	pg[L] = px[L] = a[L];  pos[x][px[L]] = L;
	for (int i = L + 1; i <= R; i++) {
		pg[i] = gcd(pg[i - 1], a[i]); px[i] = px[i - 1] ^ a[i];
		if (!pos[x].count(px[i])) pos[x][px[i]] = i;
	}
}
int Query(LL x) {
	LL lstG = x; int lstX = 0;
	for (int i = 1; i <= B; i++) {
		int L = bl[i], R = br[i];
		if (gcd(lstG, pg[R]) == lstG) {
			int qval = (x / lstG) ^ lstX;
			if (pos[i].count(qval)) return pos[i][qval];
		}
		else {
			for (int k = L; k <= R; k++)
				if (x / gcd(lstG, pg[k]) == (lstX ^ px[k])) return k;
		}
		lstG = gcd(lstG, pg[R]); lstX ^= px[R];
	}
	return 0;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); B = sqrt(N);
	for (int i = 1; i <= N; i++) Read(a[i]);
	for (int i = 1; i <= N; i++) bel[i] = (i - 1) / B + 1;
	for (int i = 1; i <= N; i++) br[bel[i]] = i;
	for (int i = N; i; i--) bl[bel[i]] = i; B = bel[N];
	for (int i = 1; i <= B; i++) Build(i);
	int x, y; char op; LL lx;
	Read(M);
	while (M--) {
		Re(op);
		if (op == 'M') {
			Read(x); Read(y); a[++x] = y; Build(bel[x]);
		}
		else {
			Read(lx);
			int val = Query(lx) - 1;
			if (~val) printf("%d\n", val);
			else printf("no\n");
		}
	}
	return 0;
}
