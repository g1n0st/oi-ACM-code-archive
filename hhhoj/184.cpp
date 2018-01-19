#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int V = 100010;
const int P = 1000000000 + 1;
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
		x = x * 10 + c - '0', c = get();
	}
}

void $(int &x, int y) {
	(x += y) %= P;
}

struct Mat {
	int a[2][2];
	Mat() {
		memset(a, 0, sizeof a);
	}
	Mat(int f1, int f2) {
		a[0][0] = f1; a[1][1] = f2;
		a[0][1] = a[1][0] = 0;
	}
	int * operator [] (const int x) {
		return a[x];
	}
	friend Mat operator + (Mat x, Mat y) {
		Mat z; static int i, j;
		for (i = 0; i < 2; i++)
			for (j = 0; j < 2; j++)
				$(z.a[i][j], x[i][j] + y[i][j]);
		return z;
	}
	friend Mat operator * (Mat x, Mat y) {
		Mat z; static int i, j, k;
		for (i = 0; i < 2; i++)
			for (j = 0; j < 2; j++)
				for (k = 0; k < 2; k++)
					$(z.a[i][j], (LL)x[i][k] * y[k][j] % P);
		return z;
	}
} w[V];

void InitMat(int n) {
	int i, j;
	w[1].a[0][0] = 0; w[1].a[1][0] = w[1].a[0][1] = w[1].a[1][1] = 1;
	for (i = 2; i <= n; i++) w[i] = w[i - 1] * w[1];
}

int Mulx(Mat x, int y) {
	if (!y) return x.a[0][0];
	Mat mt = x * w[y];
	return (mt[0][0] + mt[1][0]) % P;
}
int Kth(int A, int B, int k) {
	return Mulx(Mat(A, B), k - 1);
}

int N, M, a[V];
int tagA[V << 2], tagB[V << 2], sum[V << 2];
void pushUp(int o) {
	sum[o] = (sum[o << 1] + sum[o << 1 | 1]) % P;
}
void build(int o, int l, int r) {
	if (l == r) {
		sum[o] = a[l]; return;
	}
	int Mid = (l + r) >> 1;
	build(o << 1, l, Mid); build(o << 1 | 1, Mid + 1, r);
	pushUp(o);
}
void SetT(int o, int A, int B, int l) {
	(tagA[o] += A) %= P; (tagB[o] += B) %= P; sum[o] = ((LL)sum[o] + Kth(A, B, l + 2) - B + P) % P;
}
void pushDown(int o, int l, int r) {
	if (tagA[o] && tagB[o]) {
		int Mid = (l + r) >> 1;
		SetT(o << 1, tagA[o], tagB[o], Mid - l + 1);
		int rA = Kth(tagA[o], tagB[o], Mid - l + 2),
			rB = Kth(tagA[o], tagB[o], Mid - l + 3);
		SetT(o << 1 | 1, rA, rB, r - Mid);
		tagA[o] = tagB[o] = 0;
	}
}
void Modify(int o, int l, int r, int L, int R, int A, int B) {
	if (l == L && r == R) {
		SetT(o, A, B, r - l + 1);
		return;
	}
	int Mid = (l + r) >> 1;
	pushDown(o, l, r);
	if (R <= Mid) Modify(o << 1, l, Mid, L, R, A, B);
	else if (Mid < L) Modify(o << 1 | 1, Mid + 1, r, L, R, A, B);
	else {
		int rA = Kth(A, B, Mid - L + 2),
			rB = Kth(A, B, Mid - L + 3);
		Modify(o << 1, l, Mid, L, Mid, A, B);
		Modify(o << 1 | 1, Mid + 1, r, Mid + 1, R, rA, rB);
	}
	pushUp(o);
}
int Query(int o, int l, int r, int L, int R) {
	if (l == L && r == R) return sum[o];
	int Mid = (l + r) >> 1;
	pushDown(o, l, r);
	if (R <= Mid) return Query(o << 1, l, Mid, L, R);
	else if (Mid < L) return Query(o << 1 | 1, Mid + 1, r, L, R);
	return (Query(o << 1, l, Mid, L, Mid) + Query(o << 1 | 1, Mid + 1, r, Mid + 1, R)) % P;
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int i, j;
	InitMat(V - 1);
	Read(N); Read(M);
	for (i = 1; i <= N; i++) Read(a[i]);
	build(1, 1, N);
	int op, l, r;
	while (M--) {
		Read(op); Read(l); Read(r);
		if (op & 1) {
			Modify(1, 1, N, l, r, 1, 1);
		}
		else {
			printf("%d\n", Query(1, 1, N, l, r));
		}
	}
	return 0;
}
