#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 200010;
char get() {
    static char buf[V], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, V, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}
void Read(int &x) {
    x = 0; static char c;
    for (; !isdigit(c); c = get());
    for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
void Read(char *s, int &len) {
    len = 0; static char c;
    for (; !islower(c); c = get());
    for (; islower(c); s[len++] = c, c = get()); s[len] = 0;
}
string str[V];
char s[V];
int N, K, L[V];
int head[V], sub;
struct Edge {
    int to, nxt;
    Edge(int to = 0, int nxt = 0) : to(to), nxt(nxt) {}
} edge[V];
void Add(int a, int b) {
    edge[++sub] = Edge(b, head[a]); head[a] = sub;
}
namespace SAM {
    set<int> S[V];
    int c[V][26], fa[V], len[V], tot[V], lst, pT, rt;
    void Init() {
        rt = lst = ++pT;
    }
    void reset() {
        lst = rt;
    }
    void Extend(int x, int id) {
        int cur = ++pT;
        len[cur] = len[lst] + 1; S[cur].insert(id);
        int p = lst;
        while (p && !c[p][x]) c[p][x] = cur, p = fa[p];
        if (!p) fa[cur] = rt;
        else {
            int q = c[p][x];
            if (len[q] == len[p] + 1) fa[cur] = q;
            else {
                ++pT; len[pT] = len[p] + 1; fa[pT] = fa[q];
                memcpy(c[pT], c[q], sizeof c[q]);
                while (c[p][x] == q) c[p][x] = pT, p = fa[p];
                fa[q] = fa[cur] = pT;
            }
        }
        lst = cur;
    }
    void Dfs(int u) {
        for (int i = head[u], v; i; i = edge[i].nxt) {
            v = edge[i].to; Dfs(v);
            if (S[v].size() > S[u].size()) swap(S[v], S[u]);
            for (set<int>::iterator it = S[v].begin(); it != S[v].end(); ++it) S[u].insert(*it);
            S[v].clear();
        }
        tot[u] = S[u].size();
    }
    void Work() {
        for (int i = 2; i <= pT; i++) Add(fa[i], i);
        Dfs(rt);
    }
    void Deal(const char *s, int l) {
        int p = rt; LL ans = 0;
        for (int i = 0; i < l; i++) {
            p = c[p][s[i] - 'a'];
            while (p && tot[p] < K) p = fa[p];
            ans += len[p];
        }
        printf("%lld ", ans);
    }
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("a.txt", "w", stdout);
    Read(N); Read(K); SAM::Init();
    for (int i = 1; i <= N; i++) {
        Read(s + 1, L[i]); SAM::reset();
        for (int j = 1; j <= L[i]; j++) SAM::Extend(s[j] - 'a', i);
        str[i] = (s + 1);
    }
    SAM::Work();
    for (int i = 1; i <= N; i++) SAM::Deal(str[i].c_str(), L[i]);
    return 0;
}
