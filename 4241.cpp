#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long LL;
const int V = 200010;
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
void Write(LL x) {
    if (!x) return (void)puts("0");
    if (x < 0) putchar('-'), x = -x;
    static short s[20], t;
    while (x) s[++t] = x % 10, x /= 10;
    while (t) putchar('0' + s[t--]);
    putchar('\n');
}
int block[V], N, M, B, a[V], b[V];
LL s[V], Ans[V];
struct Node {
    int l, r, id;
    friend bool operator < (const Node x, const Node y) {
        return block[x.l] < block[y.l] ||
            (block[x.l] == block[y.l] && (block[x.l] & 1 ? x.r < y.r : x.r > y.r));
    }
} v[V];
vector<int> q;
typedef __gnu_pbds::priority_queue<LL, less<LL>, pairing_heap_tag> heap;
heap Q;
heap::point_iterator p[V];
void Update(int pos, int v) {
    s[b[pos]] += a[pos] * v;
    Q.modify(p[b[pos]], s[b[pos]]);
}
void Solve() {
    int L = 1, R = 0;
    for (int i = 1; i <= M; i++) {
        while (R < v[i].r) R++, Update(R, 1);
        while (L > v[i].l) L--, Update(L, 1);
        while (R > v[i].r) Update(R, -1), R--;
        while (L < v[i].l) Update(L, -1), L++;
        Ans[v[i].id] = Q.top();
    }
}
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int i, j;
    Read(N); Read(M); B = sqrt(N);
    for (i = 1; i <= N; i++) {
        Read(a[i]); block[i] = (i - 1) / B + 1;
        q.push_back(a[i]);
    }
    sort(q.begin(), q.end());
    q.erase(unique(q.begin(), q.end()), q.end());
    int R = 0;
    for (i = 1; i <= N; i++) {
        b[i] = lower_bound(q.begin(), q.end(), a[i]) - q.begin() + 1;
        R = max(R, b[i]);
    }
    for (i = 1; i <= R; i++) p[i] = Q.push(0);
    for (i = 1; i <= M; i++) {
        Read(v[i].l); Read(v[i].r); v[i].id = i;
    }
    sort(v + 1, v + 1 + M);
    Solve();
    for (i = 1; i <= M; i++) Write(Ans[i]);
    return 0;
}
