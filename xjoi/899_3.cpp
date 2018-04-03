#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
typedef long long LL;
const int V = 200010;
inline char get() {
    static char buf[V], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, V, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}
inline void Read(int &x) {
    x = 0; static char c;
    for (; !isdigit(c); c = get());
    for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
 
int n, n2;
 
namespace SGT {
    int tag[V << 3], val[V << 3];
    void Clear() {
        val[1] = 0; tag[1] = 1;
    }
    void Add(int p, int v) {
        int l = 1, r = n2, o = 1, mid;
        while (1) {
            val[o] += v; if (l == r) return;
            if (tag[o]) {
                tag[o << 1] = 1; tag[o << 1 | 1] = 1;
                val[o << 1] = 0; val[o << 1 | 1] = 0;
                tag[o] = 0;
            }
            mid = (l + r) >> 1;
            if (p <= mid) o = (o << 1), r = mid;
            else o = (o << 1 | 1), l = mid + 1;
        }
    }
    int Query(int p) {
        int res = 0;
        int l = 1, r = n2, o = 1, mid;
        while (1) {
            if (l == p) {
                res += val[o]; break;
            }
            if (tag[o]) {
                tag[o << 1] = 1; tag[o << 1 | 1] = 1;
                val[o << 1] = 0; val[o << 1 | 1] = 0;
                tag[o] = 0;
            }
            mid = (l + r) >> 1;
            if (p <= mid) {
                res += val[o << 1 | 1]; o = (o << 1); r = mid;
            } else {
                o = (o << 1 | 1); l = mid + 1;
            }
        }
        return res;
    }
}
 
struct pi {
    int l, r;
    pi(int l = 0, int r = 0) : l(l), r(r) {}
    friend inline pi operator + (const pi &a, const pi &b) {
        if (a.r < b.l || b.r < a.l) return pi();
        else return pi(max(a.l, b.l), min(a.r, b.r));
    }
    friend inline bool operator == (const pi &a, const pi &b) {
        return a.l == b.l && a.r == b.r;
    }
    friend inline bool operator < (const pi &a, const pi &b) {
        return a.l == b.l ? a.r < b.r : a.l < b.l;
    }
};
int head[V], sub;
struct Edge {
    int to, nxt; pi v;
    Edge() {}
    Edge(int to, int nxt, int L, int R) :
        to(to), nxt(nxt), v(pi(L, R)) {
        }
} edge[V << 1];
 
void Add(int a, int b, int L, int R) {
    edge[++sub] = Edge(b, head[a], L, R); head[a] = sub;
}
 
int rt, son[V], siz[V], vis[V], S;
void getroot(int u, int fa) {
    siz[u] = 1; son[u] = 0;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (v == fa || vis[v]) continue;
        getroot(v, u); siz[u] += siz[v]; son[u] = max(son[u], siz[v]);
    }
    son[u] = max(son[u], S - siz[u]);
    if (son[u] < son[rt]) rt = u;
}
 
LL ans;
 
int t1, t2;
pi s1[V], s2[V];
 
void dfs(int u, int fa, pi val) {
    if (!val.l) return ;
    s1[++t1] = val; s2[++t2] = val; ans++;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (v == fa || vis[v]) continue;
        dfs(v, u, val + edge[i].v);
    }
}
void calc(pi *s, int t, int f) {
    SGT::Clear();
    sort(s + 1, s + 1 + t);
    int tot = 0, lst = 0;
    for (int i = 1; i <= t; i++) {
        if (s[i] == s[lst]) tot++;
        else {
            if (i > 1) SGT::Add(s[i - 1].r, tot);
            ans += ((LL)tot * (tot - 1) >> 1) * f;
            tot = 1; lst = i;
        }
        ans += SGT::Query(s[i].l) * f;
    }
    ans += ((LL)tot * (tot - 1) >> 1) * f;
}
void solve(int u) {
    vis[u] = 1;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (vis[v]) continue;
        t1 = 0; dfs(v, u, edge[i].v); calc(s1, t1, -1);
    }
    calc(s2, t2, 1); t2 = 0;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to; if (vis[v]) continue;
        rt = 0; S = siz[v];
        getroot(v, u);
        solve(rt);
    }
}
int u[V], v[V], L[V], R[V];
 
int G[V << 1], tot;
inline int sc(int x) {
    int l = 1, r = tot, mid = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (x == G[mid]) return mid;
        if (x < G[mid]) r = mid;
        else l = mid;
    }
    return mid;
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("a.txt", "w", stdout);
    Read(n);
    for (int i = 1; i < n; i++) {
        Read(u[i]); Read(v[i]); Read(L[i]); Read(R[i]);
        G[++tot] = L[i]; G[++tot] = R[i];
    }
    sort(G + 1, G + 1 + tot); tot = unique(G + 1, G + 1 + tot) - G;
    for (int i = 1; i < n; i++) {
        L[i] = sc(L[i]); R[i] = sc(R[i]);
        //L[i] = lower_bound(G + 1, G + 1 + tot, L[i]) - G;
        //R[i] = lower_bound(G + 1, G + 1 + tot, R[i]) - G;
        Add(u[i], v[i], L[i], R[i]); Add(v[i], u[i], L[i], R[i]);
    }
     
    n2 = tot;
    S = son[0] = n; getroot(1, 0);
    solve(rt);
     
    cout << ans << endl;
    return 0;
}
