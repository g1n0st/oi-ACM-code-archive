#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, LL> PI;
const int V = 100010;
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
	for (; !(c >= '0' && c <= '9'); c = get());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int N, Ans; LL p[70];
vector<PI> a;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	LL x; int y, i, j;
	Read(N);
	for (i = 1; i <= N; i++) {
		Read(x); Read(y);
		a.push_back(PI(y, x));
	}
	sort(a.begin(), a.end(), greater<PI>());
	for (i = 0; i < a.size(); i++)
		for (j = 63; ~j; j--) {
			if (!(a[i].second >> j)) continue;
			if (!p[j]) {
				p[j] = a[i].second; Ans += a[i].first; break;
			}
			a[i].second ^= p[j];
		}
	cout << Ans << endl;
	return 0;
}
