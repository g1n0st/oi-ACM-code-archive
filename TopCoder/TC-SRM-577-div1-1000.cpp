// BEGIN CUT HERE

// END CUT HERE
#line 5 "BoardPainting.cpp"  
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
#include <queue>
using namespace std;

const int INF = 1 << 30;
namespace Net {
	const int N = 10010;
	const int M = 500100;
	int S, T;
	int head[N], sub;
	struct Edge {
		int to, nxt, v;
		Edge() {}
		Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
	} edge[M];
	void Add(int a, int b, int v) {
		edge[++sub] = Edge(b, head[a], v); head[a] = sub;
	}
	void Link(int a, int b, int v) {
		Add(a, b, v); Add(b, a, 0);
	}
	void Init() {
		memset(head, 0, sizeof head); sub = 1;
	}
	int h[N];
	bool bfs() {
		queue<int> qu; qu.push(S);
		memset(h, -1, sizeof h); h[S] = 0;
		while (!qu.empty()) {
			int u = qu.front(); qu.pop();
			for (int i = head[u], v; i; i = edge[i].nxt) {
				v = edge[i].to; if (~h[v] || !edge[i].v) continue;
				h[v] = h[u] + 1; qu.push(v);
			}
		}
		return ~h[T];
	}
	int Dfs(int u, int flow) {
		if (u == T) return flow;
		int used = 0, w;
		for (int i = head[u], v; i; i = edge[i].nxt) {
			v = edge[i].to; if (h[v] != h[u] + 1) continue;
			w = Dfs(v, min(edge[i].v, flow - used));
			used += w; edge[i].v -= w; edge[i ^ 1].v += w;
			if (used == flow) return used;
		}
		if (!used) h[u] = -1;
		return used;
	}
	int Dinic() {
		int r = 0;
		while (bfs()) r += Dfs(S, INF);
		return r;
	}
}
const int V = 210;
const int sx[] = { 1, 0, -1, 0 };
const int sy[] = { 0, 1, 0, -1 };
class BoardPainting {
public:
	int N, M, id[V][V], pT;
	char v[V][V];
	int minimalSteps(vector <string> target) {
		//$CARETPOSITION$ 
		int i, j, k;
		N = target.size(); M = target[0].size();
		for (i = 0; i < N; i++)
			for (j = 0; j < M; j++)
				v[i + 1][j + 1] = target[i][j];
		pT = 0; Net::Init();
		for (i = 1; i <= N; i++)
			for (j = 1; j <= M; j++)
				if (v[i][j] == '#') id[i][j] = ++pT;
		Net::S = ++pT; Net::T = ++pT;
		for (i = 1; i <= N; i++)
			for (j = 1; j <= M; j++) if (v[i][j] == '#')
				for (k = 0; k < 4; k++) {
					int x = i + sx[k], y = j + sy[k];
					if (v[x][y] == '#') Net::Link(id[i][j], id[x][y], 1);
					else {
						if (k & 1) Net::Link(Net::S, id[i][j], 1);
						else Net::Link(id[i][j], Net::T, 1);
					}
				}
		return Net::Dinic() / 2;
	}

	// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { "#####" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, minimalSteps(Arg0)); }
	void test_case_1() {
		string Arr0[] = { "#####",
			".....",
			"#####",
			".....",
			"#####" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, minimalSteps(Arg0));
	}
	void test_case_2() {
		string Arr0[] = { "..#..",
			"..#..",
			"#####",
			"..#..",
			"..#.." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, minimalSteps(Arg0));
	}
	void test_case_3() {
		string Arr0[] = { "#####",
			"..#..",
			"#####",
			"..#..",
			"#####" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(3, Arg1, minimalSteps(Arg0));
	}
	void test_case_4() {
		string Arr0[] = { ".#.#.",
			"#####",
			".#.#.",
			"#####",
			".#.#." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(4, Arg1, minimalSteps(Arg0));
	}
	void test_case_5() {
		string Arr0[] = { ".##.####.####.#########.##..",
			"##.#.####################.##",
			".##.###.##.###.###.###.###..",
			"#..###..#########..###.##.##",
			"####..#######.#.#####.######",
			"##.######.#..#.#############",
			"##.######.###########.######",
			"#######.#######.#..###.#.###",
			"#####..#######.#####.#.###.#",
			"#..#################.#.####.",
			"##.######..#.#####.######.##",
			"..#.#############.#.##....#.",
			"....##..##..#.#####.#.###.##",
			"##.#########...#..#.#.######",
			"##.#..###########..#..####.#",
			"#.####.###.########.########",
			"#####.#########.##.##.######",
			".##.####..###.###...######.#" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 88; verify_case(5, Arg1, minimalSteps(Arg0));
	}
	void test_case_6() { string Arr0[] = { "...................." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(6, Arg1, minimalSteps(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE  
int main() {
	BoardPainting ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE  
