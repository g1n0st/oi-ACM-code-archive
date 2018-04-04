#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 2010;

int n;

string s;

int a[N], tot, vis[N];

bitset<N> d, ba[N], sel[N];



void Trans(string s) {
	reverse(s.begin(), s.end());
	while (s.size() % 8) s += '0';
	int L = s.size() / 8;
	for (int i = 0; i < L; i++) {
		a[i] = 0;
		for (int j = 7; ~j; j--)
			a[i] = a[i] * 10 + s[i * 8 + j] - '0';
	}
	LL S = 0; tot = 0;
	while (L) {
		S = 0;
		for (int i = L - 1; ~i; i--) {
			S = S * 100000000LL + a[i];
			a[i] = S >> 32;
			S %= (1LL << 32);
		}
		for (int i = 0; i < 32; i++)
			d[tot++] = ((S >> i) & 1);
		while (L && a[L - 1] == 0) --L; 
	}
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s; Trans(s);
		bitset<N> ns; int flg = 1;
		for (int j = tot - 1; ~j; j--) if (d[j])
			if (vis[j]) {
				d ^= ba[j]; ns ^= sel[j];
			} else {
				flg = 0; ns.flip(i);
				ba[j] = d; sel[j] = ns; vis[j] = 1;
				break;
			}
		if (!flg) {
			cout << 0 << endl; continue;
		} else {
			cout << ns.count() << ' ';
			for (int i = 0; i < N; i++)
				if (ns[i]) cout << i << ' '; cout << endl;
		}
	}
	return 0;
}
