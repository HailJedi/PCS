/*
Created 2018-11-06
"Compute Power"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int B = 100 + 5;
const int INF = 0x3f3f3f3f;

int f[2][N*B]; // #task, diff -> min total power

struct Task {
	int p, b;
	bool operator < (const Task &t) const {
		return p > t.p;
	}
} task[N];

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

int sumb[N];

int main() {
	freopen("test.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &task[i].p);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &task[i].b);
	}
	sort(task+1, task+1+n);
	int m = 0;
	for (int i = 1; i <= n; i++) {
		if (task[i].p == task[m].p) {
			task[m].b += task[i].b;
		} else {
			task[++m] = task[i];	
		}
	}
	n = m;
	for (int i = 1; i <= n; i++) {
		sumb[i] = sumb[i-1] + task[i].b;
	}
	int t = 0;
	memset(f[t], INF, sizeof f[t]);
	f[t][0] = 0;
	for (int i = 0; i < n; i++) {
		memset(f[t^1], INF, sizeof f[t^1]);
		for (int j = sumb[i] & 1; j <= sumb[i]; j += 2) {
			for (int k = 0; k <= min(j, task[i+1].b); k++) {
				int nj = j + (task[i+1].b - k) - k;
				update(f[t^1][nj], f[t][j] + (task[i+1].b - k) * task[i+1].p);
			}
		}
		t ^= 1;
	}
	double ans = 1e30;
	for (int i = sumb[n] & 1; i <= sumb[n]; i += 2) {
		int fst = (sumb[n] + i) / 2;
		ans = min(ans, (double)f[t][i] / fst);
		cout << fst << ' ' << f[t][i] << endl;
	}
	printf("%d\n", (int)(ans * 1000.0));
	return 0;
}
