#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
LL Max(LL a, LL b) {
    return a > b ? a : b;
}
LL Min(LL a, LL b) {
    return a < b ? a : b;
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
    while (c > '9' || c < '0') {
        c = get();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = get();
    }
}
int head[V], sub;
struct Edge {
    int to, nxt, v;
    Edge(void) {}
    Edge(int to, int nxt, int v) : to(to), nxt(nxt), v(v) {}
} edge[V << 3];
void Add(int a, int b, int v) {
    edge[++sub] = Edge(b, head[a], v); head[a] = sub;
}
LL INF;
int N, M, K, bin[20];
LL f[1 << 6][V], Ans;
namespace Net {
    int vis[V];
    void spfa(LL *dis) {
        deque<int> qu;
        for (int i = 1; i <= N; i++)
            if (dis[i] != INF) {
                qu.push_back(i); vis[i] = 1;
            } else vis[i] = 0;
        while (!qu.empty()) {
            int u = qu.front(); qu.pop_front(); vis[u] = 0;
            for (int i = head[u], v; i; i = edge[i].nxt) {
                v = edge[i].to;
                if (dis[v] > dis[u] + edge[i].v) {
                    dis[v] = dis[u] + edge[i].v;
                    if (!vis[v]) {
                        vis[v] = 1;
                        if (!qu.empty() && dis[v] <= dis[qu.front()])
                            qu.push_front(v);
                        else
                            qu.push_back(v);
                    }
                }
            }
        }
    }
}
int main(void) {
    //freopen("in.txt", "r", stdin);
    int i, j, S, s;
    int x, y, v;
    Read(N); Read(K); Read(M);
    bin[0] = 1; for (i = 1; i <= K; i++) bin[i] = bin[i - 1] << 1;
    memset(f, 0x3f, sizeof f); INF = f[0][0];
    for (i = 1; i <= K; i++) {
        Read(x); f[bin[i - 1]][x] = 0LL;
    }
    for (i = 1; i <= M; i++) {
        Read(x); Read(y); Read(v);
        Add(x, y, v); Add(y, x, v);
    }
    for (S = 1; S < bin[K]; S++) {
        for (i = 1; i <= N; i++)
            for (s = (S - 1) & S; s; s = (s - 1) & S)
                f[S][i] = Min(f[S][i], f[s][i] + f[S ^ s][i]);
        Net::spfa(f[S]);
    }
    LL Ans = INF;
    for (i = 1; i <= N; i++) Ans = Min(Ans, f[bin[K] - 1][i]);
    cout << Ans << endl;
    return 0;
}
