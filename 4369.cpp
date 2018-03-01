#include <bits/stdc++.h>
using namespace std;
const int V = 500010;
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
namespace SGT {
    const int N = V * 30;
    int ls[N], rs[N], sum[N], pT;
    namespace func {
        int rt[N];
        void Add(int &x, int y, int l, int r, int p) {
            x = ++pT; sum[x] = sum[y] + 1; ls[x] = ls[y]; rs[x] = rs[y];
            if (l == r) return; int mid = (l + r) >> 1;
            if (p <= mid) Add(ls[x], ls[y], l, mid, p); else Add(rs[x], rs[y], mid + 1, r, p);
        }
        int Query(int x, int y, int l, int r, int p) {
            if (l == r) return sum[y] - sum[x];
            int mid = (l + r) >> 1;
            if (p <= mid) return (sum[rs[y]] - sum[rs[x]]) + Query(ls[x], ls[y], l, mid, p);
            else return Query(rs[x], rs[y], mid + 1, r, p);
        }
        int Kth(int x, int y, int l, int r, int k) {
            if (l == r) return l;
            int mid = (l + r) >> 1;
            if (k <= sum[rs[y]] - sum[rs[x]]) return Kth(rs[x], rs[y], mid + 1, r, k);
            else return Kth(ls[x], ls[y], l, mid, k - (sum[rs[y]] - sum[rs[x]]));
        }
    }
}; using namespace SGT::func;
int n, Q, m, w[V];
vector<int> G[V];
int t, s[V], tot[V], h[V];
int chk() {
    t = 0;
    for (int i = 1; i <= m; i++) {
        while (t && h[t] < w[i]) --t;
        int cur = tot[t] + Query(rt[s[t]], rt[w[i]], 1, n, w[i]) - w[i];
        if (cur < 0) return 0;
        int curh;
        while ((curh = Kth(rt[s[t]], rt[w[i]], 1, n, cur - tot[t])) > h[t] && t) t--;
        ++t; s[t] = w[i]; h[t] = curh; tot[t] = cur;
    }
    return 1;
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(n);
    int a, b;
    for (int i = 1; i <= n; i++) {
        Read(a); Read(b);
        G[a].push_back(b);
    }
    for (int i = 1; i <= n; i++) {
        int pre = rt[i - 1], cur = pre;
        for (int j = 0; j < G[i].size(); j++) {
            Add(cur, pre, 1, n, G[i][j]); pre = cur;
        }
        rt[i] = cur;
    }
    Read(Q);
    while (Q--) {
        Read(m); SGT::pT = 0;
        for (int i = 1; i <= m; i++) Read(w[i]);
        sort(w + 1, w + 1 + m);
        putchar('0' + chk()); putchar('\n');
    }
    return 0;
}
