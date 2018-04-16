#include <cstdio>
#include <ctype.h>
#include <algorithm>

inline int nxt_bit() {
	static char c; c = getchar();
	while (!isdigit(c)) c = getchar();
	return c - '0';
}

const int N = 5050;
const int P = 1000000007;

int n, m, Q;
int mi[N], num[N];
int rk[N], tmp[N], kth[N], a[N];

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	scanf("%d%d%d", &n, &m, &Q);

	int fill1 = 0;
	for (int i = 1; i <= m; i++) fill1 = (fill1 * 2 + 1) % P;
	mi[0] = 1;
	for (int i = 1; i <= n; i++) mi[i] = mi[i - 1] * 2 % P;

	for (int i = 1; i <= m; i++) kth[i] = i;
	for (int i = 1; i <= n; i++) {
		int bit[2] = { 0, 0 };
		for (int j = 1; j <= m; j++) bit[a[j] = nxt_bit()]++;
		bit[0] += bit[1];
		for (int j = m; j; j--) tmp[bit[a[kth[j]]]--] = kth[j];
		for (int j = 1; j <= m; j++) std::swap(kth[j], tmp[j]);
		for (int j = 1; j <= m; j++) num[j] = (num[j] + a[j] * mi[i - 1]) % P;
	}

	for (int i = 1; i <= m; i++) rk[kth[i]] = i;

	while (Q--) {
		
		int mx = 0, mn = m + 1;
		for (int i = 1; i <= m; i++)
			if (nxt_bit()) mx = std::max(mx, rk[i]);
			else mn = std::min(mn, rk[i]);
		
		if (mx > mn) {
			puts("0"); continue;
		}

		int val1 = mx ? num[kth[mx]] : mi[n];
		int val2 = mx == m ? 0 : num[kth[mx + 1]];

		printf("%d\n", (val1 - val2 + P) % P);
	}
	return 0;
}
