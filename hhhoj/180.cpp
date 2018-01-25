#include <bits/stdc++.h>
using namespace std;
typedef unsigned U;
const int M_LEN = 10;
const int D_SIZE = 1024;
const int S_RANGE = 8;
int Rd() {
	return (rand() << 16) | rand();
}
int hash_0(U x) {
	int r = 0;
	for (; x; x >>= 1) r += (x & 0x01);
	return r & 1;
}
int hash_1(U x) {
	int r = 0;
	for (; x; x >>= 3) r ^= (x & 0x07);
	return r;
}
namespace W1 {
	U w[D_SIZE + 1]; int f[D_SIZE + 1], id[D_SIZE + 1];
	struct Buf {
		string buf; int tmp[32];
		~Buf() { std::cout << buf; }
		void _c(int x) { buf += (x + '0'); }
		void ext(int x) {
			memset(tmp, 0x00, sizeof tmp);
			for (int i = 0; i < M_LEN; i++) tmp[i] = ((x >> i) & 1);
			for (int i = M_LEN - 1; ~i; i--) _c(tmp[i]);
		}
		void ext(int val, int l0) {
			memset(tmp, 0x00, sizeof tmp);
			int len = 0;
			while (val) {
				tmp[len++] = val & 1; val >>= 1;
			}
			len = max(len, l0);
			for (int i = len; i > l0; i--) _c(0); _c(1);
			for (int i = len - 1; ~i; i--) _c(tmp[i]);
		}
	} $;
	void low_r(int l, int r) {
		int k0, cnt = 0, num; static int CNT, tmp[S_RANGE];
		do {
			cnt++; CNT++; k0 = Rd(); num = 0;
			for (int i = l; i <= r; i++) tmp[hash_1(w[id[i]] & k0)] = CNT;
			for (int i = 0; i < S_RANGE; i++) num += (tmp[i] == CNT);
		} while (num ^ 8);
		$.ext(cnt, S_RANGE - 1);
		for (int i = 0; i < S_RANGE; i++)
			for (int j = l; j <= r; j++)
				if (hash_1(w[id[j]] & k0) == i) $.ext(f[id[j]]);
	}
	void divide(int l, int r) {
		if (r - l == S_RANGE - 1) return low_r(l, r);
		int len = r - l + 1, cnt = 0, lim = 0, num, k0;
		while ((1 << lim) ^ len) lim++; lim = (lim + 2) >> 1;
		do {
			num = 0; ++cnt; k0 = rand();
			for (int i = l; i <= r; i++) num += hash_0(w[id[i]] & k0);
		} while (num != len / 2);
		int now = l;
		for (int i = l; i <= r; i++)
			if (!hash_0(w[id[i]] & k0)) {
				swap(id[i], id[now]); ++now;
			}
		$.ext(cnt, lim);
		int Mid = (l + r) >> 1;
		divide(l, Mid); divide(Mid + 1, r);
	}
	void Solve() {
		for (int i = 1; i <= D_SIZE; i++) {
			cin >> w[i] >> f[i]; id[i] = i;
		}
		divide(1, D_SIZE);
	}
}

namespace W2 {
	int Q, id[D_SIZE + 1], ans[D_SIZE + 1]; U w[D_SIZE + 1];
	struct Buf {
		string buf; int ptr;
		void Init() { std::cin >> buf; ptr = 0; }
		int _c() {
			return buf[ptr++] - '0';
		}
		int cpy() {
			int r = 0;
			for (int i = 0; i < M_LEN; i++) r = (r << 1) | _c();
			return r;
		}
		int cpy(int lim) {
			while (!_c()) ++lim;
			int r = 0;
			for (int i = 0; i < lim; i++) r = (r << 1) | _c();
			return r;
		}
	} $;
	void low_r(int l, int r, int L, int R) {
		static int tmp[S_RANGE];
		int cnt = $.cpy(S_RANGE - 1), k0 = 0;
		while (cnt--) k0 = Rd();
		for (int i = 0; i < S_RANGE; i++) tmp[i] = $.cpy();
		for (int i = L; i <= R; i++) ans[id[i]] = tmp[hash_1(w[id[i]] & k0)];
	}
	void divide(int l, int r, int L, int R) {
		if (r - l == S_RANGE - 1) return low_r(l, r, L, R);
		int len = r - l + 1, cnt, lim = 0, k0 = 0;
		while ((1 << lim) ^ len) lim++; lim = (lim + 2) >> 1;
		for (cnt = $.cpy(lim); cnt--;) k0 = rand();
		int now = L;
		for (int i = L; i <= R; i++)
			if (!hash_0(w[id[i]] & k0)) {
				swap(id[i], id[now]); ++now;
			}
		int Mid = (l + r) >> 1;
		divide(l, Mid, L, now - 1); divide(Mid + 1, r, now, R);
	}
	void Solve() {
		$.Init(); cin >> Q;
		for (int i = 1; i <= Q; i++) {
			cin >> w[i]; id[i] = i;
		}
		divide(1, D_SIZE, 1, Q);
		for (int i = 1; i <= Q; i++) cout << ans[i] << endl;
	}
}
string SIGN;
int main() {
	ios::sync_with_stdio(false);
	srand(0);
	cin >> SIGN;
	if (SIGN == "encode") W1::Solve();
	else W2::Solve();
	return 0;
}
