#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
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
    while (c > '9' || c < '0') c = get();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = get();
    }
}
  
int Ans1[V * 10], Ans2[V * 10];
int block[V], N, M, B, a[V];
  
struct T {
    int t[V];
    int lowbit(int x) {
        return x & (-x);
    }
    void Add(int x, int v) {
        while (x <= N) {
            t[x] += v;
            x += lowbit(x);
        }
    }
    int Query(int x) {
        int Ret = 0;
        while (x) {
            Ret += t[x];
            x -= lowbit(x);
        }
        return Ret;
    }
    int Query(int l, int r) {
        return Query(r) - Query(l - 1);
    }
} t1, t2;
void Add(int x) {
    t2.Add(x, 1);
    if (t2.Query(x, x) == 1) t1.Add(x, 1);
}
void Del(int x) {
    t2.Add(x, -1);
    if (t2.Query(x, x) == 0) t1.Add(x, -1);
}
struct P {
    int id;
    int l, r, a, b;
    friend bool operator < (const P x, const P y) {
         return block[x.l] < block[y.l] || 
        (block[x.l] == block[y.l] && (block[x.l] & 1 ? x.r < y.r : x.r > y.r));
    }
} p[V * 10];
void Solve() {
    int i, j;
    int L = 1, R = 0;
    for (i = 1; i <= M; i++) {
        while (L < p[i].l) Del(a[L]), ++L;
        while (R > p[i].r) Del(a[R]), --R;
        while (L > p[i].l) --L, Add(a[L]);
        while (R < p[i].r) ++R, Add(a[R]);
        Ans1[p[i].id] = t2.Query(p[i].a, p[i].b);
        Ans2[p[i].id] = t1.Query(p[i].a, p[i].b);
    }
}
int main(void) {
    int i, j;
    //freopen("in.txt", "r", stdin);
    Read(N); Read(M); B = sqrt(N);
    for (i = 1; i <= N; i++) Read(a[i]);
    for (i = 1; i <= N; i++) block[i] = (i - 1) / B + 1;
    for (i = 1; i <= M; i++) {
        p[i].id = i;
        Read(p[i].l); Read(p[i].r); Read(p[i].a); Read(p[i].b);
    }
    sort(p + 1, p + 1 + M);
    Solve();
    for (i = 1; i <= M; i++) printf("%d %d\n", Ans1[i], Ans2[i]);
    return 0;
}
