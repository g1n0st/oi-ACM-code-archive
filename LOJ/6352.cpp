#include <bits/stdc++.h>
using namespace std;

struct Xy {
	double x, y;
	Xy(double x = 0, double y = 0) : x(x), y(y) {}
};
struct Ar {
	double a, r;
	Ar(double a = 0, double r = 0) : a(a), r(r) {}
	void read() {
		cin >> a >> r;
		a /= 360.0; r /= 100.0;
	}
};

double RGB(double r, double g, double b) {
	return 0.30 * r + 0.59 * g + 0.11 * b;
}
double HSV(Ar val) {
	double a = val.a * 360.0, r = val.r;
	int h = floor(a / 60.0);
	double f = a / 60.0 - h;
	double p = 1 - r;
	double q = 1 - f * r;
	double t = 1 - (1 - f) * r;
	switch (h) {
	case 0: return RGB(1, t, p);
	case 1: return RGB(q, 1, p);
	case 2: return RGB(p, 1, t);
	case 3: return RGB(p, q, 1);
	case 4: return RGB(t, p, 1);
	case 5: return RGB(1, p, q);
	}
}

Ar a1, a2;
Xy b1, b2;

Xy ar_to_xy(Ar o) {
	return Xy(cos(o.a * M_PI * 2) * o.r, sin(o.a * M_PI * 2) * o.r);
}
Ar xy_to_ar(Xy o) {
	double a = atan2(o.y, o.x);
	double r = sqrt(o.x * o.x + o.y * o.y);
	if (a < 0) a += M_PI * 2;
	a /= M_PI * 2;
	return Ar(a, r);
}

int T;

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	cin >> T;
	while (T--) {
		a1.read(); a2.read();
		b1 = ar_to_xy(a1); b2 = ar_to_xy(a2);

		double ans = 0;

		for (double s = 0.0; s <= 1.0; s += 1.0 / 131072) {

			double x = s * b1.x + (1.0 - s) * b2.x;
			double y = s * b1.y + (1.0 - s) * b2.y;

			ans = max(ans, HSV(xy_to_ar(Xy(x, y))));
		}

		printf("%.4lf\n", ans);
	}
	return 0;
}
