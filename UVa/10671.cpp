#include <bits/stdc++.h>

using namespace std;

const int BUF = 210;
const int L = 100 + 5;
const int R = 1000 + 5;
const int N = 10 + 5;
const double INF = 1e18;
const double eps = 1e-9;

double gas[N][N][BUF*R*2];
int h_lim[N], v_lim[N];

int gcd(int x, int y) {
	return !y ? x : gcd(y, x % y);
}

void update(double &x, double y) {
	if (x > y) {
		x = y;
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T, kase = 0;
	scanf("%d", &T);
	while (T--) {
		int n, l;
		scanf("%d %d", &n, &l);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &h_lim[i]);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &v_lim[i]);
		}
		int sx, sy, tx, ty, st, ed;
		int buf = BUF / gcd(l, BUF);
		scanf("%d %d %d %d %d %d", &sx, &sy, &tx, &ty, &st, &ed);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 0; k <= ed*buf; k++) {
					gas[i][j][k] = INF;
				}
			}
		}
		gas[sx][sy][0] = 0;
		int dx = sx < tx ? 1 : -1;
		int dy = sy < ty ? 1 : -1;
		for (int i = 0; i <= abs(sx-tx); i++) {
			for (int j = 0; j <= abs(sy-ty); j++) {
				int cx = sx + i * dx, cy = sy + j * dy;
				for (int t = 0; t <= ed*buf; t++) {
					if (gas[cx][cy][t] != INF) {
						for (int v = 5; v <= h_lim[cy]; v += 5) {
							update(gas[cx+dx][cy][t+l*60*buf/v], gas[cx][cy][t] + l/(80-0.03*v*v));
						}
						for (int v = 5; v <= v_lim[cx]; v += 5) {
							update(gas[cx][cy+dy][t+l*60*buf/v], gas[cx][cy][t] + l/(80-0.03*v*v));
						}
					}
				}
			}
		}
		printf("Scenario %d:\n", ++kase);
		double mn_gas = INF;
		int mn_t = -1, done = 0;
		for (int t = st*buf; t <= ed*buf; t++) {
			if (gas[tx][ty][t] != INF && !done) {
				printf("The earliest  arrival: %d minutes, fuel %.2lf gallons\n", (int)((double)t/buf+1-eps), gas[tx][ty][t]);
				done = 1;
			}
			if (gas[tx][ty][t] < mn_gas) {
				mn_gas = gas[tx][ty][t];
				mn_t = (double)t/buf+1-eps;
			}
		}
		if (mn_t == -1) {
			puts("IMPOSSIBLE");
		} else {
			printf("The economical travel: %d minutes, fuel %.2lf gallons\n", mn_t, mn_gas);
		}
	}
	return 0;
}