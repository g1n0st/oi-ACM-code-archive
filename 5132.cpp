#include <bits/stdc++.h>
using namespace std;
const int V = 100100;
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
int rt[V], ls[V * 100], rs[V * 100], sum[V * 100], pT;
int NewNode() {
    ++pT; sum[pT] = ls[pT] = rs[pT] = 0;
    return pT;
}
void Add(int &x, int l, int r, int p, int v) {
    if (!x) x = NewNode(); sum[x] += v;
    if (l == r) return;
    int Mid = (l + r) >> 1;
    if (p <= Mid) Add(ls[x], l, Mid, p, v); else Add(rs[x], Mid + 1, r, p, v);
}
int Query(int x, int l, int r, int L, int R) {
    if (!x) return 0;
    if (l == L && r == R) return sum[x];
    int Mid = (l + r) >> 1;
    if (R <= Mid) return Query(ls[x], l, Mid, L, R);
    if (Mid < L) return Query(rs[x], Mid + 1, r, L, R);
    return Query(ls[x], l, Mid, L, Mid) + Query(rs[x], Mid + 1, r, Mid + 1, R);
}
int QMin(int x, int l, int r) {
    if (l == r) return l;
    int Mid = (l + r) >> 1;
    if (sum[ls[x]]) return QMin(ls[x], l, Mid); else return QMin(rs[x], Mid + 1, r);
}
struct Node {
    int op, a, b, t;
  Node(int op = 0, int a = 0, int b = 0, int t = 0) : op(op), a(a), b(b), t(t) {}
  friend bool operator < (const Node &a, const Node &b) {
        if (a.t ^ b.t) return a.t < b.t;
        return a.op < b.op;
  }
} cm[V * 10];
const int M = 1e9;
int T, N, Q, s[V], tot;
void Solve() {
    int i, j;
    Read(N); pT = 0;
    for (i = 1; i <= N; i++) Read(s[i]);
    Read(Q); tot = 0;
    int t, op, a = 0, b = 0;
    for (i = 1; i <= Q; i++) {
        Read(t); Read(op);
        if (op != 1) Read(a);
        if (op == 3) Read(b);
        if (!op) cm[++tot] = Node(-1, a, t, t + s[a]);
        cm[++tot] = Node(op, a, b, t);
    }
        memset(rt, 0, sizeof rt);
    sort(cm + 1, cm + 1 + tot);
    for (i = 1; i <= tot; i++) {
        if (cm[i].op == 0) Add(rt[cm[i].a], 1, M, cm[i].t, 1);
        if (cm[i].op == -1) {
            Add(rt[cm[i].a], 1, M, cm[i].b, -1);
            Add(rt[0], 1, N, cm[i].a, 1);
        }
                if (cm[i].op == 1) {
                    if (!sum[rt[0]]) printf("Yazid is angry.\n");
                    else {
                        int tmp = QMin(rt[0], 1, N);
                        printf("%d\n", tmp);
                        Add(rt[0], 1, N, tmp, -1);
                    }
                }
                if (cm[i].op == 2) {
                    int tmp = Query(rt[0], 1, N, cm[i].a, cm[i].a);
                    if (!(tmp + sum[rt[cm[i].a]])) printf("YJQQQAQ is angry.\n");
                    else if (tmp) {
                        printf("Succeeded!\n");
                        Add(rt[0], 1, N, cm[i].a, -1);
                    }
                    else printf("%d\n", QMin(rt[cm[i].a], 1, M) + s[cm[i].a] - cm[i].t);
                }
                if (cm[i].op == 3) printf("%d\n", Query(rt[0], 1, N, cm[i].a, cm[i].b));
    }
}
int main() {
    Read(T);
        while (T--) Solve();
    return 0;
}
