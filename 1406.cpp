#include <bits/stdc++.h>
using namespace std;
set<int> S;
int n;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i * i <= n; i++)
		if (n % i == 0) {
			int n1 = n / i;
			for (int x = 1; x <= n; x += n1)
				if ((x + 1) % i == 0) S.insert(x);
			for (int x = n1 - 1; x <= n; x += n1)
				if ((x - 1) % i == 0) S.insert(x);
		}
	if (!S.size()) return puts("None"), 0;
	for (set<int>::iterator it = S.begin(); it != S.end(); ++it)
		printf("%d\n", *it);
	return 0;
}
