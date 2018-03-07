#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 1000000007;
const int V = 100010;
void Read(int &x) {
    scanf("%d", &x);
}
int a[V], h[V], m[V], n, K, b[V];
void mul(int *a, int *b) {
    static int r[V];
    for (int i = 0; i <= K + K; i++) r[i] = 0;
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++)
            r[i + j] = (r[i + j] + (LL)a[i] * b[j]) % P;
    for (int i = 2 * (K - 1); i >= K; i--)
        for (int j = 1; j <= K; j++)
            r[i - j] = (r[i - j] + (LL)r[i] * m[K - j]) % P;
    for (int i = 0; i < K; i++) a[i] = r[i];
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(n); Read(K);
    for (int i = K - 1; ~i; i--) {
        Read(a[i]); (a[i] += P) %= P;
    }
    for (int i = 0; i < K; i++) {
        Read(h[i]); (h[i] += P) %= P;
    }
    for (int i = K; i <= 2 * (K - 1); i++)
        for (int j = 1; j <= K; j++)
            h[i] = (h[i] + (LL)h[i - j] * a[K - j]) % P;
    if (n <= 2 * (K - 1)) return printf("%d\n", h[n]), 0;
    for (int i = 0; i < K; i++) m[i] = a[i];
    b[1] = 1;
    for (int i = n - 2 * K + 1; i; i >>= 1, mul(b, b))
        if (i & 1) mul(a, b);
    int ans = 0;
    for (int i = K - 1; i < K + K - 1; i++)
        ans = (ans + (LL)h[i] * a[i - K + 1]) % P;
    cout << ans << endl;
    return 0;
}
