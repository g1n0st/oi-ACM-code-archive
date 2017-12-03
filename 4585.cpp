#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 3000010;
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
int son[V][2], d[V], len[V], fa[V], rt[V];
int N, M, tot;
LL Sum, v[V];
int Union(int x, int y) {
    if (!x || !y) return x + y;
    if (v[x] < v[y]) swap(x, y);
    son[x][1] = Union(son[x][1], y);
    swap(son[x][0], son[x][1]);
    return x;
}
void Pop(int x) {
    rt[x] = Union(son[rt[x]][0], son[rt[x]][1]);
}
int main(void) {
    int i, j;
    //freopen("in.txt", "r", stdin);
    Read(N); Read(M);
    for (i = 2; i <= N + M; i++) {
        Read(fa[i]); Read(len[i]);
        Sum += len[i]; d[fa[i]]++;
    }
    for (i = N + M; i > 1; i--) {
        LL l = 0, r = 0;
        if (i <= N) {
            while (--d[i]) Pop(i);
            r = v[rt[i]]; Pop(i);
            l = v[rt[i]]; Pop(i);
        }
        v[++tot] = l + len[i];
        v[++tot] = r + len[i];
        rt[i] = Union(rt[i], Union(tot, tot - 1));
        rt[fa[i]] = Union(rt[fa[i]], rt[i]);
    }
    while (d[1]--) Pop(1);
    while (rt[1]) {
        Sum -= v[rt[1]]; Pop(1);
    }
    cout << Sum << endl;
    return 0;
}
