/*
Created 2018-11-26
"Write The Contest"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int P = 1000 + 5;
const double INF = 1e32;

void update(double &x, double y) {
	if (x > y) {
		x = y;
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m = 0;
		double C, T;
		scanf("%d %lf %lf", &n, &C, &T);
		vector<pair<int, int>> p(N);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &p[i].first, &p[i].second);
			m += p[i].second;
		}
		sort(p.begin(), p.end(), greater<pair<int, int>>());
		vector<double> pw(n+1);
		pw[0] = 1;
		for (int i = 1; i <= n; i++) {
			pw[i] = pw[i-1] * 0.9;
		}
		vector<vector<double>> f(n+1, vector<double>(m+1, INF));
		f[0][0] = 0;
		for (auto e: p) {
			for (int i = n; i >= 1; i--) {
				for (int j = m; j >= e.second; j--) {
					update(f[i][j], f[i-1][j-e.second] + e.first / pw[i]);
				}
			}
		}
		int ans = 0, ok = 0;
		for (int j = m; j >= 0 && !ok; j--) {
			for (int i = 1; i <= n; i++) {
				if (f[i][j] != INF) {
					double t = max(1 / C, sqrt(f[i][j] / C));
					if (f[i][j] / C / t + t - 1 / C + 10 * i <= T) {
						ans = j;
						ok = 1;
						break;
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
