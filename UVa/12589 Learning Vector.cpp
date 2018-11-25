#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

const int INF = 1e9;
const int maxn = 50+5;
int area[maxn][maxn*maxn];
struct Vector { 
	int x, y; 
	Vector(int x = 0, int y = 0) : x(x), y(y) {}
	bool operator < (const Vector &rhs) const {
		return x * rhs.y - y * rhs.x < 0;
	}
} vec[maxn];

int main() {
	int T; scanf("%d", &T);
	int N, K, H;
	for (int kase = 1; kase <= T; kase++) {
		scanf("%d%d", &N, &K);
		H = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d%d", &vec[i].x, &vec[i].y);
			H += vec[i].y;
		}
		sort(vec+1, vec+1+N);

		memset(area, -1, sizeof(area));
		area[0][0] = 0;
		for (int i = 1; i <= N; i++)
			for (int j = min(i, K); j >= 0; j--)
				for (int k = 0; k <= H; k++)
					if (~area[j][k]) {
						area[j+1][k+vec[i].y] = max(area[j+1][k+vec[i].y],
							area[j][k] + vec[i].x * (2 * k + vec[i].y));
					}

		int ans = 0;
		for (int i = 0; i <= H; i++)
			ans = max(ans, area[K][i]);
		printf("Case %d: %d\n", kase, ans);
	}
	return 0;
}