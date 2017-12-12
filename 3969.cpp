#include <cstdio>
#include <algorithm>
using namespace std;
const int V = 1000100;
int N, K, M, a[V];
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
    while (c > '9' || c < '0') c = get();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = get();
    }
}
bool Check(int x) {
    int cnt = N, i, j;
    for (i = 1; i < M && cnt; i++)
        if (a[i + 1] - a[i] <= x) {
            if (M - i + 1 < 2 * cnt * K) return 0;
            --cnt; i++;
        }
    return (cnt == 0);
}
int main() {
    int i, j;
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Read(N); Read(K);
    for (M = 2 * N * K, i = 1; i <= M; i++) Read(a[i]);
    sort(a + 1, a + 1 + M);
    int L = 0, R = a[M], Mid, Ans;
    while (L <= R) {
        Mid = L + R >> 1;
        if (Check(Mid)) 
                R = (Ans = Mid) - 1;
        else
                L = Mid + 1;
    }
    printf("%d\n", Ans);
    return 0;
}
