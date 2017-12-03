#include <bits/stdc++.h>
using namespace std;
const int V = 2010;
const int L = 100010;
int Max(int a, int b) {
    return a > b ? a : b;
}
char get(void) {
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
int A[V][V], N, M, MX, s[V], top, vis[V][V];
bool Chk(int x) {
    int i, j, k;
    for (i = 1; i <= N; i++)
        for (j = 1; j <= M; j++)
            vis[i][j] = 0;
    for (i = 1; i <= N; i++) {
        top = 0;
        for (j = 1; j <= M; j++)
            if (A[i][j] >= x) s[++top] = j;
        for (j = 1; j <= top; j++)
            for (k = j + 1; k <= top; k++)
                if (vis[s[j]][s[k]])
                    return 1;
                else
                    vis[s[j]][s[k]] = 1; 
    }
    return 0;
}
int main(void) {
    int i, j;
    //freopen("in.txt", "r", stdin);
    Read(N); Read(M);
    for (i = 1; i <= N; i++)
        for (j = 1; j <= M; j++) {
            Read(A[i][j]); MX = Max(MX, A[i][j]); 
        }
    int L = 0, R = MX, Mid, Ans;
    while (L <= R) {
        if (Chk(Mid = L + R >> 1)) 
            L = (Ans = Mid) + 1;
        else
            R = Mid - 1;
    }
    cout << Ans << endl;
    return 0;
}
