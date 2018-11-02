#include <bits/stdc++.h>

using namespace std;

const int N = 500+5;
const int INF = 1e9;
const double eps = 1e-10;
typedef pair<double, double> Point;
#define x first
#define y second

double operator * (Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}

Point operator - (Point a, Point b) {
	return make_pair(a.x - b.x, a.y - b.y);
}

int n, m;
Point a[N], b[N];
int dist[N][N];
double k;

bool spj() {
	for (int i = 1; i <= n; i++) {
		if (fabs(a[i].x - a[1].x) > eps || fabs(a[i].y - a[1].y) > eps) {
			return false;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (fabs(b[i].x - a[1].x) > eps || fabs(b[i].y - a[1].y) > eps) {
			return false;
		}
	}
	puts("1");
	return true;
}

bool colinear(Point p, Point q) {
	if (p.x > q.x) {
		swap(p, q);
	}
	for (int i = 1; i <= m; i++) {
		if (b[i].x < p.x || b[i].x > q.x) {
			return false;
		}
	}
	if (p.y > q.y) {
		swap(p, q);
	}
	for (int i = 1; i <= m; i++) {
		if (b[i].y < p.y || b[i].y > q.y) {
			return false;
		}
	}
	return true;
}

int judge(Point p, Point q) {
	int c1 = 0, c2 = 0;
	for (int i = 1; i <= m; i++) {
		double t = (q - p) * (b[i] - p);
		if (t > eps) {
			c1++;
		} else
		if (t < -eps) {
			c2++;
		}
		if (c1 * c2) {
			return 0;
		}
	}
	if (c1 == 0 && c2 == 0 && colinear(p, q)) {
		puts("2");
		return -1;
	}
	if (c1 != 0) {
		return 1;
	} else
	if (c2 != 0) {
		return 2;
	} else {
		return 3;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = INF;
		}
	}
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y >> k;
		a[i].x /= k, a[i].y /= k;
	}
	for (int i = 1; i <= m; i++) {
		cin >> b[i].x >> b[i].y >> k;
		b[i].x /= k, b[i].y /= k;
	}
	if (spj()) {
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			int info = judge(a[i], a[j]);
			if (info == -1) {
				return 0;
			} else
			if (info == 1) {
				dist[i][j] = 1;
			} else
			if (info == 2) {
				dist[j][i] = 1;
			} else 
			if (info == 3) {
				dist[i][j] = dist[j][i] = 1;
			}
		}
	}
	int ans = INF;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			if (dist[i][k] < INF) {
				for (int j = 1; j <= n; j++) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		ans = min(ans, dist[i][i]);
	}
	if (ans >= INF || ans <= 2) {
		puts("-1");
	} else {
		cout << ans << endl;
	}
	return 0;
}