#include <bits/stdc++.h>
using namespace std;
const int V = 2000100;
const int INF = 1 << 30;
int Min(int a, int b) {
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
    while (c > '9' || c < '0') c = get();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = get();
    }
}
namespace Tr {
    struct Node {
        Node *ch[2];
        int val;
        int Query() {
            int Ret = val;
            if (ch[0]) Ret = Min(Ret, ch[0]->Query());
            if (ch[1]) Ret = Min(Ret, ch[1]->Query());
            return Ret;
        }
        bool Clear(int x) {
            if (x == val) return val = INF, ch[0] = ch[1] = 0, 1;
            if (ch[0] && ch[0]->Clear(x)) return ch[1] = 0, 1;
            if (ch[1] && ch[1]->Clear(x)) return ch[0] = 0, 1;
            return 0;
        }
    } *Tree[V], poor[V], *pT;
    void Init() {
        pT = poor;
    }
    Node * NewNode(int val, Node *a, Node *b) {
        Node *Ret = pT++;
        Ret->val = val; Ret->ch[0] = a; Ret->ch[1] = b;
        return Ret;
    }
};
int N;
int main(void) {
using namespace Tr;
    //freopen("in.txt", "r", stdin);
    Read(N); Init();
    int i, j, x;
    for (i = 1; i <= N; i++) {
        Read(x); Tree[i] = NewNode(x, 0, 0);
    }
    for (i = 2; i <= N; i++) {
        Node *a = Tree[i], *b = Tree[i >> 1];
        Tree[i] = NewNode(INF, a, b);
        Tree[i >> 1] = NewNode(INF, a, b);
    }
    for (i = 1; i <= N; i++) {
        int nVal = Tree[i]->Query(); Tree[i]->Clear(nVal);
        printf("%d%c", nVal, (i == N) ? '\n' : ' ');
    }
    return 0;
}
