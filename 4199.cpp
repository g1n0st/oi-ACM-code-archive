#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 600010;
const int INF = 2000000000;
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
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get());
}
LL AnsMx[V], AnsTot[V];
namespace SAM {
	int c[V][26], fa[V], len[V], val[V], lst, rt, pT;
	int mn0[V], mn1[V], mx0[V], mx1[V];
	void Init() {
		lst = rt = ++pT;
	}
	void NewNode(int x) {
		mn0[x] = mn1[x] = INF; mx0[x] = mx1[x] = -INF;
	}
	void Extend(int x, int va) {
		int cur = ++pT; NewNode(cur);  mx0[cur] = mn0[cur] = va;
		len[cur] = len[lst] + 1; val[cur] = 1;
		int p = lst; 
		while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
		if (!p) fa[cur] = rt;
		else {
			int q = c[p][x];
			if (len[q] == len[p] + 1) fa[cur] = q;
			else {
				NewNode(++pT); len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (c[p][x] == q) c[p][x] = pT, p = fa[p];
				fa[q] = fa[cur] = pT;
			}
		}
		lst = cur;
	}
	int q[V], id[V];
	void Pre(int n) {
		for (int i = 1; i <= pT; i++) q[len[i]]++;
		for (int i = 1; i <= n; i++) q[i] += q[i - 1];
		for (int i = pT; i; i--) id[q[len[i]]--] = i;
	}
	void QMax(int x, int va) {
		if (va > mx0[x]) {
			mx1[x] = mx0[x]; mx0[x] = va;
		} else mx1[x] = max(mx1[x], va);
	}
	void QMin(int x, int va) {
		if (va < mn0[x]) {
			mn1[x] = mn0[x]; mn0[x] = va;
		} else mn1[x] = min(mn1[x], va);
	}
	void Work() {
		for (int i = pT; i; i--) {
			int t = id[i];
			if (val[t] > 1) {
				AnsMx[len[t]] = max(AnsMx[len[t]], max((LL)mn0[t] * mn1[t], (LL)mx0[t] * mx1[t]));
				AnsTot[len[t]] += (LL)val[t] * (val[t] - 1) / 2;
				if (t ^ rt) AnsTot[len[fa[t]]] -= (LL)val[t] * (val[t] - 1) / 2;
			}
			QMax(fa[t], mx0[t]); QMax(fa[t], mx1[t]); 
			QMin(fa[t], mn0[t]); QMin(fa[t], mn1[t]);
			val[fa[t]] += val[t];
		}
	}
}
int N, a[V];
char s[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(N); Read(s + 1, N); SAM::Init();
	for (int i = 1; i <= N; i++) Read(a[i]);
	for (int i = N; i; i--) SAM::Extend(s[i] - 'a', a[i]);
	memset(AnsMx, 0xc0, sizeof AnsMx);
	SAM::Pre(N); SAM::Work();
	for (int i = N; i >= 0; i--) AnsMx[i] = max(AnsMx[i], AnsMx[i + 1]);
	for (int i = N; i >= 0; i--) AnsTot[i] += AnsTot[i + 1];
	for (int i = N; i >= 0; i--) if (!AnsTot[i]) AnsMx[i] = 0;
	for (int i = 0; i < N; i++) printf("%lld %lld\n", AnsTot[i], AnsMx[i]);
	return 0;
}
