/*
Created 2018-11-07
"Compute Power"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const long long INF = 1e18;

struct Task {
	long long p, b;
	bool operator < (const Task &t) const {
		return p > t.p;
	}
} task[N];

int n;
long long f[2][N][N];
long long val[N];

void setV(int t) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			f[t][i][j] = INF;
		}
	}
}

void update(long long &x, long long y) {
	if (x > y) {
		x = y;
	}
}

bool check(long long thres) {
	for (int i = 1; i <= n; i++) {
		val[i] = task[i].p - thres * task[i].b;
	}
	int t = 0;
	setV(t);
	f[t][0][0] = 0;
	for (int i = 0; i < n; i++) {
		setV(t^1);
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k <= n; k++) {
				if (f[t][j][k] != INF) {
					int nj = 0, nk = 0;
					if (task[i+1].p == task[i].p) {
						nj = j, nk = k;
					} else {
						nj = j + k, nk = 0;
					}
					update(f[t^1][nj][nk+1], f[t][j][k] + val[i+1]);
					if (nj > 0) {
						update(f[t^1][nj-1][nk], f[t][j][k]);
					}
				}
			}
		}
		t ^= 1;
	}
	long long ret = INF;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			update(ret, f[t][i][j]);
		}
	}
	return ret <= 0;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &task[i].p);
		task[i].p *= 10000;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &task[i].b);
	}
	sort(task+1, task+1+n);
	long long l = 0, r = 1e13;
	while (r - l > 1) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	long long ans = ceil((double)r / 10);
	printf("%lld\n", ans);
	return 0;
}
