#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int V = 1000010;
DB fac[14];
struct Data {
    DB key[14], sum[14];
    void Set(int x, DB a, DB b) {
        DB s[] = { sin(b), cos(b), -sin(b), -cos(b) };
        memset(key, 0, sizeof key); DB f = 1;
        switch (x) {
        case 1:
            for (int i = 0; i < 14; i++) {
                key[i] = s[i % 4] * f; f *= a;
            } break;
        case 2:
            for (int i = 0; i < 14; i++) {
                key[i] = exp(b) * f; f *= a;
            } break;
        case 3:
            key[0] = b; key[1] = a; break;
        }
    }
    DB Val(DB x) {
        DB r = 0, f = 1;
        for (int i = 0; i < 14; i++) {
            r += f * sum[i] / fac[i]; f *= x;
        }
        return r;
    }
};
namespace LCT {
    int fa[V], c[V][2], st[V], top, nxt[V], rev[V];
    Data dat[V];
    void pushDown(int x) {
        int &l = c[x][0], &r = c[x][1];
        if (rev[x]) {
            rev[l] ^= 1; rev[r] ^= 1; rev[x] ^= 1; swap(l, r);
        }
    }
    void pushUp(int x) {
        int l = c[x][0], r = c[x][1];
        for (int i = 0; i < 14; i++)
            dat[x].sum[i] = dat[x].key[i] + dat[l].sum[i] + dat[r].sum[i];
    }
    inline bool Rt(int x) {
        return c[fa[x]][0] != x && c[fa[x]][1] != x;
    }
    inline void rotate(int x) {
        int y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
        if (!Rt(y)) {
            if (c[z][0] == y) c[z][0] = x;
            else c[z][1] = x;
        }
        fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
        c[y][l] = c[x][r]; c[x][r] = y;
        pushUp(y), pushUp(x);
    }
 
    inline void splay(int x) {
        st[++top] = x;
        for (int i = x; !Rt(i); i = fa[i]) st[++top] = fa[i];
        while (top) pushDown(st[top--]);
        while (!Rt(x)) {
            int y = fa[x], z = fa[y];
            if (!Rt(y)) {
                if ((c[y][0] == x) ^ (c[z][0] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
 
    inline void access(int x) {
        for (int t = 0; x; t = x, x = fa[x])
            splay(x), c[x][1] = t, pushUp(x);
    }
    inline void makeroot(int x) {
        access(x), splay(x), rev[x] ^= 1;
    }
    inline void link(int x, int y) {
        makeroot(x), fa[x] = y;
    }
    inline void cut(int x, int y) {
        makeroot(x); access(y), splay(y);
        if (c[y][0] == x) c[y][0] = fa[x] = 0; pushUp(y);
    }
    void set(int x, int f, DB a, DB b) {
        makeroot(x); dat[x].Set(f, a, b); pushUp(x);
    }
    DB query(int x, int y, DB v) {
        makeroot(x);  access(y);  splay(y);
        return dat[y].Val(v);
    }
    int sRt(int x, int y) {
        while (fa[x]) x = fa[x];
        while (fa[y]) y = fa[y];
        return x == y;
    }
}
int N, M;
int main() {
    int i, j, f; DB a, b;
    char op[20]; int x, y;
    scanf("%d%d", &N, &M); scanf("%s", op);
    fac[0] = 1; for (i = 1; i < 14; i++) fac[i] = fac[i - 1] * i;
    for (i = 1; i <= N; i++) {
        scanf("%d%lf%lf", &f, &a, &b); LCT::set(i, f, a, b);
    }
    while (M--) {
        scanf("%s%d%d", op, &x, &y); x++; y++; if (op[0] == 'm') y--;
        switch (op[0]) {
        case 'a': LCT::link(x, y); break;
        case 'd': LCT::cut(x, y); break;
        case 'm': scanf("%lf%lf", &a, &b); LCT::set(x, y, a, b); break;
        case 't':
            scanf("%lf", &a);
            if (!LCT::sRt(x, y)) puts("unreachable");
            else printf("%.8e\n", LCT::query(x, y, a));
        }
    }
    return 0;
}
