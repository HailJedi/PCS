#include <bits/stdc++.h>

using namespace std;

#define dig3 fixed << setprecision(3)
typedef long double db;
const int N = 1e3+5;
const db PI = acosl(-1.0);
const db eps = 1e-10;

int cmp(db x, db y) {
	db dif = x - y;
	return fabs(dif) <= eps ? 0 : dif > 0 ? 1 : -1;
}

struct Point {
	db x, y;
	Point() {}
	Point(db x, db y) : x(x), y(y) {}
	Point operator - (const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	bool operator == (const Point &p) const {
		return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
	}
};

typedef Point Vector;

db dot(Vector v1, Vector v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

db cross(Vector v1, Vector v2) {
	return v1.x * v2.y - v2.x * v1.y;
}

db p2p(Point &a, Point &b) {
	return sqrt(dot(a - b, a - b));
}

db r(db x) {
	while (cmp(x, 0) < 0) {
		x += 2 * PI;	
	}
	return x;
}

db len(Vector &vec) {
	return sqrt(dot(vec, vec));
}

db angle(Vector vec) {
	db ret = 0;
	if (cmp(vec.y, 0) < 0) {
		ret += PI;
		vec.x *= -1.0;
		vec.y *= -1.0;
	}
	if (cmp(vec.x, 0) < 0) {
		ret += PI / 2;
		swap(vec.x, vec.y);
		vec.y *= -1;
	}
	if (vec.x == 0) {
		return ret + PI / 2;
	}
	db t = vec.y / vec.x;
	return ret + atanl(t);
}

struct Touch {
	db s, t;
	Touch() {}
	Touch(db s, db t) : s(s), t(t) {}
	bool operator < (const Touch &in) const {
		return cmp(s, in.s) < 0;
	}
};

struct Circle {
	Point c;
	db r;
	vector<Touch> inters;
	Circle() {}
} circle[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, t;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> circle[i].r >> circle[i].c.x >> circle[i].c.y;
		circle[i].inters.clear();
	}
	db ans = 0;
	for (int i = 1; i <= n; i++) {
		vector<Touch> &vec = circle[i].inters;
		for (int j = i + 1; j <= n; j++) {
			Point &c1 = circle[j].c, &c2 = circle[i].c;
			db r1 = circle[j].r, r2 = circle[i].r;
			db d = p2p(c1, c2);
			if (cmp(d, r1 - r2) <= 0) {
				vec.push_back(Touch(0, 2 * PI));
				break;
			}
			if (cmp(d, r1 + r2) < 0 && cmp(d, fabs(r1 - r2)) > 0) {
				db a2 = acosl((r2 * r2 - r1 * r1 + d * d) / (2 * d * r2));
				db ak = angle(c1 - c2);
				db low = r(ak - a2);
				vec.push_back(Touch(low, low + 2 * a2));
			} 
		}
		if (!vec.empty()) {
			sort(vec.begin(), vec.end());
			db up = vec[0].s + 2 * PI;
			for (int j = 0; j < vec.size(); j++) {
				vec[j].t = min(vec[j].t, up);
			}
			// cout << dig3 << vec[0].s / PI << ' ' << vec[0].t / PI << ' ' << vec.back().s / PI << ' ' << vec.back().t / PI << ' ';
		}
		db angle = 2 * PI;
		int lp = 0, rp = 0;
		while (lp < vec.size()) {
			rp = lp;
			db far = vec[rp].t, cls = vec[lp].s;
			while (rp+1 < vec.size() && cmp(vec[rp+1].s, far) <= 0) {
				rp++;
				far = max(far, vec[rp].t);
			}
			angle -= (far - cls);
			lp = rp + 1;
		}
		angle += eps;
		// cout << dig3 << angle << endl;
		ans += angle * circle[i].r;
	}
	cout << dig3 << ans << endl;
	return 0;
}