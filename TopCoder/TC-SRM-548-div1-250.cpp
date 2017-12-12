// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndTrees.cpp"  
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
class KingdomAndTrees {
public:
	int Max(int a, int b) {
		return a > b ? a : b;
	}
	bool Check(vector<int> a, int x) {
		int i, j, b[100];
		memset(b, 0, sizeof b);
		for (i = 0; i < a.size(); i++) {
			int lb = i ? b[i - 1] : 0;
			if (lb < a[i]) b[i] = Max(a[i] - x, lb + 1);
			else if (lb + 1 > a[i] + x) return 0;
			else b[i] = lb + 1;
		}
		return 1;
	}
	int minLevel(vector <int> heights) {
		int L = 0, R = 1e9, Mid, Ans;
		while (L <= R) {
			Mid = L + R >> 1;
			if (Check(heights, Mid))
				R = (Ans = Mid) - 1;
			else
				L = Mid + 1;
		}
		return Ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {9, 5, 11}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, minLevel(Arg0)); }
	void test_case_1() { int Arr0[] = {5, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, minLevel(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, minLevel(Arg0)); }
	void test_case_3() { int Arr0[] = {548, 47, 58, 250, 2012}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 251; verify_case(3, Arg1, minLevel(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main() {
	KingdomAndTrees ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE  
