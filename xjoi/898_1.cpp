#include <bits/stdc++.h>
using namespace std;
const int N = 510;
typedef long long LL;
void Read(int &x) {
    scanf("%d", &x);
}
const int INF = 0x3f3f3f3f;
namespace Net {
    const int M = N * N * 2 + N * 4;
    int head[N], sub;
    struct Edge {
        int to, nxt, cap, flow, w;
        Edge() {
        }
        Edge(int to, int nxt, int cap, int flow, int w) :
            to(to), nxt(nxt), cap(cap), flow(flow), w(w) {}
    } edge[M];
    void Add(int a, int b, int c, int f, int w) {
        edge[++sub] = Edge(b, head[a], c, f, w); head[a] = sub;
    }
    void Link(int a, int b, int f, int w) {
        Add(a, b, f, 0, w); Add(b, a, 0, 0, -w);
    }
    void init() {
        sub = 1;
    }
    LL dis[N]; int pre[N], vis[N];
    int spfa(int S, int T) {
        queue<int> q;
        for (int i = 1; i <= T; i++) {
            dis[i] = INF; pre[i] = 0;
        }
        dis[S] = 0; q.push(S); vis[S] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop(); vis[u] = 0;
            for (int i = head[u], v; i; i = edge[i].nxt) {
                Edge e = edge[i]; v = edge[i].to;
                if (dis[v] > dis[u] + e.w && e.cap - e.flow > 0) {
                    dis[v] = dis[u] + e.w; pre[v] = i;
                    if (!vis[v]) {
                        vis[v] = 1; q.push(v);
                    }
                }
            }
        }
        return pre[T];
    }
    int mcmf(int S, int T, LL &cost, int &flow) {
        cost = flow = 0;
        while (spfa(S, T)) {
            int Mn = INF;
            for (int i = pre[T]; i; i = pre[edge[i ^ 1].to])
                Mn = min(Mn, edge[i].cap - edge[i].flow);
            flow += Mn;
            for (int i = pre[T]; i; i = pre[edge[i ^ 1].to]) {
                edge[i].flow += Mn; edge[i ^ 1].flow -= Mn; cost += (LL)Mn * edge[i].w;
            }
        }
    }
}
int n, m, a[N], b[N], c[N][N];
typedef pair<int, int> PI;
typedef pair<int, PI> PII;
#define x first
#define y second
vector<PII> G;
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("a.txt", "w", stdout);
    Read(n); Read(m); Net::init();
    int S = n + m + 1, T = n + m + 2;
    for (int i = 1; i <= n; i++) {
        Read(a[i]); Net::Link(S, i, a[i], 0);
    }
    for (int i = 1; i <= m; i++) {
        Read(b[i]); Net::Link(i + n, T, b[i], 0);
    }
    if (n >= 100 && m >= 100) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                Read(c[i][j]);
                G.push_back(PII(c[i][j], PI(i, j)));
        }
        sort(G.begin(), G.end());
        int f = 0; LL c = 0;
        for (int i = 0; i < n * n / 8; i++) {
            Net::Link(G[i].second.first, G[i].second.second + n, INF, G[i].first);
        }
        for (int i = n * n / 8; i < n * n; i++)
            if (G[i].first == G[n * n / 8 - 1].first)
                Net::Link(G[i].second.first, G[i].second.second + n, INF, G[i].first);
        Net::mcmf(S, T, c, f);
        cout << c << endl;
    } else {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++) {
                    Read(c[i][j]);
                    Net::Link(i, j + n, INF, c[i][j]);
            }
        LL c = 0; int f = 0;
        Net::mcmf(S, T, c, f);
        cout << c << endl;
    }
    return 0;
}
