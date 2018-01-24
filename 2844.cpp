#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
const int P = 10086;
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
int Ksm(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = r * x % P;
		if (y >>= 1) x = x * x % P;
	}
	return r;
}
int N, a[V], Q, tot, p[32];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Read(N);
	for (i = 0; i < N; i++) Read(a[i]);
	Read(Q);
	for (i = 0; i < N; i++)
		for (int j = 30; ~j; j--) {
			if (!(a[i] >> j)) continue;
			if (!p[j]) {
				p[j] = a[i]; tot++; break;
			}
			a[i] ^= p[j];
		}
	vector<int> v;
	int rnk = 0;
	for (i = 0; i <= 30; i++) if (p[i]) v.push_back(i);
	for (i = 0; i < v.size(); i++) if ((Q >> v[i]) & 1)
		rnk += (1 << i);
	rnk = (rnk % P * Ksm(2, N - tot) % P + 1) % P;
	cout << rnk << endl;
	return 0;
}
