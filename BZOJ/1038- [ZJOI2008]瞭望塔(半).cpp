#include <bits/stdc++.h>

using namespace std;

typedef long double ldb;
typedef pair<ldb, ldb> point;
#define x first
#define y second
const int N = 1e3+5;
const double eps = 1e-7;
ldb INF = 0;
point p[N];
int n;

point operator - (point &p1, point &p2) {
	return make_pair(p1.x - p2.x, p1.y - p2.y);
}

struct line {
	ldb k, b, x1, x2;
	line() {}
	line(point &p1, point &p2) {
		point p = p2 - p1;
		x1 = min(p1.x, p2.x);
		x2 = max(p1.x, p2.x);
		k = p.y / p.x;
		b = p1.y - k * p1.x;
	}
	ldb f(ldb x) const {
		return k * x + b;
	}
	bool operator < (const line &l) const {
		if (k != l.k) {
			return k < l.k;
		}
		return this->f(0) < l.f(0);
	}
} l[N];

ldb f(ldb x, int ll, int rr) {
	for (int i = ll; i < rr; i++) {
		if (l[i].x1 <= x && x <= l[i].x2) {
			return l[i].f(x);
		}
	}
	return 0;
}

ldb inter_x(line &l1, line &l2) {
	if (l1.k == l2.k) {
		return -INF;
	}
	return (l2.b - l1.b) / (l1.k - l2.k);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p[i].x;
	}
	for (int i = 1; i <= n; i++) {
		cin >> p[i].y;
	}
	for (int i = 1; i < n; i++) {
		l[i] = line(p[i], p[i+1]);
	}
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (l[i].k != l[j].k) {
				INF = max(INF, fabs(inter_x(l[i], l[j])));
			}
		}
	}
	INF *= 1e5;
	sort(l+1, l+n);
	vector<point> shell;
	vector<int> shape;
	for (int i = 1; i < n; i++) {
		ldb intx = -INF;
		while (!shape.empty()) {
			line &tl = l[shape.back()];	
			intx = inter_x(l[i], tl);
			if (intx <= shell.back().x) {
				shell.pop_back();
				shape.pop_back();
			} else {
				break;
			}
		}
		shape.push_back(i);
		shell.push_back(make_pair(intx, l[i].f(intx)));
	}
	shell.push_back(make_pair(INF, l[shape.back()].f(INF)));
	vector<ldb> pts;
	for (int i = 1; i <= n; i++) {
		pts.push_back(p[i].x);
	}
	int old_n = n;
	while (shell.size() >= 2) {
		point p1 = shell.back();
		shell.pop_back();
		point p2 = shell.back();
		l[n++] = line(p1, p2);
		pts.push_back(p1.x);
	}
	ldb ans = INF; 
	for (int i = 0; i < pts.size(); i++) {
		if (fabs(pts[i]) >= INF) {
			continue;
		}
		ldb bt = f(pts[i], 1, old_n);
		ldb tp = f(pts[i], old_n, n);
		ans = min(ans, tp - bt);
	}
	cout << fixed << setprecision(3) << ans + eps << endl;
	return 0;
}