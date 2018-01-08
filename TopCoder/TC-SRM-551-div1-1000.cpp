// BEGIN CUT HERE

// END CUT HERE
#line 5 "SweetFruits.cpp"  
#include <vector>  
#include <list>  
#include <map>  
#include <set>  
#include <deque>  
#include <stack>  
#include <bitset>  
#include <algorithm>  
#include <functional>  
#include <numeric>  
#include <utility>  
#include <sstream>  
#include <iostream>  
#include <iomanip>  
#include <cstdio>  
#include <cmath>  
#include <cstdlib>  
#include <ctime>  
#include <cstring>  
using namespace std;

typedef long long LL;
const int P = 1000000007;
const int V = 51;
int Pow(int x, int y, int p = P) {
	int r = 1;
	while (y) {
		if (y & 1) r = r * x % p;
		y >>= 1;
		if (y) x = x * x % p;
	}
	return r;
}
class SweetFruits {
public:
	int N, M, S;
	LL a[V][V], s[V], C[V][V], t[V];
	vector <LL> A[V], B[V];
	void Add(int x, int y) {
		a[x][y]--; a[y][x]--; a[x][x]++; a[y][y]++;
	}
	LL Guass(int n) {
		LL Det = 1; int f = 1;
		int i, j, k;
		for (i = 1; i < n; i++)
			for (j = 1; j < n; j++)
				(a[i][j] += P) %= P;

		for (i = 1; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				LL x = a[i][i], y = a[j][i];
				while (y) {
					LL t = x / y; x %= y; swap(x, y);
					for (k = i; k < n; k++) a[i][k] = (a[i][k] - t * a[j][k] % P + P) % P;
					for (k = i; k < n; k++) swap(a[i][k], a[j][k]);
					f = -f;
				}
			}
			if (!a[i][i]) return 0;
			Det = Det * a[i][i] % P;
		}
		if (f == -1) Det = (P - Det) % P;
		while (Det < 0) Det += P;
		return Det;
	}
	LL Calc(int k) {
		int i, j;
		memset(a, 0, sizeof a);
		for (i = 1; i <= N; i++)
			for (j = i + 1; j <= N; j++)
				if (j > S || i <= k && j <= k) Add(i, j);
		return Guass(N);
	}
	void Init(int n) {
		int i, j;
		memset(C, 0, sizeof C);
		C[0][0] = 1;
		for (i = 1; i <= n; i++) {
			C[i][0] = 1;
			for (j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
	}
	int countTrees(vector <int> sweetness, int maxSweetness) {
		//$CARETPOSITION$
		int i, j, x, y;
		N = sweetness.size(); M = maxSweetness; S = 0;
		for (i = 0; i < N; i++) {
			s[i] = sweetness[i]; S += (s[i] != -1);
		}
		Init(N);
		sort(s, s + N, greater<LL>());
		memset(t, 0, sizeof t);
		for (i = 0; i <= S; i++) {
			t[i] = Calc(i);
			for (j = 0; j < i; j++) (t[i] += P - C[i][j] * t[j] % P) %= P;
		}

		int s1 = S / 2, s2 = S - s1;
		for (i = 0; i <= s1; i++) A[i].clear();
		for (i = 0; i <= s2; i++) B[i].clear();
		for (i = 0; i < (1 << s1); i++) {
			LL sum = 0; int cnt = 0;
			for (j = 0; j < s1; j++)
				if ((i >> j) & 1) sum += s[j], cnt++;
			A[cnt].push_back(sum);
		}
		for (i = 0; i < (1 << s2); i++) {
			LL sum = 0; int cnt = 0;
			for (j = 0; j < s2; j++)
				if ((i >> j) & 1) sum += s[j + s1], cnt++;
			B[cnt].push_back(sum);
		}
		for (i = 0; i <= s1; i++) sort(A[i].begin(), A[i].end());
		for (i = 0; i <= s2; i++) sort(B[i].begin(), B[i].end());
		LL Ans = 0LL;
		for (x = 0; x <= s1; x++)
			for (y = 0; y <= s2; y++) {
				LL cnt = 0; int i, j;
				for (i = A[x].size() - 1, j = 0; ~i; i--) {
					for (; j < B[y].size() && A[x][i] + B[y][j] <= M; j++) ++cnt;
					Ans = (Ans + cnt * t[x + y] % P) % P;
				}
			}
		return Ans;
	}

	// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { -1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 1; verify_case(0, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = { 1, 2, -1, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 7; verify_case(1, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = { -1, -1, 2, 5, 5 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 20; verify_case(2, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = { 2, 6, 8, 4, 1, 10, -1, -1, -1, -1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; int Arg2 = 17024000; verify_case(3, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_4() {
		int Arr0[] = { 1078451, -1, 21580110, 8284711, -1, 4202301, 3427559, 8261270, -1, 16176713,
			22915672, 24495540, 19236, 5477666, 12280316, 3305896, 17917887, 564911, 22190488, 21843923,
			23389728, 14641920, 9590140, 12909561, 20405638, 100184, 23336457, 12780498, 18859535, 23180993,
			10278898, 5753075, 21250919, 17563422, 10934412, 22557980, 24895749, 7593671, 10834579, 5606562 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 245243285; int Arg2 = 47225123; verify_case(4, Arg2, countTrees(Arg0, Arg1));
	}

	// END CUT HERE

};

// BEGIN CUT HERE  
int main() {
	SweetFruits ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE  
