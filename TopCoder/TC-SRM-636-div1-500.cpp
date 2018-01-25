// BEGIN CUT HERE

// END CUT HERE
#line 5 "ClosestRabbit.cpp"  
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
const int V = 510;
class ClosestRabbit {
public:
	double C[V][V]; int x[V], y[V], tot, d[V][V];
	int Dist(int a, int b) {
		return (x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]);
	}
	void Pre(int n) {
		memset(C, 0, sizeof C);
		C[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			C[i][0] = 1;
			for (int j = 1; j <= i; j++)
				C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
	double getExpected(vector <string> board, int r) {
		tot = 0;
		for (int i = 0; i < board.size(); i++)
			for (int j = 0; j < board[i].size(); j++)
				if (board[i][j] == '.') {
					++tot; x[tot] = i; y[tot] = j;
				}
		for (int i = 1; i <= tot; i++)
			for (int j = 1; j <= tot; j++)
				d[i][j] = Dist(i, j);
		Pre(tot);
		double R = 0;
		for (int i = 1; i <= tot; i++)
			for (int j = i + 1; j <= tot; j++) {
				int b = 0;
				for (int k = 1; k <= tot; k++) {
					if ((k == i) || (k == j)) continue;
					else if (d[k][i] < d[j][i] ||
						(d[k][i] == d[j][i] && x[k] < x[j]) ||
						(d[k][i] == d[j][i] && x[k] == x[j] && y[k] < y[j])) b++;
					else if (d[k][j] < d[i][j] ||
						(d[k][j] == d[i][j] && x[k] < x[i]) ||
						(d[k][j] == d[i][j] && x[k] == x[i] && y[k] < y[i])) b++;
				}
				R += C[tot - 2 - b][r - 2] / C[tot][r];
			}
		return R;
	}

	// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { ".#.#." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; double Arg2 = 1.0; verify_case(0, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_1() {
		string Arr0[] = { "..###.",
			".###.#" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; double Arg2 = 1.6; verify_case(1, Arg2, getExpected(Arg0, Arg1));
	}
	void test_case_2() {
		string Arr0[] = { "..###.",
			".###.#" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; double Arg2 = 2.0; verify_case(2, Arg2, getExpected(Arg0, Arg1));
	}
	void test_case_3() {
		string Arr0[] = { ".....",
			"#...." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; double Arg2 = 1.253968253968254; verify_case(3, Arg2, getExpected(Arg0, Arg1));
	}
	void test_case_4() {
		string Arr0[] = { ".#####.#####..#....#",
			"#......#....#.##..##",
			".####..#####..#.##.#",
			".....#.#...#..#....#",
			"#####..#....#.#....#" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 19; double Arg2 = 5.77311527122319; verify_case(4, Arg2, getExpected(Arg0, Arg1));
	}

	// END CUT HERE

};

// BEGIN CUT HERE  
int main() {
	ClosestRabbit ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE  
