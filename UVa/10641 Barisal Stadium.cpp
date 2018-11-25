#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = (1<<7);
const int maxm = (1<<10);
const int INF = 1e9;

struct Point {
	int x, y;
	Point(int x = 0, int y = 0) : x(x), y(y) {}
	Point operator + (const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	Point operator / (const double div) const {
		return Point(x / div, y / div);
	}
	int cross(const Point &rhs) const {
		return x * rhs.y - y * rhs.x;
	}
	void read() {
		scanf("%d%d", &x, &y);
	}
} points[maxn], lights[maxm];
int cost[maxm];

typedef Point Vector;

int n, m;
bool lighton[maxm][maxn];

void prepare() {
	for (int lit = 1; lit <= m; lit++) {
		for (int pt = 1, k = n; pt <= n; k = pt++) {
			Vector vec1 = points[k] - lights[lit];
			Vector vec2 = points[pt] - lights[lit];
			if (vec1.cross(vec2) < 0)
				lighton[lit][pt] = lighton[lit][pt+n] = 1;
			else lighton[lit][pt] = lighton[lit][pt+n] = 0;
		}
	}
}

int d[maxn][maxn];

void dp() {
	memset(d, 63, sizeof(d));
	for (int len = 1; len <= n; len++) {
		for (int l = 1; l + len - 1 <= 2 * n; l++) {
			int r = l+len-1;
			d[l][r] = INF;
			for (int lit = 1; lit <= m; lit++) {
				for (int p = l; p <= r && lighton[lit][p]; p++)
					d[l][r] = min(d[l][r], 
						(p + 1 <= r ? d[p+1][r] : 0) + cost[lit]);
				for (int p = r; p >= l && lighton[lit][p]; p--)
					d[l][r] = min(d[l][r],
						(p - 1 >= l ? d[l][p-1] : 0) + cost[lit]);
			}
		}
	}
}

void print() {
	int ans = INF;
	for (int i = 1; i <= 2*n; i++)
		ans = min(ans, d[i][i+n-1]);
	if (ans == INF) puts("Impossible.");
	else printf("%d\n", ans);
}

void solve() {
	prepare();
	dp();
	print();
}

bool read() {
	scanf("%d", &n);
	if (!n) return false;
	for (int i = 1; i <= n; i++) {
		points[i].read();
		points[i+n] = points[i];
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		lights[i].read();
		scanf("%d", &cost[i]);
	}
	return true;
}

int main() {
	while (read()) {
		solve();
	}
	return 0;
}