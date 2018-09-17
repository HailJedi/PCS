#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const int N = 10010;
const ld PI = acos(-1);

struct point {
	ld x, y;
	point() {}
	point(ld x, ld y) : x(x), y(y) {}
	point operator - (const point &p) const {
		return point(x-p.x, y-p.y);
	}
	ld dist(point &p) const {
		return sqrt(pow(x-p.x, 2) + pow(y-p.y, 2));
	}
} p[N], center;
int n, q;
ld dist[N], ang[N];

ld dot(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

ld cross(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

ld angle(int i, int j) {
	point p1 = p[i], p2 = p[j];
	return acos(dot(p1-center, p2-center) / (dist[i] * dist[j]));
}

point calc_centroid() {
	ld area = 0.0, tmp;
	point a, b, res = point(0, 0);
	for (int i = 1; i <= n; i++) {
		a = p[i], b = p[i%n+1];
		tmp = cross(a, b);
		area += tmp;
		res.x += (a.x + b.x) * tmp;
		res.y += (a.y + b.y) * tmp;
	}
	area *= 0.5;
	res.x /= (area * 6);
	res.y /= (area * 6);
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) 
		cin >> p[i].x >> p[i].y;
	ld sx = p[1].x, sy = p[1].y;
	for (int i = 1; i <= n; i++)
		p[i].x -= sx, p[i].y -= sy;
	center = calc_centroid();
	p[0] = p[1]; dist[0] = p[1].dist(center);
	for (int i = 1; i <= n; i++) {
		dist[i] = p[i].dist(center);
		ang[i] = atan2l(p[i].y-center.y, p[i].x-center.x);
		if (ang[i] < 0) ang[i] += 2 * PI;
	}
	int pin1 = 1, pin2 = 2, opt, pul, pin, v, f = true;
	for (int i = 1; i <= q; i++) {
		cin >> opt;
		if (opt == 1) {
			cin >> pul >> pin;
			int rot = pul == pin1 ? pin2 : pin1;
			if (!f && rot == pin2) {
				ld angle = ang[rot]-ang[pin1];
				p[rot].x = center.x - sin(angle) * dist[rot];
				p[rot].y = center.y + cos(angle) * dist[rot];
			}
			center.x = p[rot].x; center.y = p[rot].y - dist[rot];
			pin1 = rot, pin2 = pin;
			f = false;
		} else 
		if (opt == 2) {
			cin >> v;
			if (f) cout << fixed << setprecision(10) << p[v].x + sx << ' ' << p[v].y + sy << endl;
			else {
				ld angle = ang[v]-ang[pin1];
				cout << fixed << setprecision(10) << center.x - sin(angle) * dist[v] + sx << ' ' << center.y + cos(angle) * dist[v] + sy << endl;
			}
		}
	}
	return 0;
}