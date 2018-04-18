#include <cstdio>
#include <ctype.h>
#include <algorithm>
#include <vector>

namespace __g1n0st_workspace__ {

	typedef long long LL;
	typedef std::pair<int, int> PI;
	typedef std::pair<int, PI> PII;

	static const int V = 100010;

	// fast IO module
	inline char get() {
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

	char pbuf[V], *pp = pbuf;
	inline void push(const char c) {
		if (pp == pbuf + V) fwrite(pbuf, 1, V, stdout), pp = pbuf;
		*pp++ = c;
	}
	inline void Write(LL x) {
		static char sta[20];
		int top = 0;
		if (!x) push('0');
		while (x) sta[++top] = x % 10 ^ '0', x /= 10;
		while (top) push(sta[top--]);
		push('\n');
	}
	inline void flush() {
		fwrite(pbuf, 1, pp - pbuf, stdout);
	}

	std::vector<int> G;
	int n, Q, A[V], B[V];
	std::vector<PII> qr;

	struct Binary_Index {
		int n; LL val[V << 2];
		inline int lowbit(int x) {
			return x & -x;
		}
		inline void add(int x, int v) {
			for (; x <= n; x += lowbit(x)) val[x] += v;
		}
		inline LL query(int x) {
			LL r = 0;
			for (; x; x -= lowbit(x)) r += val[x];
			return r;
		}
	} num_pre_A, val_pre_A, num_pre_B, val_pre_B;

	inline LL calc(Binary_Index &num_pre, Binary_Index &val_pre, int key) {
		LL res = val_pre.query(key), lst = n - num_pre.query(key);
		return res + lst * G[key];
	}
	inline int kth(int x) {
		return std::lower_bound(G.begin(), G.end(), x) - G.begin();
	}
	void __main__() {
		Read(n);
		for (int i = 1; i <= n; i++) {
			Read(A[i]); G.emplace_back(A[i]);
		}
		for (int i = 1; i <= n; i++) {
			Read(B[i]); G.emplace_back(B[i]);
		}
		
		Read(Q);
		int type, x, y;
		while (Q--) {
			Read(type); Read(x); Read(y);
			G.emplace_back(y);
			qr.emplace_back(PII (type, {x, y} ));
		}

		G.emplace_back(-1);
		std::sort(G.begin(), G.end());
		G.erase(std::unique(G.begin(), G.end()), G.end());

		num_pre_A.n = num_pre_B.n = val_pre_A.n = val_pre_B.n = G.size();

		for (int i = 1; i <= n; i++) {
			A[i] = kth(A[i]);
			val_pre_A.add(A[i], G[A[i]]);
			num_pre_A.add(A[i], 1);
		}
		for (int i = 1; i <= n; i++) {
			B[i] = kth(B[i]);
			val_pre_B.add(B[i], G[B[i]]);
			num_pre_B.add(B[i], 1);
		}

		LL ans = 0;
		for (int i = 1; i <= n; i++)
			ans += calc(num_pre_A, val_pre_A, B[i]);

		Write(ans);
		
		for (auto v : qr) {
			type = v.first; x = v.second.first; y = v.second.second;
			if (type) {
				ans -= calc(num_pre_A, val_pre_A, B[x]);
				num_pre_B.add(B[x], -1);
				val_pre_B.add(B[x], -G[B[x]]);
				B[x] = kth(y);
				ans += calc(num_pre_A, val_pre_A, B[x]);
				num_pre_B.add(B[x], 1);
				val_pre_B.add(B[x], G[B[x]]);
			}
			else {
				ans -= calc(num_pre_B, val_pre_B, A[x]);
				num_pre_A.add(A[x], -1);
				val_pre_A.add(A[x], -G[A[x]]);
				A[x] = kth(y);
				ans += calc(num_pre_B, val_pre_B, A[x]);
				num_pre_A.add(A[x], 1);
				val_pre_A.add(A[x], G[A[x]]);
			}

			Write(ans);
		}
		flush();
	}
}
int main() {

#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	__g1n0st_workspace__::__main__();

	return 0;
}
