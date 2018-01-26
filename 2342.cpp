#include <bits/stdc++.h>
using namespace std;
const int V = 1000100;
char str[V]; int len, p[V];
char s[V]; int f[V];
void Manacher() {
	int i, j;
	for (s[0] = '$', s[1] = '#', i = 1; i <= len; i++) {
		s[i << 1] = str[i]; s[i << 1 | 1] = '#';
	}
	int t = len << 1 | 1;
	int mx = 1, pos = 1;
	for (i = 1; i <= t; i++) {
		if (i < mx) f[i] = min(f[pos * 2 - i], mx - i); else f[i] = 1;
		while (i + f[i] <= t && s[i + f[i]] == s[i - f[i]]) f[i]++;
		if (f[i] + i > mx) {
			mx = f[i] + i; pos = i;
		}
	}
	for (i = 1; i <= len; i++) p[i] = (f[i << 1 | 1] - 1) / 2;
}
struct PI {
	int x, y;
	PI(int x = 0, int y = 0) : x(x), y(y) {}
	friend bool operator < (const PI &a, const PI &b) {
		return a.x < b.x;
	}
};
PI g[V]; int tot;
set<int>S;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	scanf("%d%s", &len, str + 1);
	Manacher();
	for (i = 1; i <= len; i++) g[++tot] = PI(i - p[i], i);
	sort(g + 1, g + 1 + tot);
	int Ans = 0;
	for (i = 1, j = 1; i <= len; i++) {
		while (j < tot && g[j].x <= i) S.insert(g[j++].y);
		set<int>::iterator it = S.upper_bound(i + p[i] / 2); --it;
		if (it == S.begin()) continue;
		Ans = max(Ans, *it - i);
	}
	cout << Ans * 4 << endl;
	return 0;
}
