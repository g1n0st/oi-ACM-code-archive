#include <bits/stdc++.h>
using namespace std;
void Read(int &x) {
	scanf("%d", &x);
}
struct Xor {
	int p[32];
	Xor() {
		memset(p, 0, sizeof p);
	}
	void Add(int x) {
		for (int i = 31; ~i; i--) {
			if (!(x >> i)) continue;
			if (!p[i]) {
				p[i] = x; break;
			}
			x ^= p[i];
		}
	}
	int Query() {
		int r = 0;
		for (int i = 31; ~i; i--)
			if ((r ^ p[i]) > r) r ^= p[i];
		return r;
	}
} s;
const int V = 100010;
int N, a[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(a[i]); s.Add(a[i]);
	}
	int mx = s.Query(), rmx = 0;
	for (int i = 31; ~i; i--)
		if (s.p[i] && (s.p[i] ^ mx) > rmx) rmx = mx ^ s.p[i];
	cout << mx << ' ' << rmx << endl;
	return 0;
} 
