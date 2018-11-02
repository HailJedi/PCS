#include <bits/stdc++.h>

using namespace std;

typedef long double ldb;
const int N = 300+5;
typedef pair<ldb, ldb> point;
#define x first
#define y second
point p[N];
int n;

point operator - (point &p1, point &p2) {
	return make_pair(p1.x - p2.x, p1.y - p2.y);
}

point operator + (point &p1, point &p2) {
	return make_pair(p1.x + p2.x, p1.y + p2.y);
}

point operator / (point &p1, ldb a) {
	return make_pair(p1.x / a, p1.y / a);
}

double operator * (point p1, point p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

struct line {
	ldb k, b;
	line() {}
	line(point &p1, point &p2) {
		point p = p2 - p1;
		k = p.y / p.x;
		b = p1.y - k * p1.x;
	}
	ldb f(ldb x) {
		return k * x + b;
	}
} l[N];

ldb pos, minh;

ldb Rand() {
	return rand() % 1000 / 1000.0;
}

bool inbound(ldb x) {
	return p[1].x <= x && x <= p[n].x;
}

bool judge(ldb x, ldb y) {
	for (int i = 1; i < n; i++) {
		if (l[i].f(x) > y) {
			return false;
		}
	}
	return true;
}

ldb f(ldb x) {
	for (int i = 1; i < n; i++) {
		if (p[i].x <= x && x <= p[i+1].x) {
			return l[i].f(x);
		}
	}
	return 0;
}

ldb bisrch(ldb x) {
	ldb l = 0, r = 1e18, h;
	while (r - l > 1e-7) {
		h = (l + r) / 2;
		if (judge(x, h)) {
			r = h;
		} else {
			l = h;
		}
	}
	h = (l + r) / 2 - f(x);
	if (h < minh) {
		pos = x;
		minh = h;
	}
	return h;
}

void SA(ldb T) {
	ldb cp = pos;
	while (T > 1e-5) {
		ldb cdp = cp + T * (Rand() * 2 - 1);
		if (inbound(cdp)) {
			ldb dE = bisrch(cp) - bisrch(cdp);
			if (dE > 0 || exp(dE / T) > Rand()) {
				cp = cdp;
			}
		}
		T *= 0.99;
	}
	for (int i = 1; i <= 1e3; i++) {
		ldb cdp = pos + T * (Rand() * 2 - 1);
		if (inbound(cdp)) {
			bisrch(cdp);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(NULL));
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
	pos = (p[1].x + p[n].x) / 2.0;
	minh = 1e18;
	SA(p[n].x - p[1].x);
	cout << fixed << setprecision(3) << minh << endl;
	return 0;
}