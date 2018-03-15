#include "quantumbreak.h"
#include <bits/stdc++.h>
using namespace std;
const double INV2 = 1 / sqrt(2.);
double A[][2] = { {INV2, INV2}, {INV2, -INV2} };
int query_xor(int n, int t) {
	vector<int> all;
	for (int t = 0; t < 23; t++) {
		for (int i = 0; i < n; i++) manipulate(A, i);
		all.emplace_back(query());
	}
	for (int i = 1; i < (1 << n); i++) {
		bool ojbk = 1;
		for (auto u : all)
			if (__builtin_popcount(i & u) & 1) {
				ojbk = 0; break;
			}
		if (ojbk) return i;
	}
	return 233333;
}
