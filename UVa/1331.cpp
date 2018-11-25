#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const double eps = 1e-9;

struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
} pt[N];

Point operator -(const Point p1, const Point p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

double cross(Point p1, Point p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

double area(int i, int j, int k) {
	return fabs(cross(pt[i]-pt[j], pt[k]-pt[j])) / 2;
}

double f[N][N];
int g[N][N][N];
int n;

int good(int i, int j, int k) {
	if (g[i][j][k] != -1) {
		return g[i][j][k];
	}
	double a = area(i, j, k);
	for (int p = 0; p < n; p++) {
		if ((p-i) * (p-j) * (p-k)) {
			double b = area(i, j, p) + area(j, k, p) + area(i, k, p);
			if (fabs(a-b) < eps) {
				return g[i][j][k] = 0;
			}
		}
	}
	return g[i][j][k] = 1;
}

double dp(int i, int j) {
	if (f[i][j] != -1) {
		return f[i][j];
	}
	f[i][j] = 1e18;
	for (int k = (i+1) % n; k != j; k = (k+1) % n) {
		if (good(i, j, k)) {
			f[i][j] = min(f[i][j], max(max(dp(i, k), dp(k, j)), area(i, k, j)));
		}
	}
	return f[i][j];
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &pt[i].x, &pt[i].y);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				f[i][j] = -1;
			}
		}
		for (int i = 0; i+1 < n; i++) {
			f[i][i+1] = 0;
		}
		f[n-1][0] = 0;
		memset(g, -1, sizeof g);
		double ans = 1e18;
		for (int i = 0; i < n; i++) {
			ans = min(ans, dp(i, (i+n-1)%n));
		}
		printf("%.1lf\n", ans);
	}
	return 0;
}
