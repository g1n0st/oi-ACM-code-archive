#include <bits/stdc++.h>
using namespace std;
const int V = 50010;
char s[V]; int N, mxr[V];
void Manacher(char *str, int len) {
	static char s[V << 1]; static int p[V << 1], id[V << 1];
	memset(p, 0, sizeof p);
	int i, j;
	for (s[0] = '$', s[1] = '#', i = 1; i <= len; i++) {
		s[i << 1] = str[i]; s[i << 1 | 1] = '#'; id[i << 1] = i;
	}
	len = len << 1 | 1;
	int mx = 1, pos = 1;
	for (i = 1; i <= len; i++) {
		p[i] = min(p[pos * 2 - i], mx - i);
		while (s[i + p[i]] == s[i - p[i]]) {
			if (s[i - p[i]] != '#') mxr[id[i - p[i]]] = id[i + p[i]];
			p[i]++;
		}
		if (i + p[i] > mx) {
			mx = i + p[i]; pos = i;
		}
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	while (~scanf("%s", s + 1)) {
		N = strlen(s + 1); s[++N] = '^';
		for (int i = 1; i <= N; i++) mxr[i] = i;
		Manacher(s, N);
		int lst, mx, ans = 0; lst = mx = mxr[1] + 1;
		for (i = 1; i <= N; i++) {
			if ((i - 1) == lst) lst = mx, ans++;
			mx = max(mx, mxr[i] + 1);
		}
		cout << ans << endl;
	}
	return 0;
}
