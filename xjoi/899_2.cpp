#include <bits/stdc++.h>
#include <queue>
using namespace std;
 
typedef long long LL;
const int V = 200010;
 
void Read(int &x) {
    scanf("%d", &x);
}
 
int n, a[V];
 
priority_queue<int, vector<int>, greater<int> > q;
LL sum, ans;
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
     
    Read(n);
    for (int i = 1; i <= n; i++) {
        Read(a[i]); sum += a[i];
    }
    for (int i = 2; i <= n; i++)
        if (i & 1) {
            int t = q.top();
            if (a[i] > t) {
                ans += a[i] - t; q.pop();
                q.push(a[i]);
            }
        } else ans += a[i], q.push(a[i]);
 
    cout << ans * 2 - sum << endl;
    return 0;
}
