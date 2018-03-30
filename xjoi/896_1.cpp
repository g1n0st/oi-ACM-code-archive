#include <bits/stdc++.h>
using namespace std;
const int N = 4096;
void Read(int &x) {
	scanf("%d", &x);
}
int n, fr[N], to[N], f[N], L[N], D[N];
int S[N][3], T[N][3], ts[N], tt[N], id[N][2];
void init(int n) {
	for (int i = 1; i <= n; i++) f[i] = i;
}
int getf(int x) {
	return x == f[x] ? x : f[x] = getf(f[x]);
}
void merge(int x, int y) {
	x = getf(x); y = getf(y); 
	if (x == y) return;
	f[x] = y;
}
void merge(int x, int a, int y, int b) {
	x = x + (a - 1) * n; y = y + (b - 1) * n;
	merge(x, y); 
}

int p[N], A[N], B[N];
bool cmp(const int &x, const int &y) {
	return B[x] - A[x] < B[y] - A[y];
}
int calc(int x, int y) {
	return x <= y ? y - x : 24 + y - x;
}
int Solve() {
	int r = 0;
	init(4 * n);
	for (int i = 1; i <= 2 * n; i++)
		merge(fr[i], 2 + id[i][0], to[i], id[i][1]);
	for (int i = 1; i <= n; i++) {
		A[i] = calc(S[i][1], T[i][1]) + calc(S[i][2], T[i][2]);
		B[i] = calc(S[i][1], T[i][2]) + calc(S[i][2], T[i][1]);
		if (A[i] <= B[i]) {
			merge(i, 1, i, 3); merge(i, 2, i, 4);
		} else {
			swap(A[i], B[i]); merge(i, 1, i, 4); merge(i, 2, i, 3);
		}
		r += A[i];
	}
	for (int i = 1; i <= n; i++) p[i] = i;
	sort(p + 1, p + 1 + n, cmp);
	for (int i = 1; i <= n; i++) {
		int x = p[i];
		if (getf(x) != getf(x + n)) {
			r += B[x] - A[x]; merge(x, x + n);
		}
	}
	return r;
}
void Main(int cnt) {
	Read(n); int res = 0;
	for (int i = 1; i <= n; i++) ts[i] = tt[i] = 0;
	for (int i = 1; i <= n * 2; i++) {
		Read(to[i]); Read(L[i]); Read(D[i]); fr[i] = (i + 1) / 2;
		T[fr[i]][++tt[fr[i]]] = L[i];
		S[to[i]][++ts[to[i]]] = (D[i] + L[i]) % 24;
		res = res + D[i];
		id[i][0] = tt[fr[i]];
		id[i][1] = ts[to[i]];
	}
	int cur = 1 << 30;
	int t = S[1][1]; S[1][1] = 0;
	cur = min(cur, Solve()); S[1][1] = t;
	t = S[1][2]; S[1][2] = 0;
	cur = min(cur, Solve()); S[1][2] = t;
	printf("Case #%d: %d\n", cnt, cur + res);
}
int Test;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	Read(Test);
	int cnt = 0;
	while (Test--) Main(++cnt);
	return 0;
}
