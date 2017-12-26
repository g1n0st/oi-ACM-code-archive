#include <bits/stdc++.h>
using namespace std;
const int V = 100010;
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
        x = x * 10 + c - '0'; c = get();
    }
}
int t[V], N, a[V], M, Ans[V];
vector<int> s[V], b[V];
int lowbit(int x) {
    return x & (-x);
}
int Query(int x) {
    int Ret = ~0U >> 1;
    x = N - x + 1;
    while (x) {
        Ret = min(Ret, t[x]); x -= lowbit(x);
    }
    return Ret;
}
void Modify(int x, int v) {
    if (v == 0) return;
    x = N - x + 1;
    while (x <= N) {
        t[x] = min(t[x], v); x += lowbit(x);
    }
}
struct Node {
    int l, r, id;
    friend bool operator < (const Node &a, const Node &b) {
        return a.r < b.r;
    }
} v[V];
int main() {
    int i, j, k; 
    Read(N); Read(M);
    for (i = 1; i <= N; i++) {
        Read(a[i]); t[i] = ~0U >> 1;
    }
    for (i = 1; i <= M; i++) {
        Read(v[i].l); Read(v[i].r); v[i].id = i;
    }
    sort(v + 1, v + 1 + M);
    int sec = 1;
    for (i = 1; i <= N; i++) {
        for (k = i - 1; k && a[k] > a[i]; k--);
        if (k)
            while (k) {
                s[i].push_back(k);
                int tmp = 0;
                for (j = 0; j < b[k].size(); j++)
                    if (a[b[k][j]] <= a[i]) {
                        tmp = b[k][j]; break;
                    }
                k = tmp;
            }
        for (k = i - 1; k && a[k] < a[i]; k--);
        if (k)
            while (k) {
                b[i].push_back(k);
                int tmp = 0;
                for (j = 0; j < s[k].size(); j++)
                    if (a[s[k][j]] >= a[i]) {
                        tmp = s[k][j]; break;
                    }
                k = tmp;
            }
   
        for (j = 0; j < b[i].size(); j++) Modify(b[i][j], a[b[i][j]] - a[i]);
        for (j = 0; j < s[i].size(); j++) Modify(s[i][j], a[i] - a[s[i][j]]);
        for (; sec <= M && v[sec].r == i; ++sec)
            Ans[v[sec].id] = Query(v[sec].l);
    }
    for (i = 1; i <= M; i++) printf("%d\n", Ans[i]);
    return 0;
}
