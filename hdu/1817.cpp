#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N, Ans;
LL Gcd(LL a, LL b) {
    return b ? Gcd(b, a % b) : a;
}
LL $(LL x, LL y) {
    if (!y) return 1;
    if (y == 1) return x;
    LL d = $(x, y >> 1); d = d * d;
    if (y & 1) return d * x;
    return d;
}
int main(void) {
    int i, j;
    //freopen("in.txt", "r", stdin);
    while (cin >> N, N != -1) {
        if (N <= 0) {
            cout << 0 << endl;
            continue;
        }
        Ans = 0LL;
        for (i = 1; i <= N; i++) {
            Ans += $(3, Gcd(N, i));
        }
        if (N & 1) Ans += N * $(3, (N + 1) / 2);
        else {
            Ans += (N / 2) * $(3, N / 2);
            Ans += (N / 2) * $(3, N / 2 + 1);
        }
        Ans /= (2 * N);
        cout << Ans << endl;
    }
    return 0;
}
