#include <bits/stdc++.h>

using namespace std;

const int N = 2e3+5;
const double PI = acos(-1);

struct Point {
	double x, y;
	Point () {}
	Point (double x, double y) : x(x), y(y) {}
	bool operator < (const Point &p) const {
		if (x != p.x) {
			return x < p.x;
		} 
		return y < p.y;
	}
	bool operator == (const Point &p) const {
		return x == p.x && y == p.y;
	}
	Point operator - (const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator + (const Point &p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator / (const double &d) const {
		return Point(x / d, y / d);
	}
	Point operator * (const double &d) const {
		return Point(x * d, y * d);
	}
} p[N];

typedef Point Vector;

double cross(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}

double dot(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}

bool toright(Vector a, Vector b) {
	return cross(a, b) >= 0;
}

double area(Point a, Point b, Point c) {
	return fabs(cross(a - b, c - b) / 2);
}

double len(Vector a) {
	return sqrt(dot(a, a));
}

double angle(Vector a) {
	double ret = 0;
	if (a.y < 0) {
		a.x *= -1;
		a.y *= -1;
		ret += PI;
	}
	return ret + acos(dot(a, Point(1, 0)) / len(a));
}

Point c; 

bool cmp(Point a, Point b) {
	return angle(a - c) < angle(b - c);
}

int n;
vector<Point> cvh;
Point sk[N];
int it;

void get_CVH() {
	sort(p+1, p+1+n);
	it = 0;
	for (int i = 1; i <= n; i++) {
		while (it >= 2 && toright(p[i] - sk[it], sk[it] - sk[it - 1])) {
			it--;
		}
		sk[++it] = p[i];
	}
	while (it) {
		cvh.push_back(sk[it--]);
	}
	for (int i = n; i >= 1; i--) {
		while (it >= 2 && toright(p[i] - sk[it], sk[it] - sk[it - 1])) {
			it--;
		}
		sk[++it] = p[i];
	}
	while (it) {
		cvh.push_back(sk[it--]);
	}
	sort(cvh.begin(), cvh.end());
	cvh.resize(unique(cvh.begin(), cvh.end()) - cvh.begin());
}

void get_c() {
	double ar = 0;
	c = Point(0, 0);
	Point p = cvh[0];
	for (int i = 1; i + 1 < n; i++) {
		Point cc = (p + cvh[i] + cvh[i + 1]) / 3;
		double a = area(p, cvh[i], cvh[i + 1]);
		c = c + cc * a;
		ar += a;
	}
	c = c / ar;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	int m = n;
	for (int i = 1; i <= n; i++) {
		cin >> p[i].x >> p[i].y;
	}
	get_CVH();
	n = cvh.size();
	c = Point(2e9, 2e9);
	for (int i = 0; i < n; i++) {
		if (cvh[i].y < c.y) {
			c = cvh[i];
		} else
		if (cvh[i].y == c.y && cvh[i].x < c.x) {
			c = cvh[i];
		}
	}
	sort(cvh.begin(), cvh.end(), cmp);
	get_c();
	sort(cvh.begin(), cvh.end(), cmp);
	double ans = 0;
	for (int i = 0; i < n; i++) {
		int lp = i, rp = (i + 1) % n;
		for (int j = i + 1; j < n; j++) {
			while (lp != j && area(cvh[lp + 1], cvh[i], cvh[j]) > area(cvh[lp], cvh[i], cvh[j])) {
				(lp += 1) %= n;
			}
			while (rp != i && area(cvh[rp + 1], cvh[i], cvh[j]) > area(cvh[rp], cvh[i], cvh[j])) {
				(rp += 1) %= n;
			}
			ans = max(ans, area(cvh[lp], cvh[i], cvh[j]) + area(cvh[rp], cvh[i], cvh[j]));
		}
	}
	cout << fixed << setprecision(3) << ans << endl;
	return 0;
}