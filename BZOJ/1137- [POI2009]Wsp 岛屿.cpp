#include <bits/stdc++.h>

using namespace std;

typedef double db;
const int N = 1e5+5;
const int M = 1e6+5;
const db eps = 1e-7;
const db INF = 1e18;
vector<int> baned[N];
int n, m, u, v;

int cmp(db x, db y) {
	if (fabs(x - y) < eps) {
		return 0;
	}
	return x < y ? -1 : 1;
}

namespace P {

	struct Point {
		db x, y;
		Point(db x = 0, db y = 0) : x(x), y(y) {}
		Point operator + (const Point &p) const {
			return Point(x + p.x, y + p.y);
		}
		Point operator - (const Point &p) const {
			return Point(x - p.x, y - p.y);
		}
		Point operator * (const db m) const {
			return Point(x * m, y * m);
		}
		Point operator / (const db m) const {
			return Point(x / m, y / m);
		}
	} cord[N];

	typedef Point Vector;

	db cross(const Point &a, const Point &b) {
		return a.x * b.y - a.y * b.x;
	}

	db dot(Point &a, Point &b) {
		return a.x * b.x + a.y * b.y;
	}

	db dist(Point &a, Point &b) {
		return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	}

} using namespace P;

namespace HalfPlane {

	struct Line {
		Point p;
		Vector v;
		Line() {}
		Line(Point &p, Vector v) : p(p), v(v) {}
	};

	Point intersect(Line &l1, Line &l2) {
		Point u = l1.p - l2.p;
        db t = cross(l2.v, u) / cross(l1.v, l2.v);
        return l1.p + l1.v * t;
	}

	static Line stack[M];
	static int top = 0;

	bool toleft(const Line &l, const Point &p) {
        return cross((l.p - p), l.v) > eps;
    }

	void add(Line l) {
		while (top >= 2 && toleft(l, intersect(stack[top-1], stack[top])) ) {
			top--;
		}
		stack[++top] = l;  
	}

	db ask() {
		db ret = 0;
		Point lst = cord[1];
		for (int i = 2; i <= top; i++) {
			Point its = intersect(stack[i], stack[i-1]);
			ret += dist(lst, its);
			lst = its;
		}
		return ret + dist(cord[n], lst);
	}

} using namespace HalfPlane;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> cord[i].x >> cord[i].y;
	}
	for (int _ = 1; _ <= m; _++) {
		cin >> u >> v;
		if (u > v) {
			swap(u, v);
		}
		baned[u].push_back(v);
	}
	for (int i = 1; i <= n; i++) {
		sort(baned[i].begin(), baned[i].end());
	}
	int cur = 0;
	for (int i = 1; i <= n; i++) {
		int j, k;
		for (j = n, k = baned[i].size()-1; j > cur && k >= 0; j--, k--) {
			if (baned[i][k] != j) {
				break;
			}
		}
		if (j > cur) {
			add(Line(cord[i], cord[cur = j] - cord[i]));
		}
	}
	db ans = ask();
	cout << fixed << setprecision(9) << ans << endl;
	return 0;
}