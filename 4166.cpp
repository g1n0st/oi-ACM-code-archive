#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long LL;
typedef __gnu_pbds::gp_hash_table<LL, int> mp;
const int V = 2000010;
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
	for (; !isdigit(c); c = get());
	for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !islower(c); c = get());
	for (; islower(c); s[len++] = c, c = get());
}
char s[V];
int N, T;
mp m;
namespace Hash {
	template<size_t mo>
	struct ha {
		size_t pow[V], hash[V];
		void init() {
			pow[0] = 1; hash[0] = 0;
			for (int i = 1; i <= N; i++) {
				pow[i] = pow[i - 1] * 131u % mo; hash[i] = (hash[i - 1] * 131u + s[i]) % mo;
			}
		}
		size_t val(int l, int r) {
			return (hash[r] + mo - (size_t)((LL)hash[l - 1] * pow[r - l + 1] % mo)) % mo;
		}
	};
	ha<23333333> h1; ha<19260817> h2;
	void Init() {
		h1.init(); h2.init();
	}
	LL sub(int l, int r) {
		return (LL)h1.val(l, r) << 32 | (LL)h2.val(l, r);
	}
}
using Hash::sub;
int fa[V], sum[V], tot;
int NewNode(int f) {
	fa[++tot] = f; sum[tot] = 0; return tot;
}
void Manacher(char *str, int len) {
	static char s[V]; s[0] = '$'; s[1] = '#';
	static int p[V];
	for (int i = 1; i <= len; i++) {
		s[i << 1] = str[i]; s[i << 1 | 1] = '#';
	}
	len = len << 1 | 1; s[len + 1] = 0;
	int mx = 0, pos = 0;
	for (int i = 1; i <= len; i++) {
		p[i] = mx > i ? min(mx - i, p[pos * 2 - i]) : 1;;
		int lst = (p[i] == 1 ? 0 : m[sub((i - p[i] >> 1) + 1, i + p[i] - 1 >> 1)]);
		while (s[i + p[i]] == s[i - p[i]]) {
			++p[i];
			int &now = m[sub((i - p[i] >> 1) + 1, i + p[i] - 1 >> 1)];
			if (!now) now = NewNode(lst);
			lst = now;
		}
		if (lst) sum[lst] ^= ((i >> 1) - 1);
		if (i + p[i] > mx) {
			mx = i + p[i]; pos = i;
		}
	}

}
void Solve() {
	Read(s + 1, N); Hash::Init(); m.clear(); tot = 0;
	Manacher(s, N);
	int Ans = 0;
	for (int i = tot; i; i--) {
		Ans = max(Ans, sum[i]); sum[fa[i]] ^= sum[i];
	}
	printf("%d\n", Ans);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(T);
	while (T--) Solve();
	return 0;
}
