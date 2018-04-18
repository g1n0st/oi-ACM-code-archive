#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int V = 100010;

char s[V];
LL n, pre0[V], suf2[V], pre1[V], suf1[V];

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	cin >> n >> s + 1;

	for (int i = 1; i <= n; i++) pre0[i] = pre0[i - 1] + (s[i] == 'J');
	for (int i = n; i; i--)			 suf2[i] = suf2[i + 1] + (s[i] == 'I');
	for (int i = 1; i <= n; i++) pre1[i] = pre1[i - 1] + (s[i] == 'O') * pre0[i];
	for (int i = n; i; i--) suf1[i] = suf1[i + 1] + (s[i] == 'O') * suf2[i];
	
	LL lst = 0, cur = 0;
	
	for (int i = 1; i <= n; i++) lst += (s[i] == 'O') * pre0[i] * suf2[i];
	
	cur = max(pre1[n], suf1[1]);
	for (int i = 1; i < n; i++) cur = max(cur, pre0[i] * suf2[i + 1]);

	cout << lst + cur << endl;

	return 0;
}
