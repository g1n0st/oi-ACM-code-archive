// BEGIN CUT HERE

// END CUT HERE
#line 5 "StringWeight.cpp"  
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
class StringWeight {
public:
	vector<int> L;
	int f[100][30][30];
	int Dp(int i, int fr, int ue) {
		int &r = f[i][fr][ue];
		if (~r) return r;
		r = 1000000;
		if (i == L.size()) return ue == 0 ? r = 0 : r;
		int s = 0;
		for (int j = 0; j < i; j++) s += L[j];
		int m = min(L[i], 26);
		for (int c = 0; c <= ue && c <= m; c++) // end in L[i]
			for (int p = 0; p <= fr && p + c <= m; p++) // start in L[i]
				for (int u = 0; u + c <= ue && p + u + c <= m; u++) { // L[i] belong
					int k = m - u - p - c;
					if (k + p > fr) continue;
					int w = Dp(i + 1, fr - k - p, ue - c + p);
					w += (c - p) * s - (L[i] - 1) * p;
					w += p * (p - 1) / 2 + c * (c - 1) / 2;
					if (!u) w += L[i] - c - p - k;
					r = min(w, r);
				}
		return r;
	}
	int getMinimum(vector <int> L) {
		//$CARETPOSITION$
		this->L = L;
		memset(f, -1, sizeof f);
		return Dp(0, 26, 0);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, getMinimum(Arg0)); }
	void test_case_1() { int Arr0[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, getMinimum(Arg0)); }
	void test_case_2() { int Arr0[] = {26, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(2, Arg1, getMinimum(Arg0)); }
	void test_case_3() { int Arr0[] = {25, 25, 25, 25}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1826; verify_case(3, Arg1, getMinimum(Arg0)); }
	void test_case_4() { int Arr0[] = {14, 6, 30, 2, 5, 61}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1229; verify_case(4, Arg1, getMinimum(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main() {
	StringWeight ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE  
