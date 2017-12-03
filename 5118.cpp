#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL P = 1125899839733759LL;
LL Add(LL &x, LL y, LL p) {
    (x += y) %= p; 
}
LL Mul(LL x, LL y, LL p) {
    LL Ret = 0LL;
    while (y) {
        if (y & 1) Add(Ret, x, p); 
        y >>= 1;
        if (y) x = (x + x) % p;
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
        Mat z; static int i, j;
        for (i = 0; i < 2; i++)
            for (j = 0; j < 2; j++)
                Add(z.a[i][j], x[i][j] + y[i][j], P);
        return z;
    }
    friend Mat operator * (Mat x, Mat y) {
        Mat z; static int i, j, k;
        for (i = 0; i < 2; i++)
            for (j = 0; j < 2; j++)
                for (k = 0; k < 2; k++)
                    Add(z.a[i][j], Mul(x[i][k], y[k][j], P), P);
        return z;
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
LL Pow(LL x, LL y, LL p) {
    LL Ret = 1LL;
    while (y) {
        if (y & 1) Ret = Mul(Ret, x, p); 
        y >>= 1;
        if (y) x = Mul(x, x, p);
    }
    return Ret;
}
int T;
LL N;
void Solve() {
    cin >> N;
    N = Pow(2LL, N, P - 1);
    Mat x = Mulx(N - 1);
    LL Ans = (x.a[0][0] + x.a[1][0]) % P;
    cout << Ans << endl; 
}
int main(void) {
    //freopen("in.txt", "r", stdin);
    cin >> T;
    while (T--) Solve();
    return 0;
}
