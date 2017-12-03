#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 1010;
LL N, M, P;
LL t, a[V], b[V], Ans;
LL g[V][V], inv[V], fac[V], mi[V * V], c[V][V];
LL Gcd(LL a, LL b) {
    return b ? Gcd(b, a % b) : a;
}
LL Pow(LL x, LL y) {
    LL Ret = 1LL;
    while (y) {
        if (y & 1) Ret = Ret * x % P;
        y >>= 1;
        if (y) x = x * x % P;
    }
    return Ret;
}
LL $(LL a, LL b) {
    return g[a][b];
}
void Init(LL n) {
    int i, j;
    for (i = 0; i <= n; i++)
        for (j = 0; j <= n; j++)
            g[i][j] = Gcd(i, j);
    fac[0] = 1LL; for (i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % P;
    inv[0] = 1LL; for (i = 1; i <= n; i++) inv[i] = Pow(fac[i], P - 2);
    mi[0] = 1; for (i = 1; i <= n * (n - 1) / 2; i++) mi[i] = mi[i - 1] * M % P;
    for (i = 0; i <= n; i++) {
        c[i][0] = 1LL;
        for (j = 1; j <= i; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P;
    }
}
void Dfs(int d) {
    int i, j; 
    if (!d) {
        int s = 0;
        for (i = 1; i <= t; i++)
            for (j = i + 1; j <= t; j++)
                s += $(a[i], a[j]);
        for (i = 1; i <= t; i++) s += (a[i] / 2);
        LL tot = N, G = 1LL;
        for (i = 1; i < t; i++) {
            G = G * c[tot][a[i]] % P; tot -= a[i];
        }
        for (i = 1; i <= N; i++)
            if (b[i]) G = G * inv[b[i]] % P;
        for (i = 1; i <= t; i++)
            G = G * fac[a[i] - 1] % P;
        Ans = (Ans + mi[s] * G % P) % P;
        return ;
    }
    for (i = a[t]; i <= d; i++) {
        a[++t] = i; b[i]++;
        Dfs(d - i);
        t--; b[i]--;
    }
}
int main(void) {
    int i, j;
    //freopen("in.txt", "r", stdin);
    cin >> N >> M >> P; Init(N);
    a[0] = 1LL; Dfs(N);
    Ans = Ans * inv[N] % P; 
    cout << Ans << endl;
    return 0;
}
