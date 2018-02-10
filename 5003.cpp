#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 1000000009;
const int V = 100010;
void Add(int &x, int y) {
    (y += P) %= P; (x += y) %= P;
}
int n, k, f[2][V], h[V], x, o;
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    scanf("%d%d", &k, &n); f[0][0] = 1;
    for (x = 1, o = 1; x <= n; x <<= 1, o ^= 1) {
        memset(h, 0, sizeof h);
        for (int i = 0; i <= n; i++) {
            Add(h[i % x], f[o ^ 1][i]);
            if (i - (LL)x * (k + 1) >= 0) Add(h[i % x], -f[o ^ 1][i - x * (k + 1)]);
            f[o][i] = h[i % x];
        }
    }
    cout << f[o ^ 1][n] << endl;
    return 0;
}
