#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N;
int K, pr[1300], p, vis[1300];
struct Node {
    LL val; int x, y, u;
    Node () {
    }
    Node (LL val, int x, int y, int u) : val(val), x(x), y(y), u(u) {
        //cout << val << ' ' << x << ' ' << y << ' ' << u << endl;
    }
    friend bool operator < (const Node &a, const Node &b) {
        return a.val < b.val;
    }
};
priority_queue<Node> qu;
void Init() {
    int i, j;
    for (i = 2; i < 128; i++) 
        if (!vis[i]) {
            pr[++p] = i;
            for (j = i; j < 128; j += i) vis[j] = 1;
            LL x = i;
            for (j = 1; x <= N; x *= i, j++)
                qu.push(Node(x, i, j, p));
    }
}
 
int main(void) {
    int i, j;
    //freopen("in.txt", "r", stdin);
    cin >> N >> K;
    Init();
    while (K--) {
        Node x = qu.top(); qu.pop();
        if (!K) {
            cout << x.val << endl;
            return 0;
        }
        if (x.y > 1)
            for (i = 1; i < x.u; i++)
                qu.push(Node(x.val / x.x * pr[i], x.x, x.y - 1, i + 1));
    }
    return 0; 
}
