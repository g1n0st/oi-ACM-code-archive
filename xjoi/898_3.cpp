#include <bits/stdc++.h>
using namespace std;
 
typedef pair<int, int> PI;
typedef pair<int, PI> PII;
 
const int SIZ = 16;
 
struct DatBlk {
    stack<PII> opr;
    int pre[SIZ + 1], nxt[SIZ + 1], ext[SIZ + 1], tot;
    DatBlk() {
        tot = SIZ;
        for (int i = 0; i <= SIZ; i++) {
            nxt[i] = (i + 1 > SIZ ? 0 : i + 1);
            pre[i] = (i ? i - 1 : 0);
            if (i) ext[i] = 1;
        }
    }
    int Del(int x) {
        if (!ext[x]) {
            opr.push(PII(0, PI(0, 0)));
            return 0;
        }
        tot--;
        opr.push(PII(x, PI(pre[x], nxt[x])));
        ext[x] = 0;
        nxt[pre[x]] = nxt[x];
        pre[nxt[x]] = pre[x];
        return (tot == 0);
    }
    void Cover() {
        PII op = opr.top(); opr.pop();
        if (!op.first) return ;
        tot++;
        int x = op.first;
        ext[x] = 1;
        int p = op.second.first, n = op.second.second;
        nxt[p] = x; pre[n] = x;
    }
} c[SIZ + 1][SIZ + 1];
 
struct Qzone {
    DatBlk * a[SIZ + 1];
     
    stack<PII> opr;
    int pre[SIZ + 1], nxt[SIZ + 1], ext[SIZ + 1], tot;
     
    Qzone() {
        tot = SIZ;
        for (int i = 0; i <= SIZ; i++) {
            nxt[i] = (i + 1 > SIZ ? 0 : i + 1);
            pre[i] = (i ? i - 1 : 0);
            if (i) ext[i] = 1;
        }
    }
    int Del_Number(int x) {
        int r = 0;
        for (int i = nxt[0]; i; i = nxt[i])
            if (i) r |= a[i]->Del(x);
        return r;
    }
    void Cov_Number() {
        for (int i = nxt[0]; i; i = nxt[i])
            if (i) a[i]->Cover();
    }
     
    void Del(int x) {
        if (!ext[x]) {
            opr.push(PII(0, PI(0, 0)));
            return;
        }
        opr.push(PII(x, PI(pre[x], nxt[x])));
        ext[x] = 0;
        nxt[pre[x]] = nxt[x];
        pre[nxt[x]] = pre[x];
    }
    void Cover() {
        PII op = opr.top(); opr.pop();
        if (!op.first) return ;
        int x = op.first;
        ext[x] = 1;
        int p = op.second.first, n = op.second.second;
        nxt[p] = x; pre[n] = x;
    }
} Hz[SIZ + 1], Lz[SIZ + 1], Bz[SIZ + 1];
 
int L[SIZ + 1][SIZ + 1], H[SIZ + 1][SIZ + 1], B[SIZ + 1][SIZ + 1];
int L_M[SIZ + 1][SIZ + 1], H_M[SIZ + 1][SIZ + 1], B_M[SIZ + 1][SIZ + 1];
void Init_Data() {
    for (int i = 1; i <= SIZ; i++)
        for (int j = 1; j <= SIZ; j++) {
            L[i][j] = i; L_M[i][j] = j;
            H[i][j] = j; H_M[i][j] = i;
             
            int I = (i - 1) / 4 + 1, J = (j - 1) / 4 + 1;
            B[i][j] = (I - 1) * 4 + J;
            int II = i % 4, JJ = j % 4;
            if (!II) II = 4; if (!JJ) JJ = 4;
            B_M[i][j] = (II - 1) * 4 + JJ;
             
            Lz[L[i][j]].a[L_M[i][j]] = &c[i][j];
            Hz[H[i][j]].a[H_M[i][j]] = &c[i][j];
            Bz[B[i][j]].a[B_M[i][j]] = &c[i][j];
        }
}
 
 
inline void Del(int i, int j) {
    Lz[L[i][j]].Del(L_M[i][j]);
    Hz[H[i][j]].Del(H_M[i][j]);
    Bz[B[i][j]].Del(B_M[i][j]);
}
 
inline void reDel(int i, int j) {
    Lz[L[i][j]].Cover();
    Hz[H[i][j]].Cover();
    Bz[B[i][j]].Cover();
}
 
inline int Fz(int i, int j, int x) {
    return Lz[L[i][j]].Del_Number(x) |
    Hz[H[i][j]].Del_Number(x) |
    Bz[B[i][j]].Del_Number(x);
}
inline void Cv(int i, int j) {
    Lz[L[i][j]].Cov_Number();
    Hz[H[i][j]].Cov_Number();
    Bz[B[i][j]].Cov_Number();
}
 
char Mat[SIZ + 1][SIZ + 1];
 
vector<PI> G;
 
void Output() {
    for (int i = 1; i <= SIZ; i++) printf("%s\n", Mat[i] + 1);
}
 
void dfs(int o) {
    if (o == G.size()) {
        Output(); exit(0);
    }
    int i = G[o].first, j = G[o].second;
    Del(i, j);
    int k = c[i][j].nxt[0];
    while (k) {
        Mat[i][j] = 'A' + k - 1;
        if (Fz(i, j, k)) Cv(i, j);
        else {
            dfs(o + 1); Cv(i, j);
        }
        k = c[i][j].nxt[k];
    }
    reDel(i, j);
}
int main() {
    //freopen("mat.txt", "r", stdin);
    //freopen("mat.out", "w", stdout);
    Init_Data();
    for (int i = 1; i <= SIZ; i++) scanf("%s", Mat[i] + 1);
     
    for (int i = 1; i <= SIZ; i++)
        for (int j = 1; j <= SIZ; j++)
            if (Mat[i][j] != '-') Del(i, j);
             
    for (int i = 1; i <= SIZ; i++)
        for (int j = 1; j <= SIZ; j++)
            if (Mat[i][j] == '-') {
                for (int k = 1; k <= SIZ; k++)
                    if (Mat[k][j] != '-') c[i][j].Del(Mat[k][j] - 'A' + 1);
                 
                for (int k = 1; k <= SIZ; k++)
                    if (Mat[i][k] != '-') c[i][j].Del(Mat[i][k] - 'A' + 1);
                     
                int I = ((i - 1) / 4) * 4, J = ((j - 1) / 4) * 4;
                 
                for (int a = 1; a <= 4; a++)
                    for (int b = 1; b <= 4; b++)
                        if (Mat[I + a][J + b] != '-') c[i][j].Del(Mat[I + a][J + b] - 'A' + 1);
                         
                G.push_back(PI(i, j));
    }
     
    dfs(0);
     
    return 0;
}
