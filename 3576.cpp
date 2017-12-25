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
inline void Read(int &x) {
    x = 0; static char c;
    while (c > '9' || c < '0') c = get();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0'; c = get();
    }
}
int sg[V], vis[V], tp;
inline int Cal(int x) {
    int Nxt, r, k1, k0, x0, x1, tmp; ++tp;
    for (int i = 2; i <= x; i = Nxt + 1) {
        tmp = (x / i);
        k1 = x % i; k0 = i - k1;
        r = 0;
        if (k0 & 1) r ^= sg[tmp];
        if (k1 & 1) r ^= sg[tmp + 1];
        vis[r] = tp;
        Nxt = min(x, x / tmp);
        if (i + 1 <= Nxt) {
            k1 = x % (i + 1); k0 = (i + 1) - k1;
            r = 0;
            if (k0 & 1) r ^= sg[tmp];
            if (k1 & 1) r ^= sg[tmp + 1];
            vis[r] = tp;
        }
    }
    int mex = 0;
    for (; vis[mex] == tp; mex++);
    return mex;
}
void Init(int F, int n) {
    int i, j;
    for (i = 0; i < F; i++) sg[i] = 0;
    for (i = F; i <= n; i++) sg[i] = Cal(i);
}
int T, F, N;
int main() {
    int i, j;
    Read(T); Read(F);
    Init(F, 100000);
    while (T--) {
        Read(N); int Ans = 0, x;
        for (i = 1; i <= N; i++) {
            Read(x); Ans ^= sg[x];
        }
        putchar('0' + (Ans ? 1 : 0));
        putchar(T ? ' ' : '\n');
    }
    return 0;
}
