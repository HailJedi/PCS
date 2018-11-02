#include <bits/stdc++.h>

using namespace std;

#define dig2 fixed << setprecision(2)
const double INF = 1e18;
const int N = 12;
const int LCM = 2520;
int n, l;
int lim_x[N], lim_y[N];
int xs, ys, xt, yt, t1, t2;
double f[N][N][LCM * N * 2];

double trans(double t) {
	return t / LCM * l * 12;
}

double fuel(int v) {
	return l / (80 - 0.03 * v * v);
}

int cmp(double x, double y) {
	double t = x - y;
	if (fabs(t) < 1e-8) {
		return 0;
	}
	return t < 0 ? -1 : 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> l;
	for (int i = 1; i <= n; i++) {
		cin >> lim_x[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> lim_y[i];
	}
	cin >> xs >> ys >> xt >> yt >> t1 >> t2;
	int dtx = abs(xs - xt), dty = abs(ys - yt);
	for (int i = 0; i <= dtx; i++) {
		for (int j  = 0; j <= dty; j++) {
			for (int k = 0; k <= 2 * n * LCM; k++) {
				f[i][j][k] = INF;
			}
		}
	}
	f[0][0][0] = 0;
	int x, y, t;
	int dx = xs < xt ? 1 : -1, dy = ys < yt ? 1 : -1;
	for (int i = 0; i <= dtx; i++) {
		for (int j = 0; j <= dty; j++) {
			for (int k = 0; k <= 2 * n * LCM; k++) {
				if (f[i][j][k] != INF) {
					x = i + 1, y = j;
					if (x <= dtx) {
						for (int v = 1; v * 5 <= lim_x[ys + y * dy]; v++) {
							f[x][y][k + LCM / v] = min(f[x][y][k + LCM / v], f[i][j][k] + fuel(v * 5));
						}
					}
					x = i, y = j + 1;
					if (y <= dty) {
						for (int v = 1; v * 5 <= lim_y[xs + x * dx]; v++) {
							f[x][y][k + LCM / v] = min(f[x][y][k + LCM / v], f[i][j][k] + fuel(v * 5));
						}
					}
				}
			}
		}
	}
	bool ok = true;
	double oil = INF, tim = 0;
	for (int t = 0; cmp(trans(t), t2) <= 0; t++) {
		if (cmp(trans(t), t1) < 0) {
			continue;
		}
		if (ok && f[dtx][dty][t] != INF) {
			cout << (int)ceil(trans(t)) << ' ' << dig2 << f[dtx][dty][t] << endl;
			ok = false;
		}
		if (cmp(f[dtx][dty][t], oil) < 0) {
			oil = f[dtx][dty][t];
			tim = t;
		}
	}
	if (ok) {
		cout << "No" << endl;
	} else {
		cout << (int)ceil(trans(tim)) << ' ' << dig2 << oil << endl;
	}
	return 0;
}