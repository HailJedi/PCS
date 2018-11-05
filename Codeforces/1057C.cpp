/*
Created 2018-11-05
"Tanya and Colored Candies"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int K = 2500 + 5;
const int INF = 0x3f3f3f3f;

int inq[N][K];
int f[N][K];
char col[N];
int r[N];

bool update(int &x, int y) {
	if (x > y) {
		x = y;
		return true;
	}
	return false;
}

int main() {
	int n, s, k;
	scanf("%d %d %d", &n, &s, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &r[i]);
	}
	scanf("%s", col+1);
	memset(f, INF, sizeof f);
	queue<pair<int, int>> q;
	for (int i = 1; i <= n; i++) {
		int d = abs(i - s);
		f[i][r[i]] = d;
		inq[i][r[i]] = true;
		q.push(make_pair(i, r[i]));
	}
	while (!q.empty()) {
		int p = q.front().first, e = q.front().second;
		q.pop();
		inq[p][e] = false;
		for (int i = 1; i <= n; i++) {
			if (r[i] > r[p] && col[i] != col[p]) {
				if (update(f[i][e + r[i]], f[p][e] + abs(i - p))) {
					if (!inq[i][e + r[i]]) {
						inq[i][e + r[i]] = true;
						q.push(make_pair(i, e + r[i]));
					}
				}
			}
		}
	}
	int ans = INF;
	for (int i = 1; i <= n; i++) {
		for (int j = k; j < K; j++) {
			update(ans, f[i][j]);
		}
	}
	if (ans == INF) {
		ans = -1;
	}
	printf("%d\n", ans);
	return 0;
}

