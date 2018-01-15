#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
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
    for (; !(c >= 'a' && c <= 'z'); c = get());
    for (; c >= '0' && c <= 'z'; s[len++] = c, c = get());
}
struct Seg {
    int tag[V << 2], mn[V << 2];
    void Build(int o, int l, int r) {
        tag[o] = 1 << 30; mn[o] = 1 << 30;
        if (l == r) return;
        int Mid = (l + r) >> 1;
        Build(o << 1, l, Mid); Build(o << 1 | 1, Mid + 1, r);
    }
    void setv(int o, int v) {
        tag[o] = min(tag[o], v); mn[o] = min(mn[o], v);
    }
    void pushDown(int o) {
        if (tag[o] != 1 << 30) {
            setv(o << 1, tag[o]); setv(o << 1 | 1, tag[o]);
            tag[o] = 1 << 30;
        }
    }
    void Modify(int o, int l, int r, int L, int R, int x) {
        if (l == L && r == R) {
            setv(o, x); return;
        }
        int Mid = (l + r) >> 1; pushDown(o);
        if (R <= Mid) Modify(o << 1, l, Mid, L, R, x); else if (Mid < L) Modify(o << 1 | 1, Mid + 1, r, L, R, x);
        else Modify(o << 1, l, Mid, L, Mid, x), Modify(o << 1 | 1, Mid + 1, r, Mid + 1, R, x);
        mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
    }
    int Query(int o, int l, int r, int p) {
        if (l == r) return mn[o];
        int Mid = (l + r) >> 1; pushDown(o);
        if (p <= Mid) return Query(o << 1, l, Mid, p); else return Query(o << 1 | 1, Mid + 1, r, p);
    }
} t1, t2;
namespace SAM {
    int c[V * 2][26], len[V * 2], fa[V * 2], val[V * 2], pT, rt, lst;
    void Init() {
        rt = lst = ++pT;
    }
    void Extend(int x) {
        int cur = ++pT;
        len[cur] = len[lst] + 1; val[cur] = 1;
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
                fa[cur] = fa[q] = pT;
            }
        }
        lst = cur;
    }
    void Work(int n) {
        int i, j;
        for (i = 1; i <= pT; i++)
            if (fa[i]) val[fa[i]] = 0;
        for (i = 1; i <= pT; i++) {
            if (!val[i]) continue;
            int l = len[i] - len[fa[i]], r = len[i];
            t1.Modify(1, 1, n, l, r, r - l + 1);
            if (l > 1) t2.Modify(1, 1, n, 1, l - 1, r);
        }
        for (i = 1; i <= n; i++) {
            int v1 = t1.Query(1, 1, n, i);
            int v2 = t2.Query(1, 1, n, i) - i + 1;
            printf("%d\n", min(v1, v2));
        }
    }
}
char s[V]; int n;
int main() {
    int i, j;
    Read(s, n); SAM::Init();
    t1.Build(1, 1, n);
    t2.Build(1, 1, n);
    for (i = 0; i < n; i++) SAM::Extend(s[i] - 'a');
    SAM::Work(n);
    return 0;
}
