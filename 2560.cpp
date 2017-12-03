#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL P = 1000000007LL;
const int V = 21;
int N, bin[V], a[V][V];
LL f[1 << V], g[1 << V];
int main(void) {
    int i, j, S;
    //freopen("in.txt", "r", stdin);
    cin >> N;
    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++)
            cin >> a[i][j];
    bin[0] = 1; for (i = 1; i <= N; i++) bin[i] = bin[i - 1] << 1;
    for (S = 1; S < bin[N]; S++) {
        g[S] = 1;
        int p = 0;
        for (i = 1; i <= N; i++) if (S & bin[i - 1]) {
            p = i;
            for (j = i + 1; j <= N; j++) if (S & bin[j - 1])
                g[S] = g[S] * (a[i][j] + 1) % P;
        }
        f[S] = g[S];
        for (i = S ^ bin[p - 1]; i; i = (i - 1) & S)
            f[S] = (f[S] - g[i] * f[S ^ i] % P + P) % P;
    }
    cout << f[bin[N] - 1] << endl;
    return 0;
}
