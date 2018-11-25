#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int maxn = 20+5;

int cake[maxn][maxn];
int R, C, k;

int cherry[maxn][maxn][maxn][maxn];
int done[maxn][maxn][maxn][maxn];

int statis(int r, int c, int h, int w) {
	int &res = cherry[r][c][h][w];
	int &don = done[r][c][h][w];
	if (don) return res;
	if (h * w == 1) return res = cake[r][c];
	int midh = h / 2, midw = w / 2;
	if (h != 1) {
		res = statis(r, c, midh, w) 
			+ statis(r+midh, c, h-midh, w);
	} else {
		res = statis(r, c, h, midw) 
			+ statis(r, c+midw, h, w-midw);
	}
	return res;
}

void prepare() {
	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			for (int h = 1; r+h <= R+1; h++)
				for (int w = 1; c+w <= C+1; w++)
					cherry[r][c][h][w] = statis(r, c, h, w);
	// for (int r = 1; r <= R; r++)
		// for (int c = 1; c <= C; c++)
			// for (int h = 1; r+h <= R+1; h++)
				// for (int w = 1; c+w <= C+1; w++)
					// if (cherry[r][c][h][w]) 
						// cout << r << ' ' << c << ' ' << h << ' ' << w << ' ' << cherry[r][c][h][w] << endl;

}

int kase;
int dp[maxn][maxn][maxn][maxn];
int vis[maxn][maxn][maxn][maxn];
const int INF =  1e9;

int divide(int r, int c, int h, int w) {
	int &res = dp[r][c][h][w];
	int &tim = vis[r][c][h][w];
	if (cherry[r][c][h][w] == 0) return res = INF;
	if (cherry[r][c][h][w] <= 1) return res = 0;
	if (tim == kase) return res;
	tim = kase; res = INF;
	for (int cuth = 1; cuth < h; cuth++) {
		res = min(res, divide(r, c, cuth, w) 
					 + divide(r+cuth, c, h-cuth, w) + w);
	}
	for (int cutw = 1; cutw < w; cutw++) {
		res = min(res, divide(r, c, h, cutw) 
					 + divide(r, c+cutw, h, w-cutw) + h);
	}
	return res;
}


void solve() {
	cout << "Case " << ++kase << ": ";
	cout << divide(1, 1, R, C) << endl;
}

int main() {
	// freopen("read.in", "r", stdin);
	// freopen("write.out", "w", stdout);
	ios::sync_with_stdio(false);
	while (cin >> R >> C >> k && R) {
		memset(cake, 0, sizeof(cake));
		memset(cherry, 0, sizeof(cherry));
		for (int i = 1; i <= k; i++)  {
			int r, c;
			cin >> r >> c;
			cake[r][c] = 1;
		}
		prepare();
		solve();
	}
	return 0;
}
