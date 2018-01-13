#ifdef ONLINE_JUDGE
#include "Bucharest.h"
#endif
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
int getHeaviest(int A, int B, int C) {
	return 1;
}
int getLightest(int A, int B, int C) {
	return 1;
}
int getMedian(int A, int B, int C) {
	return 1;
}
int getNextLightest(int A, int B, int C, int D) {
	return 1;
}
void answer(int c[]) {

}
#endif

struct P {
	int lst[6], rk[7];
} p[720]; int tp;
void InitPerms() {
	int x[] = { 1, 2, 3, 4, 5, 6 };
	do {
		for (int i = 0; i < 6; i++) {
			p[tp].lst[i] = x[i]; p[tp].rk[x[i]] = i;
		}
		tp++;
	} while (next_permutation(x, x + 6));
}
struct Oper {
	int type, A, B, C, D;
	Oper() {}
	Oper(int type, int A, int B, int C, int D) :
		type(type), A(A), B(B), C(C), D(D) {}

	int Ask(P * p) {
		int L = p->rk[A] < p->rk[B] ? p->rk[A] < p->rk[C] ? A : C : p->rk[B] < p->rk[C] ? B : C;
		int H = p->rk[A] > p->rk[B] ? p->rk[A] > p->rk[C] ? A : C : p->rk[B] > p->rk[C] ? B : C;
		int M = (A ^ B ^ C) ^ (L ^ H);

		switch (type) {
		case 0: return H;
		case 1: return L;
		case 2: return M;
		case 3: return p->rk[H]<p->rk[D] || p->rk[L]>p->rk[D] ? L : p->rk[M] > p->rk[D] ? M : H;
		}
	}

	int Ask() {
		switch (type) {
		case 0: return getHeaviest(A, B, C);
		case 1: return getLightest(A, B, C);
		case 2: return getMedian(A, B, C);
		case 3: return getNextLightest(A, B, C, D);
		}
	}
} op[4][60];
int to[4];
void InitOpers() {
	for (int t = 0; t < 4; t++) {
		if (t < 3)
			for (int A = 1; A < 7; A++)
				for (int B = A + 1; B < 7; B++)
					for (int C = B + 1; C < 7; C++)
						op[t][to[t]++] = Oper(t, A, B, C, 0);
		else
			for (int D = 1; D < 7; D++)
				for (int A = 1; A < 7; A++) if (A ^ D)
					for (int B = A + 1; B < 7; B++) if (B ^ D)
						for (int C = B + 1; C < 7; C++) if (C ^ D)
							op[t][to[t]++] = Oper(t, A, B, C, D);
	}
}
const int N = 1100;
vector<P*> adm[N];
Oper *oper[N];
int ch[N][7];

int InitTree(int u = 0, int Mx = 729) {
	if (!u) {
		for (int i = 0; i < tp; i++)
			adm[u].emplace_back(p + i);
	}
	if (adm[u].size() <= 1) return 1;
	for (int t = 0; t < 4; t++)
		for (int i = 0; i < to[t]; i++) {
			Oper * no = oper[u] = op[t] + i;
			for (int c = 1; c < 4; c++) adm[u * 3 + c].clear();
			int A = no->A, B = no->B, C = no->C, res;
			for (auto pp : adm[u]) {
				res = no->Ask(pp);
				if (res == A) adm[u * 3 + 1].emplace_back(pp);
				if (res == B) adm[u * 3 + 2].emplace_back(pp);
				if (res == C) adm[u * 3 + 3].emplace_back(pp);
			}
			bool s = 1;
			for (int c = 1; c < 4 && s; c++)
				s &= (adm[u * 3 + c].size() <= Mx / 3);
			for (int c = 1; c < 4 && s; c++)
				s &= InitTree(u * 3 + c, Mx / 3);
			if (s) {
				ch[u][A] = u * 3 + 1;
				ch[u][B] = u * 3 + 2;
				ch[u][C] = u * 3 + 3;
				return 1;
			}
		}
	return 0;
}

void init(int T) {
	InitPerms();
	InitOpers();
	InitTree();
}

void orderDolls() {
	int u = 0;
	while (adm[u].size() > 1)
		u = ch[u][oper[u]->Ask()];
	answer(adm[u][0]->lst);
}
#ifndef ONLINE_JUDGE
int main() {
	init(36);
	return 0;
}
#endif
