#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

int pref[N][N], order[N][N];
int future_boy[N], future_girl[N];
int nxt[N];
queue<int> q;

void lady_choose(int girl, int boy) {
	int bulb = future_girl[boy];
	if (bulb) {
		future_boy[bulb] = 0;
		q.push(bulb);
	}
	future_boy[girl] = boy;
	future_girl[boy] = girl;
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &pref[i][j]);
			}
			nxt[i] = 1;
			future_boy[i] = 0;
			q.push(i);
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int x;
				scanf("%d", &x);
				order[i][x] = j;
			}
			future_girl[i] = 0;
		}
		while (!q.empty()) {
			int girl = q.front(); q.pop();
			int boy = pref[girl][nxt[girl]++];
			if (future_girl[boy] == 0) {
				lady_choose(girl, boy);
			} else 
			if (order[boy][girl] < order[boy][future_girl[boy]]) {
				lady_choose(girl, boy);
			} else {
				q.push(girl);
			}
		}
		while (!q.empty()) q.pop();
		for (int i = 1; i <= n; i++) {
			printf("%d\n", future_boy[i]);
		}
		if (T) {
			puts("");
		}
	}
	return 0;
}
