/*
Created 2018-10-27
"USACO 2012 February Contest, Gold Division
Problem 2. Symmetry"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const double eps = 1e-10;

struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	bool operator < (const Point &pt) const {
		if (x != pt.x) {
			return x < pt.x;
		}
		return y < pt.y;
	}
} pt[N];

set<Point> st;
set<double> xs, ys;
set<pair<double, double>> slp;

int n;

void calc_from_point(Point &p1, Point &p2, double &k, double &b) {
	k = (p1.y - p2.y) / (p1.x - p2.x);
	b = p1.y - p1.x * k;
}

void calc_from_axis(Point &p1, Point &p2, double &k, double &b) {
	double x_2 = (p1.x + p2.x) / 2;
	double y_2 = (p1.y + p2.y) / 2;
	double k_0 = (p1.y - p2.y) / (p1.x - p2.x);
	k = -1 / k_0;
	b = y_2 - k * x_2;
}

bool is_integer(double x) {
	return fabs(x - round(x) < eps);
}

bool check(double k, double b) {
	for (int i = 1; i <= n; i++) {
		double x_0 = pt[i].x, y_0 = pt[i].y;
		double x_1 = (x_0 + 2 * y_0 * k - k * k * x_0 - 2 * b * k) / (k * k + 1);
		double y_1 = (x_0 - x_1) / k + y_0;
		if (is_integer(x_1) && is_integer(y_1)) {
			x_1 = round(x_1), y_1 = round(y_1);
			if (!st.count(Point(x_1, y_1))) {
				return false;
			}
		} else {
			return false;
		}
	}
	return true;
}

bool check_x(double x) {
	for (int i = 1; i <= n; i++) {
		double x_0 = pt[i].x, y_0 = pt[i].y;
		double x_1 = 2 * x - x_0;
		double y_1 = y_0;
		if (!st.count(Point(x_1, y_1))) {
			return false;
		}
	}
	return true;
}

bool check_y(double y) {
	for (int i = 1; i <= n; i++) {
		double x_0 = pt[i].x, y_0 = pt[i].y;
		double x_1 = x_0;
		double y_1 = 2 * y - y_0;
		if (!st.count(Point(x_1, y_1))) {
			return false;
		}
	}
	return true;
}

int main() {
	freopen("symmetry.in", "r", stdin);	
	freopen("symmetry.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf %lf", &pt[i].x, &pt[i].y);
		st.insert(pt[i]);
	}
	double k, b;
	int ans = 0;
	for (int i = 2; i <= n; i++) {
		if (pt[1].x == pt[i].x) {
			ans += check_x(pt[1].x) && !xs.count(pt[1].x);
			xs.insert(pt[1].x);
		} else 
		if (pt[1].y == pt[i].y) {
			ans += check_y(pt[1].y) && !ys.count(pt[1].y);
			ys.insert(pt[1].y);
		} else {
			calc_from_point(pt[1], pt[i], k, b);
			ans += check(k, b) && !slp.count(make_pair(k, b));
			slp.insert(make_pair(k, b));
		}
	}
	for (int i = 2; i <= n; i++) {
		if (pt[1].x == pt[i].x) {
			ans += check_y((pt[1].y + pt[i].y) / 2) && !ys.count((pt[1].y + pt[i].y) / 2);
			ys.insert((pt[1].y + pt[i].y) / 2);
		} else 
		if (pt[1].y == pt[i].y) {
			ans += check_x((pt[1].x + pt[i].x) / 2) && !xs.count((pt[1].x + pt[i].x) / 2);
			xs.insert((pt[1].x + pt[i].x) / 2);
		} else {
			calc_from_axis(pt[1], pt[i], k, b);
			ans += check(k, b) && !slp.count(make_pair(k, b));
			slp.insert(make_pair(k, b));
		}
	}
	printf("%d\n", ans);
	return 0;
}

