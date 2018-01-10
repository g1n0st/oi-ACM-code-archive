// BEGIN CUT HERE

// END CUT HERE
#line 5 "YetAnotherORProblem2.cpp"  
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
const int P = 1000000009;
class YetAnotherORProblem2 {
public:
	void Add(int &x, int y) {
		(x += y) %= P;
	}
	int f[100][100], N, R;
	int Dfs(int u, int eq) {
		int &r = f[u][eq];
		if (~r) return r;
		if (!u) return r = 1; r = 0;
		int p = u - 1;
		if (eq == N) {
			if (R & (1 << p)) {
				Add(r, 1LL * N * Dfs(u - 1, 1) % P);
				Add(r, Dfs(u - 1, 0));
			}
			else Add(r, Dfs(u - 1, N));
		}
		if (eq == 1) {
			if (R & (1 << p)) {
				Add(r, Dfs(u - 1, 1));
				Add(r, 1LL * (N - 1) * Dfs(u - 1, 0) % P);
				Add(r, Dfs(u - 1, 0));
			} else {
				Add(r, Dfs(u - 1, 1));
				Add(r, 1LL * (N - 1) * Dfs(u - 1, 1) % P);
			}
		}
		if (!eq) {
			Add(r, Dfs(u - 1, 0));
			Add(r, 1LL * N * Dfs(u - 1, 0) % P);
		}
		return r;
	}
	int countSequences(int N, int R) {
		//$CARETPOSITION$  
		memset(f, -1, sizeof f);
		this->N = N; this->R = R;
		return Dfs(30, N);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 7; verify_case(0, Arg2, countSequences(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 9; verify_case(1, Arg2, countSequences(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 16; verify_case(2, Arg2, countSequences(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 1023; int Arg2 = 73741815; verify_case(3, Arg2, countSequences(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main() {
	YetAnotherORProblem2 ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE  
