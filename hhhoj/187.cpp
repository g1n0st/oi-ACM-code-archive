#include <bits/stdc++.h>
using namespace std;
const int V = 300010;
typedef pair<int, int> PI;
typedef pair<PI, PI> PII;
char get() {
	static char buf[V], *p1 = buf, *p2 = buf;
	if (p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, V, stdin);
		if (p1 == p2) return EOF;
	}
	return *p1++;
}
void Read(char *s, int &len) {
	len = 0; static char c;
	for (; !((c >= 'a' && c <= 'z') || c == '-'); c = get());
	for (; ((c >= 'a' && c <= 'z') || c == '-'); s[len++] = c, c = get());
}

vector<PII> ce[V];
vector<PI> dr[V]; int vis[V], pos[V];
int Ans;
namespace SAM {
	int len[V], fa[V], rt, pT;
	PI c[V][26];
	void Init() {
		rt = ++pT;
	}
	void link(int p, int f) {
		Ans += (len[p] - len[f]);
		fa[p] = f;
	}
	void cut(int x) {
		Ans -= (len[x] - len[fa[x]]);
		fa[x] = 0;
	}
	void Extend(int lst, int x, int id) {
		int cur = ++pT; len[cur] = len[lst] + 1;
		int p = lst;
		while (p && vis[c[p][x].first]) c[p][x].first = id, c[p][x].second = cur, p = fa[p];
		if (!p) link(cur, rt);
		else {
			int q = c[p][x].second;
			if (len[q] == len[p] + 1) link(cur, q);
			else {
				dr[id].push_back(PI(fa[q], q));
				++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
				memcpy(c[pT], c[q], sizeof c[q]);
				while (!vis[c[p][x].first] && c[p][x].second == q) {
					c[p][x].second = pT,
						ce[id].push_back(make_pair(PI(p, x), PI(q, pT)));
					p = fa[p];
				}
				link(pT, fa[q]); cut(q);
				link(q, pT); link(cur, pT);
			}
		}
		pos[id] = cur;
	}
	void Del(int x) {
		if (dr[x].size()) {
			int q = dr[x][0].second, p = dr[x][0].first;
			int pT = fa[q]; cut(q); cut(pos[x]); cut(pT); link(q, p);
			memcpy(c[pT], c[0], sizeof c[0]);
			for (auto v : ce[x]) c[v.first.first][v.first.second].second = v.second.first;
		}
		else cut(pos[x]);
		vis[x] = 1;
	}
}
char s[V];
int L, pre[V];
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j, now = 0;
	vis[0] = pos[0] = 1;
	Read(s + 1, L);  SAM::Init();
	for (int i = 1; i <= L; i++) {
		if (s[i] != '-') {
			pre[i] = now; now = i;
			SAM::Extend(pos[pre[i]], s[i] - 'a', i);
		}
		else {
			SAM::Del(now); now = pre[now];
		}
		printf("%d\n", Ans);
	}
	return 0;
}
