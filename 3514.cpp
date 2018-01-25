#include <bits/stdc++.h>
using namespace std;
const int V = 400010;
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
    for (; !(c >= '0' && c <= '9'); c = get());
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int rt[V];
namespace SGT {
    int ls[V * 50], rs[V * 50], sum[V * 50], pT;
    void Add(int &x, int y, int l, int r, int p) {
        x = ++pT; ls[x] = ls[y]; rs[x] = rs[y]; sum[x] = sum[y] + 1;
        if (l == r) return;
        int Mid = (l + r) >> 1;
        if (p <= Mid) Add(ls[x], ls[y], l, Mid, p); else Add(rs[x], rs[y], Mid + 1, r, p);
    }
    int Query(int x, int y, int l, int r, int p) {
        if (r == p) return sum[y] - sum[x];
        int Mid = (l + r) >> 1;
        if (p <= Mid) return Query(ls[x], ls[y], l, Mid, p);
        else return sum[ls[y]] - sum[ls[x]] + Query(rs[x], rs[y], Mid + 1, r, p);
    }
}
int val[V], mn[V];
namespace LCT {
    int c[V][2], fa[V], rev[V];
    int Rt(int x) {
        return c[fa[x]][0] != x && c[fa[x]][1] != x;
    }
    void pushDown(int x) {
        int &l = c[x][0], &r = c[x][1];
        if (rev[x]) {
            rev[l] ^= 1; rev[r] ^= 1; rev[x] ^= 1; swap(l, r);
        }
    }
    void pushUp(int x) {
        int l = c[x][0], r = c[x][1];
        mn[x] = x;
        if (val[mn[l]] < val[mn[x]]) mn[x] = mn[l];
        if (val[mn[r]] < val[mn[x]]) mn[x] = mn[r];
    }
    void rotate(int x) {
        int y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
        if (!Rt(y)) {
            if (c[z][0] == y) c[z][0] = x;
            else c[z][1] = x;
        }
        fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
        c[y][l] = c[x][r]; c[x][r] = y;
        pushUp(y); pushUp(x);
    }
    int s[V], t;
    void splay(int x) {
        s[t = 1] = x;
        for (int i = x; !Rt(i); i = fa[i]) s[++t] = fa[i];
        while (t) pushDown(s[t--]);
        while (!Rt(x)) {
            int y = fa[x], z = fa[y];
            if (!Rt(y)) {
                if ((c[z][0] == y) ^ (c[y][0] == x)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
    void access(int x) {
        for (int t = 0; x; t = x, x = fa[x]) {
            splay(x); c[x][1] = t; pushUp(x);
        }
    }
    void rever(int x) {
        access(x); splay(x); rev[x] ^= 1;
    }
    void link(int x, int y) {
        rever(x); fa[x] = y;
    }
    void cut(int x, int y) {
        rever(x); access(y); splay(y);
        c[y][0] = fa[x] = 0;
    }
    int find(int x) {
        access(x); splay(x);
        while (c[x][0]) x = c[x][0];
        return x;
    }
    int query(int x, int y) {
        rever(x); access(y); splay(y); return mn[y];
    }
}
int ntr[V];
int N, M, K, Type, u[V], v[V], pT;
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("a.txt", "w", stdout);
    int i, j;
    Read(N); Read(M); Read(K); Read(Type);
    pT = N;
    for (i = 0; i <= N; i++) {
        mn[i] = i; val[i] = 1 << 30;
    }
    for (i = 1; i <= M; i++) {
        Read(u[i]); Read(v[i]);
    }
    for (i = 1; i <= M; i++) {
        if (u[i] == v[i]) {
            ntr[i] = i; continue;
        }
        if (LCT::find(u[i]) == LCT::find(v[i])) {
            int t = LCT::query(u[i], v[i]); ntr[i] = val[t];
            LCT::cut(u[i], t); LCT::cut(v[i], t);
        }
        ++pT; mn[pT] = pT; val[pT] = i;
        LCT::link(u[i], pT); LCT::link(v[i], pT);
    }
    for (i = 1; i <= M; i++)
        SGT::Add(rt[i], rt[i - 1], 0, M, ntr[i]);
 
    int l, r, lstAns = 0;
    while (K--) {
        Read(l); Read(r);
        if (Type) {
            l ^= lstAns; r ^= lstAns;
        }
        lstAns = N - SGT::Query(rt[l - 1], rt[r], 0, M, l - 1);
        printf("%d\n", lstAns);
    }
    return 0;
}
