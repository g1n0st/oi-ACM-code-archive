#include <bits/stdc++.h>
using namespace std;
const int V = 200005;
void Read(int &x) {
    scanf("%d", &x);
}
struct C {
    int op, x, y, v;
} c[V];
int N, M, id[V], tot = -1, Ans[V];
 
namespace BIT {
    unsigned t[V][2], d[V][2];
 
    int lowbit(int x) {
        return x & (-x);
    }
    void Modify(bool s, int x, unsigned c) {
        while (x <= N * 2 + 100) {
            if (t[x][s] != tot) { 
                t[x][s] = tot; d[x][s] = 0; 
            }
            d[x][s] += c;
            x += lowbit(x);
        }
    }
 
    unsigned Sum(bool s, int x) {
        int res = 0;
        while(x) {
            if (t[x][s] != tot) { 
                t[x][s] = tot; d[x][s] = 0; 
            }
            res += d[x][s];
            x -= lowbit(x);
        }
        return res;
    }
    void Add1(int x, int y) {
        Modify(0, x, 1); Modify(0, y + 1, -1);
        Modify(1, x, x); Modify(1, y + 1, -(y + 1));
    }
 		void Add(int x, int y) {
 			Add1(x + N + 1, y + N + 1);
		 }
    unsigned Query1(int x, int y) {
        unsigned tmp = Sum(0, y) * (y + 1) - Sum(1, y);
        tmp -= Sum(0, x - 1) * x - Sum(1, x - 1);
        return tmp;
    }
    unsigned Query(int x, int y) {
    	return Query1(x + N + 1, y + N + 1);
		}
}
 
int t1[V], t2[V];
void Solve(int L, int R, int l, int r) {
    int i, j; ++tot;
    if (L > R) return;
    if (l == r) {
        for (i = L; i <= R; i++)
            if (c[id[i]].op ^ 1) Ans[id[i]] = l;
        return;
    }
    int Mid = (l + r) >> 1;
    *t1 = *t2 = 0; using namespace BIT;
    for (i = L; i <= R; i++) {
        if (c[id[i]].op & 1) {
            if (c[id[i]].v <= Mid) t1[++*t1] = id[i];
            else {
                t2[++*t2] = id[i];
                Add(c[id[i]].x, c[id[i]].y);
            }
        }
        else {
            unsigned cnt = Query(c[id[i]].x, c[id[i]].y);
            if (cnt < c[id[i]].v) {
                t1[++*t1] = id[i];
                c[id[i]].v -= cnt;
            }
            else t2[++*t2] = id[i];
        }
    }
    int l1 = L, l2 = L + *t1 - 1;
    for (i = 1; i <= *t1; i++) id[l1++] = t1[i];
    for (i = 1; i <= *t2; i++) id[l1++] = t2[i];
    Solve(L, l2, l, Mid); Solve(l2 + 1, R, Mid + 1, r);
}
int main(void) {
    int i, j;
		Read(N); Read(M);
    for (i = 1; i <= M; i++) {
        Read(c[i].op); Read(c[i].x); Read(c[i].y); Read(c[i].v);
    }
    for (i = 1; i <= M; i++) id[i] = i;
    Solve(1, M, 1, N);
    for (i = 1; i <= M; i++) if (c[i].op ^ 1) printf("%d\n", Ans[i]);
    return 0;
}
