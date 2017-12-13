// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomMap.cpp"  
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
const int INF = 0x3f3f3f3f;
bool cmp(int x, int y) {
	return x > y;
}
class KingdomMap {
public:
	int c[V][V], N, h[V][3], vis[V], g[V], f[V];
	int Min(int a, int b) {
		return a < b ? a : b;
	}
	void Dfs(int u, int fa) {
		vis[u] = 1;
		for (int v = 0; v < N; v++) {
			if (!c[u][v] || fa == v) continue;
			Dfs(v, u);
		}
		f[u] = 0;
		for (int v = 0; v < N; v++) {
			if (!c[u][v] || fa == v) continue;
			f[u] += Min(f[v], Min(g[v], h[v][2])) + 1;
		}
		int sub = INF;
		for (int v = 0; v < N; v++) {
			if (!c[u][v] || fa == v) continue;
			sub = Min(sub, -Min(f[v], Min(g[v], h[v][2])) - 1 + Min(f[v], h[v][2]));
		}
		g[u] = f[u] + sub;
		for (int k = 0; k < 3; k++) {
			int tmp[] = { INF, INF, INF, INF };
			h[u][k] = 0;
			for (int v = 0; v < N; v++) {
				if (!c[u][v] || fa == v) continue;
				int t = Min(f[v], Min(g[v], h[v][2]) + 1);
				h[u][k] += t;
				tmp[3] = -t + Min(f[v], h[v][1]);
				push_heap(tmp, tmp + 4, cmp);
			}
			for (int i = 0; i < k; i++) h[u][k] += tmp[i];
			if (k) h[u][k] = Min(h[u][k], h[u][k - 1]);
		}
	}
	int Calc() {
		memset(vis, 0, sizeof vis);
		int Ret = 0;
		for (int i = 0; i < N; i++) {
			if (vis[i]) continue;
			Dfs(i, -1); Ret += Min(f[i], Min(g[i], h[i][2]));
		}
		return Ret;
	}
	vector <int> getRoadsToRemove(int n, vector <string> roads) {
		memset(c, 0, sizeof c);
		string S = accumulate(roads.begin(), roads.end(), string());
		replace(S.begin(), S.end(), ',', ' ');
		istringstream sin(S); this->N = n;
		int x, y;
		while (sin >> x >> y) {
			c[x][y] = c[y][x] = 1;
		}
		int K = Calc(), mark = 0;
		vector<int> Ans;
		istringstream Sin(S);
		while (K > 0 && Sin >> x >> y) {
			c[x][y] = c[y][x] = 0;
			if (K && Calc() == K - 1) {
				Ans.push_back(mark); K--;
			}
			else c[x][y] = c[y][x] = 1;
			mark++;
		}
		return Ans;
		//$CARETPOSITION$  
	}

	// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 5; string Arr1[] = { "0 1,1 2,2 3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[1] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getRoadsToRemove(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 7; string Arr1[] = { "0 1,1 2,2 3,3 4,5 6,2 5" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, getRoadsToRemove(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 20; string Arr1[] = { "8 17,9 12,4 7,2 7,2 19,3 12,6 12,1 9,5 18,0 12,6 1", "6,0 11,3 14,10 15,12 13,13 18,13 19,15 17,15 19" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1, 3, 5, 14 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, getRoadsToRemove(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1; string Arr1[1] = {}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[1] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, getRoadsToRemove(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE  
int main() {
	KingdomMap ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE  
