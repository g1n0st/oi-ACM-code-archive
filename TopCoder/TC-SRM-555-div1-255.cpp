// BEGIN CUT HERE

// END CUT HERE
#line 5 "CuttingBitString.cpp"  
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
const int V = 110;
typedef long long LL;
class CuttingBitString {
public:
	int f[V], a[V], N;
	int Min(int a, int b) {
		return a < b ? a : b;
	}
	int getmin(string S) {
		//$CARETPOSITION$  
		int i, j, k;
		for (i = 0; i < S.size(); i++) 
			a[i + 1] = S[i] - '0';
		N = S.size();
		f[0] = 0;
		for (i = 1; i <= N; i++) {
			f[i] = 1 << 30;
			for (j = 0; j < i; j++) {
				LL Now = 0; if (!a[j + 1]) continue;
				for (k = j + 1; k <= i; k++) {
					Now = (Now * 2 + a[k]);
				}
				while (Now && Now % 5 == 0) Now /= 5;
				if (Now == 1) f[i] = Min(f[i], f[j] + 1);
			}
		}
		if (f[N] == 1 << 30) return -1;
		return f[N];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "101101101"; int Arg1 = 3; verify_case(0, Arg1, getmin(Arg0)); }
	void test_case_1() { string Arg0 = "1111101"; int Arg1 = 1; verify_case(1, Arg1, getmin(Arg0)); }
	void test_case_2() { string Arg0 = "00000"; int Arg1 = -1; verify_case(2, Arg1, getmin(Arg0)); }
	void test_case_3() { string Arg0 = "110011011"; int Arg1 = 3; verify_case(3, Arg1, getmin(Arg0)); }
	void test_case_4() { string Arg0 = "1000101011"; int Arg1 = -1; verify_case(4, Arg1, getmin(Arg0)); }
	void test_case_5() { string Arg0 = "111011100110101100101110111"; int Arg1 = 5; verify_case(5, Arg1, getmin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main() {
	CuttingBitString ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE  
