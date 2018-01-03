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
void Read(LL &x) {
    x = 0; static char c;
    while (c > '9' || c < '0') c = get();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0'; c = get();
    }
}
LL gcd(LL a, LL b) {
    return !b ? a : gcd(b, a % b);
}
LL Pow(LL x, LL y) {
    LL R = 1;
    while (y) {
        if (y & 1) R = R * x;
        y >>= 1;
        if (y) x = x * x;
    }
    return R;
}
LL Pow(LL x, LL y, LL p) {
    LL R = 1;
    while (y) {
        if (y & 1) R = R * x % p;
        y >>= 1;
        if (y) x = x * x % p;
    }
    return R;
}
int cr[V];
int GtG(int p) {
    *cr = 0;
    for (int i = 2; i * i < p; i++) {
        if ((p - 1) % i) continue;
        cr[++*cr] = i; cr[++*cr] = (p - 1) / i;
    }
    for (int g = 2; g; g++) {
        int flg = 0;
        for (int i = 1; i <= *cr; i++) flg |= (Pow(g, cr[i], p) == 1);
        if (flg) continue;
        return g;
    }
}
map<LL, int>mp;
LL BSGS(LL a, LL b, LL p, LL pp) {
    mp.clear();
    int m = ceil(sqrt(p)), i, j;
    LL tmp = 1;
    for (i = 1; i <= m; i++) {
        tmp = tmp * a % p;
        if (tmp == b) return i;
        if (!mp[tmp]) mp[tmp] = i;
    }
    mp[1] = 0; LL tmp1 = 1; int phi;
    if (pp == p) phi = p - 1;
    else phi = p / pp * (pp - 1);
    for (i = 0; i <= p; i += m) {
        LL x = Pow(tmp1, phi - 1, p) * b % p;
        if (mp[x]) return mp[x] + i;
        tmp1 = tmp1 * tmp % p;
    }
    return 0;
}
LL T;
LL A, B, K, P;
LL Solve(LL p, LL t) {
    LL pr = Pow(p, t), b = B % pr;
    // sol1 
    if (!b) return Pow(p, t - (t - 1) / A - 1);
    // sol2
    int c = 0;
    while (!(b % p)) b /= p, ++c;
    int tmp = c / A; t -= c;
    int phi = pr - pr / p;
    int G = GtG(p);
    int ind = BSGS(G, b, pr, p);
    int d = gcd(A, phi);
    if (ind % d) return 0;
    return d * Pow(p, (A - 1) * tmp);
}
int main() {
    int i, j;
    Read(T);
    while (T--) {
        Read(A); Read(B); Read(K);
        LL Ans = 1;
        P = 2 * K + 1; K = P;
        for (i = 2; i * i <= P; i++) {
            if (!Ans) break;
            if (K % i) continue;
            int ci = 0;
            while (!(K % i)) ci++, K /= i;
            Ans *= Solve(i, ci);
        }
        if (Ans && K > 1) Ans *= Solve(K, 1);
        printf("%lld\n", Ans);
    }
    return 0;
}
