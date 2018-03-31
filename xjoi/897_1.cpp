#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL Ksm(LL x, LL y, LL p) {
    LL r = 1;
    while (y) {
        if (y & 1) r = r * x % p;
        y >>= 1; if (y) x = x * x % p;
    }
    return r;
}
LL P, N, M;
LL G(int n) {
    if (!n) return 0;
    if (n & 1) {
        return (G(n - 1) + Ksm(P, n, M)) % M;
    }
    int pn = Ksm(P, n >> 1, M);
    return G(n >> 1) * (pn + 1) % M;
}
LL F(int n) {
    if (!n) return 1;
    if (n & 1) {
        LL tmp = (F(n - 1) + Ksm(P, n, M) * (n + 1)) % M;
        //printf("F(%d) = %d\n", n, tmp);
        return tmp;
    }
    LL fn = F(n >> 1), pn = Ksm(P, n >> 1, M);
    LL tmp = ((pn + 1) * fn % M - pn + pn * (n >> 1) % M * G(n >> 1) % M) % M;
    (tmp += M) %= M;
    //printf("F(%d) = %d\n", n, tmp);
    return tmp;
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("a.txt", "w", stdout);
    cin >> P >> N >> M;
    cout << F(N) << endl;
    return 0;
}
