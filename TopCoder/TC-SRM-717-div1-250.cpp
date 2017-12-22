// BEGIN CUT HERE

// END CUT HERE
#line 5 "ScoresSequence.cpp"  
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
const int V = 3010;
struct Node {
	int w, id;
	Node(int w = 0, int id = 0) : w(w), id(id) {}
	friend bool operator < (const Node &a, const Node &b) {
		return a.w < b.w;
	}
} v[V];
int N, f[V][V];
class ScoresSequence {
public:
	int count(vector <int> s) {
		//$CARETPOSITION$  
		int i, j, k; N = s.size();
		for (i = 0; i < N; i++) {
			v[i + 1] = Node(s[i], i + 1);
		}
		memset(f, 0, sizeof f);
		for (i = 1; i <= N; i++) f[i][i] = 1;
		for (i = N; i; i--) {
			sort(v + 1, v + 1 + i);
			for (j = 1; j < i; j++) {
				if (v[i].w) v[i].w--, f[v[i].id][v[j].id] = 1;
				else v[j].w--, f[v[j].id][v[i].id] = 1;
			}
		}
		for (k = 1; k <= N; k++)
			for (i = 1; i <= N; i++)
				for (j = 1; j <= N; j++)
					f[i][j] |= f[i][k] & f[k][j];
		int Ret = 0;
		for (i = 1; i <= N; i++)
			for (j = 1; j <= N; j++)
				Ret += f[i][j];
		return Ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { int Arr0[] = {1, 0, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { int Arr0[] = {0, 2, 8, 4, 3, 9, 1, 5, 7, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 55; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { int Arr0[] = {22,20,14,13,17,15,12,18,23,15,21,26,33,5,19,9,37,0,25,28,4,12,35,32,25,7,31,6,2,29,10,33,36,27,39,28,40,3,8,38,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1422; verify_case(4, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main() {
	ScoresSequence ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE  
