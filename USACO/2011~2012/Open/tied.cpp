/*
Created 2018-10-29
"USACO 2012 US Open, Gold Division
Problem 1. Tied Down"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 10 + 5;
const int M = 10000 + 5;
const double INF = 1e9;

struct Point {
	double x, y;
	Point() {}
} rop[M], bes;

int n, m;
double fen[N], fx;

double F(Point &p1, Point &p2, double x) {
	double k = (p1.y - p2.y) / (p1.x - p2.x);
	double b = p1.y - k * p1.x;
	return k * x + b;
}

int main() {
	freopen("tied.in", "r", stdin);	
	freopen("tied.out", "w", stdout);
	scanf("%d %d %lf %lf", &n, &m, &bes.x, &bes.y);
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf", &fx, &fen[i]);
	}
	for (int i = 1; i <= m+1; i++) {
		scanf("%lf %lf", &rop[i].x, &rop[i].y);
	}
	sort(fen, fen+n);
	int ans = 0;
	for (int s = 0; s < (1 << n); s++) {
		vector<double> ys;
		ys.push_back(-INF);
		for (int i = 0; i < n; i++) {
			if (s & (1 << i)) {
				ys.push_back(fen[i]);
			}
		}
		ys.push_back(INF);
		stack<int> stk;
		int lst = -1;
		for (int i = 1; i <= m; i++) {
			if ((fx - rop[i].x) * (fx - rop[i+1].x) <= 0 && rop[i].x != rop[i+1].x) {
				if (rop[i].x != fx) {
					int f = rop[i].x > fx ? 1 : -1;
					double y = F(rop[i], rop[i+1], fx);
					int id = lower_bound(ys.begin(), ys.end(), y) - ys.begin();
					if (!stk.empty() && stk.top() == -f * id) {
						stk.pop();
					} else {
						stk.push(f * id);
					}
				} else {
					if ((rop[lst].x - fx) * (rop[i+1].x - fx) > 0) {
						stk.pop();
					}
				}
				lst = i;
			}
		}
		if (stk.empty()) {
			ans = max(ans, __builtin_popcount(s));
		}
	}
	printf("%d\n", n - ans);
	return 0;
}
