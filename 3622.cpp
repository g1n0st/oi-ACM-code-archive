#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 2010;
const int P = 1000000009;
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
    for (; !(c >= '0' && c <= '9'); c = get());
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get());
}
int N, K;
int C[V][V], a[V], b[V], nxt[V], f[V][V], g[V], fac[V];
void Pre(int n) {
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= n; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
    }
    fac[0] = 1; for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % P;
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int i, j; Pre(V - 1); Read(N); Read(K);
    if ((N - K) & 1) {
        printf("0\n"); return 0;
    }
    K = (N + K) >> 1;
    for (i = 1; i <= N; i++) Read(a[i]);
    for (i = 1; i <= N; i++) Read(b[i]);
    sort(a + 1, a + 1 + N);
    sort(b + 1, b + 1 + N);
    for (i = 1, j = 0; i <= N; i++) {
        while (j < N && a[i] > b[j + 1]) j++; nxt[i] = j;
    }
    f[0][0] = 1;
    for (i = 1; i <= N; i++)
        for (j = 0; j <= i; j++) {
            f[i][j] = f[i - 1][j];
            if (j && nxt[i] - j + 1 > 0) 
                f[i][j] = (f[i][j] + (LL)f[i - 1][j - 1] * (nxt[i] - j + 1) % P) % P;
        }
    for (i = N; i >= K; i--) {
        g[i] = (LL)f[N][i] * fac[N - i] % P;
        for (int j = i + 1; j <= N; j++) 
            g[i] = (g[i] + (P - (LL)g[j] * C[j][i] % P) % P) % P;
    }
    cout << g[K] << endl;
    return 0;
}
