#include <bits/stdc++.h>

using namespace std;

const int N = 10;
const double eps = 1e-6;

int cmp(double x, double y) {
	double t = x - y;
	if (fabs(t) < eps) {
		return 0;
	} else {
		return t < 0 ? -1 : 1;
	}
}

struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	Point operator - (const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator + (const Point &p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator * (const double &d) const {
		return Point(x * d, y * d);
	}
	Point operator / (const double &d) const {
		return Point(x / d, y / d);
	}
	bool operator < (const Point &p) const {
		if (cmp(x, p.x) != 0) {
			return cmp(x, p.x) < 0;
		}
		return cmp(y, p.y) < 0;
	}
	bool operator == (const Point &p) const {
		return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
	}
	void read() {
		cin >> x >> y;
	}
	void print() {
		cout << x << ' ' << y << endl;
	}
};

typedef Point Vector;

typedef pair<Point, Point> fold;
#define fs first
#define sc second
fold fd[N];
int n, m;

double cross(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}

double dot(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}

bool toleft(Vector a, Vector b) {
	return cmp(cross(a, b), 0) < 0;
}

bool toright(Vector a, Vector b) {
	return cmp(cross(a, b), 0) > 0;
}

Point project(Point p, Point ed, Point bs) {
	Vector v = ed - bs;
	return bs + v * (dot(v, p - bs) / dot(v, v));
}

Point mirror(Point p, Point ed, Point bs) {
	Point pr = project(p, ed, bs);
	return p + (pr - p) * 2;
}

bool online(Point p, Point a, Point b) {
	return cmp(cross(a - p, b - p), 0) == 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		fd[i].fs.read();
		fd[i].sc.read();
	}
	cin >> m;
	Point p;
	for (int i = 1; i <= m; i++) {
		p.read();
		set<Point> st;
		st.insert(p);
		for (int j = n; j >= 1; j--) {
			for (set<Point>::iterator it = st.begin(); it != st.end(); ++it) {
				if (toleft(*it - fd[j].fs, fd[j].sc - fd[j].fs)) {
					st.insert(mirror(*it, fd[j].sc, fd[j].fs));
				}
			}
		}
		int ans = 0;
		for (set<Point>::iterator it = st.begin(); it != st.end(); ++it) {
			Point p2 = *it;
			if (cmp(p2.x, 0) <= 0 || cmp(p2.x, 100) >= 0 || cmp(p2.y, 0) <= 0 || cmp(p2.y, 100) >= 0) {
				continue;
			}
			bool ok = true;
			for (int j = 1; j <= n; j++) {
				if (online(p2, fd[j].fs, fd[j].sc)) {
					ok = false;
					break;
				}
			}
			if (!ok) {
				continue;
			}
			// ans++;
			// p2.print();
			for (int j = 1; j <= n; j++) {
				if (toright(p2 - fd[j].fs, fd[j].sc - fd[j].fs)) {
					// cout << p2.x << ' ' << p2.y << " transfered to ";
					p2 = mirror(p2, fd[j].sc, fd[j].fs);
					for (int k = 1; k <= n; k++) {
						if (online(p2, fd[k].fs, fd[k].sc)) {
							ok = false;
							break;
						}
					}
					if (!ok) break;
					// p2.print();
					// cout << "mirror is from " << fd[j].fs.x << ' ' << fd[j].fs.y << " to " << fd[j].sc.x << ' ' << fd[j].sc.y << endl;
				}
			}
			if (!ok) {
				continue;
			}
			// p2.print();
			if (p2 == p) {
				// p2.print();
				ans++;
			}
		}
		cout << ans << endl;
	}
	return 0;
}