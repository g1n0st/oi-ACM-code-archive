#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL P = 1000000007LL;
const int V = 200010;
char get() {
    static char buf[V], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, V, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}
void Read(LL &x) {
    x = 0; static char c;
    while (c > '9' || c < '0') c = get();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0'; c = get();
    }
}
LL d[V], a[V], N, M, K;
LL Pow(LL x, int y) {
    LL Ret = 1LL;
    while (y) {
        if (y & 1) Ret = Ret * x % P;
        y >>= 1;
        if (y) x = x * x % P;
    }
    return Ret;
}
int main() {
    int i, j; LL x, y;
    //freopen("in.txt", "r", stdin);
    Read(N); Read(M); Read(K);
    for (i = 1; i <= N; i++) Read(a[i]);
    for (i = 1; i <= M; i++) {
        Read(x); Read(y);
        d[x]++; d[y]++;
    }
    LL Ans = 0LL, inv = Pow(2 * M, P - 2);
    for (i = 1; i <= N; i++) Ans = (Ans + K * d[i] % P * a[i] % P * inv % P) % P;
    cout << Ans << endl;
    return 0;
}
