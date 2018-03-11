#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1000010;
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
struct PI {
    int l, r;
    friend bool operator < (const PI &a, const PI &b) {
        return a.l == b.l ? a.r < b.r : a.l < b.l;
    }
};
PI a[V], g[V]; int n, tot;
LL ans;
LL Get(PI a, PI b) {
    return a.r < b.l ? 0 : (LL)(b.r - a.l) * (a.r - b.l);
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(n);
    for (int i = 1; i <= n; i++) {
        Read(a[i].l); Read(a[i].r);
    }
    sort(a + 1, a + 1 + n);
    int mx = 0, lst = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i].r <= mx) 
            ans = max(ans, (LL)(a[i].r - a[i].l) * (a[lst].r - a[lst].l));
        else {
            mx = a[i].r; lst = i; g[++tot] = a[i];
        }
    }
    for (int i = 1, j = 2; i < tot; i++) {
        if (i == j) ++j;
        while (j < tot && Get(g[i], g[j]) < Get(g[i], g[j + 1])) ++j;
        ans = max(ans, Get(g[i], g[j]));
    }
    printf("%lld\n", ans);
    return 0;
}
