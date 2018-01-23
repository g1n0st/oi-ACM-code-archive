#include <bits/stdc++.h>
typedef long long LL;
const int V = 520010;
const int P = 1004535809;
const int G = 3;
using namespace std;
void Read(int &x) {
    scanf("%d", &x);
}
int Ksm(int x, int y = P - 2, int p = P) {
    int r = 1;
    while (y) {
        if (y & 1) r = (LL)r * x % P;
        y >>= 1;
        if (y) x = (LL)x * x % P;
    }
    return r;
}
 
namespace NTT {
    int n, L, R[V], w[2][V], INV;
    void Init(int m) {
        for (n = 1, L = 0; n < m; n <<= 1, L++); n <<= 1; L++;
        for (int i = 0; i < n; i++)
            R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
        int t = Ksm(G, (P - 1) / n); w[0][0] = w[0][n] = 1;
        for (int i = 1; i < n; i++)
            w[0][i] = (LL)w[0][i - 1] * t % P;
        for (int i = 0; i <= n; i++) w[1][i] = w[0][n - i];
        INV = Ksm(n);
    }
    void ntt(int *a, int f) {
        for (int i = 0; i < n; i++)
            if (i < R[i]) swap(a[i], a[R[i]]);
        for (int i = 1; i < n; i <<= 1)
            for (int j = 0; j < n; j += (i << 1))
                for (int k = 0; k < i; k++) {
                    int x = a[j + k], y = (LL)w[f][n / (i << 1) * k] * a[i + j + k] % P;
                    a[j + k] = (x + y) % P; a[i + j + k] = (x - y + P) % P;
                }
        if (f) for (int i = 0; i < n; i++) a[i] = (LL)a[i] * INV % P;
    }
}
int fac[V], inv[V], cc[V], c2[V], A[V], B[V], RB[V];
int N;
int tmp[V];
void GetInv(int *a, int *b, int n) {
    if (n == 1) {
        a[0] = Ksm(b[0]); return;
    }
    GetInv(a, b, n >> 1);
    for (int i = 0; i < n; i++) tmp[i] = b[i];
    for (int i = n; i < (n << 1); i++) tmp[i] = 0;
    NTT::Init(n); NTT::ntt(tmp, 0); NTT::ntt(a, 0);
    for (int i = 0; i < (n << 1); i++)
        a[i] = (LL)a[i] * (2 - (LL)tmp[i] * a[i] % P) % P;
    NTT::ntt(a, 1);
    for (int i = n; i < (n << 1); i++) a[i] = 0;
}
void Init() {
    int i, j;
    for (fac[0] = 1, i = 1; i <= N; i++)
        fac[i] = (LL)fac[i - 1] * i % P;
    for (inv[N] = Ksm(fac[N]), i = N - 1; ~i; i--)
        inv[i] = (LL)inv[i + 1] * (i + 1) % P;
    for (i = 2; i <= N; i++)
        cc[i] = (LL)i * (i - 1) / 2 % (P - 1);
    for (i = 0; i <= N; i++)
        c2[i] = Ksm(2, cc[i]);
 
    for (i = 1; i <= N; i++)
        A[i] = (LL)c2[i] * inv[i - 1] % P;
    for (i = 0; i <= N; i++)
        B[i] = (LL)c2[i] * inv[i] % P;
    int M = 1; for (; M <= N; M <<= 1);
    GetInv(RB, B, M);
 
    NTT::Init(N); NTT::ntt(A, 0); NTT::ntt(RB, 0);
    for (i = 0; i < NTT::n; i++) A[i] = (LL)A[i] * RB[i] % P;
    NTT::ntt(A, 1);
    int Ans = ((LL)A[N] + P) % P * fac[N - 1] % P;
    printf("%d\n", Ans);
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(N); Init();
}
