#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL P = 1000000007LL;
const int V = 500010;
void $(LL &x, LL y) {
    (x += y) %= P;
}
LL Pow(LL x, LL y) {
    x %= P;
    LL Ret = 1LL;
    while (y) {
        if (y & 1) (Ret *= x) %= P;
        y >>= 1;
        if (y) (x = x * x) %= P;
    }
    return Ret;
}
struct Mat {
    LL a[2][2];
    Mat() {
        memset(a, 0, sizeof a);
    }
    LL * operator [] (const int x) {
        return a[x];
    }
    friend Mat operator + (Mat x, Mat y) {
        Mat Ret; int i, j;
        for (i = 0; i < 2; i++)
            for (j = 0; j < 2; j++)
                $(Ret.a[i][j], x[i][j] + y[i][j]);
        return Ret;
    }
    friend Mat operator * (Mat x, Mat y) {
        Mat Ret; int i, j, k;
        for (k = 0; k < 2; k++)
            for (i = 0; i < 2; i++)
                for (j = 0; j < 2; j++)
                    $(Ret.a[i][j], x[i][k] * y[k][j] % P);
        return Ret;
    }
};
Mat Mulx(LL x) {
    Mat w, s;
    w.a[0][0] = 0; w.a[0][1] = w.a[1][0] = w.a[1][1] = 1;
    s.a[0][0] = s.a[1][1] = 1; s.a[1][0] = s.a[0][1] = 0;
    while (x) {
        if (x & 1) s = s * w;
        x >>= 1;
        if (x) w = w * w;
    }
    return s;
}
LL N, f[V];
LL pr[V], p, e[V];
void Euler(int n) {
    int i, j;
    e[1] = 1;
    for (i = 2; i <= n; i++) {
        if (!e[i]) {
            e[i] = i - 1; pr[++p] = i;
        }
        for (j = 1; j <= p && i * pr[j] <= n; j++) {
            if (i % pr[j])
                e[i * pr[j]] = e[i] * (pr[j] - 1);
            else {
                e[i * pr[j]] = e[i] * pr[j];
                break;
            }
        }
    }
}
void Init() {
    int i, j;
    Euler(V - 1);
    f[1] = 1; f[2] = 3;
    for (i = 3; i < V; i++) {
        $(f[i], f[i - 1] + f[i - 2]);
    }
}
LL gfib(LL x) {
    Mat r = Mulx(x);
    return (r[0][0] + r[1][0]) % P;
}
LL gf(LL x) {
    if (x < V) return f[x];
    return (gfib(x - 2) + gfib(x)) % P;
}
LL ge(LL x) {
    //if (x < V) return e[x];
    LL Ret = x, i;
    for (i = 2; i * i <= x; i++) 
        if (!(x % i)) {
            Ret = Ret / i * (i - 1);
            while (!(x % i)) x /= i;
    }
    if (x > 1) Ret = Ret / x * (x - 1);
    return Ret;
}
int main(void) {
    Init(); int i, j;
    //freopen("in.txt", "r", stdin);
    while (cin >> N) {
        if (N == 1) {
            cout << 2 << endl;
            continue;
        }
        LL Ans = 0LL;
        for (i = 1; i * i <= N; i++) 
            if (!(N % i)) {
                $(Ans, ge(N / i) * gf(i) % P);
                if (i * i != N) {
                    j = N / i;
                    $(Ans, ge(N / j) * gf(j) % P);
                }
        }
        (Ans *= Pow(N, P - 2)) %= P;
        cout << Ans << endl;
    }
    return 0;
}
