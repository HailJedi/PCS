#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int M = 1000 + 5;
const double INF = 1e18;

struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
} front[N], monu[M];

typedef Point Vector;

Vector operator - (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

double f[N];
bool good[N][N];

double cross(Vector v1, Vector v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

double dist(int i, int j) {
	return sqrt((front[i].x-front[j].x)*(front[i].x-front[j].x)
					+(front[i].y-front[j].y)*(front[i].y-front[j].y));
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &front[i].x, &front[i].y);
		}
		for (int i = 0; i < m; i++) {
			scanf("%lf %lf", &monu[i].x, &monu[i].y);
		}
		double ans = INF;
		if (m == 0) {
			for (int i = 0; i < n; i++) {
				for (int j = i+1; j < n; j++) {
					for (int k = j+1; k < n; k++) {
						if (cross(front[i]-front[j], front[k]-front[j]) != 0) {
							ans = min(ans, dist(i, j) + dist(j, k) + dist(k, i));
						}
					}
				}
			}
		} else {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) {
						good[i][j] = true;
						continue;
					}
					bool ok = true;
					Vector v = front[i] - front[j];
					for (int k = 0; k < m && ok; k++) {
						Vector w = monu[k] - front[j];
						ok &= (cross(v, w) < 0);
					}
					good[i][j] = ok;
				}
			}
			for (int st = 0; st != n; st++) {
				for (int i = 0; i < n; i++) {
					f[i] = INF;
				}
				f[st] = 0;
				for (int ed = (st+1)%n; ed != st; ed = (ed+1)%n) {
					for (int md = st; md != ed; md = (md+1)%n) {
						if (good[ed][md]) {
							f[ed] = min(f[ed], f[md] + dist(md, ed));
						}
					}
					if (good[st][ed]) {
						ans = min(ans, f[ed] + dist(ed, st));
					}
				}
			}
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}