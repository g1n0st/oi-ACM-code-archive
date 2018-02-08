#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const double pi = acos(-1);
const int V = 400010;
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
    for (; !isdigit(c); c = get());
    for (; isdigit(c); x = x * 10 + c - '0', c = get());
}
struct E {
    double x, y;
    E() {}
    E(double x, double y) : x(x), y(y) {}
    E(double x) : x(x), y(0) {}
    friend E operator + (E a, E b) {
        return E(a.x + b.x, a.y + b.y);
    }
    friend E operator - (E a, E b) {
        return E(a.x - b.x, a.y - b.y);
    }
    friend E operator * (E a, E b) {
        return E(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }
    friend E operator / (E a, double b) {
        return E(a.x / b, a.y / b);
    }
};
namespace FFT {
    int n, L, R[V];
    void Init(int m) {
        for (n = 1, L = 0; n < m; n <<= 1, L++); n <<= 1; L++;
        for (int i = 0; i < n; i++)
            R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
    }
    void fft(E *a, int f) {
        for (int i = 0; i < n; i++)
            if (i < R[i]) swap(a[i], a[R[i]]);
        for (int i = 1; i < n; i <<= 1) {
            E wn(cos(pi / i), f * sin(pi / i));
            for (int j = 0; j < n; j += (i << 1)) {
                E w(1, 0);
                for (int k = 0; k < i; k++, w = w * wn) {
                    E x = a[j + k], y = w * a[i + j + k];
                    a[j + k] = x + y; a[i + j + k] = x - y;
                }
            }
        }
        if (f == -1) for (int i = 0; i < n; i++) a[i] = a[i] / n;
    }
}
int T, N, M, k[V], a[V];
E p[V];
void Solve() {
    Read(N); M = 0;
    for (int i = 1; i <= N; i++) {
        Read(a[i]); M = max(M, a[i]);
    }
    for (int i = 0; i <= 100000; i++) k[i] = 0;
    for (int i = 1; i <= N; i++) k[a[i]]++;
    FFT::Init(M);
    for (int i = 0; i <= M; i++) p[i] = k[i];
    for (int i = M + 1; i < FFT::n; i++) p[i] = 0;
    FFT::fft(p, 1);
    for (int i = 0; i < FFT::n; i++) p[i] = p[i] * p[i];
    FFT::fft(p, -1);
    LL tot = (LL)N * (N - 1) * (N - 2) / 6, u = 0, y = 0;
    for (int i = 1; i <= N; i++) {
        LL x = (LL)(p[i].x + 0.1);
        if (i % 2 == 0) x -= k[i / 2];
        y += x;
        u += (y / 2) * k[i];
    }
    printf("%.7lf\n", 1 - 1.0 * u / tot);
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(T);
    while (T--) Solve();
    return 0;
}
