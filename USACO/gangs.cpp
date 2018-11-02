/*
Created 2018-11-02
"USACO 2012 December Contest, Gold
Problem 1. Gangs of Instanbull/Cowstantinople"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int n, m;

void update(int &cur_cow, int &cur_gang, int cow_gang) {
	if (cur_cow == 0) {
		cur_gang = cow_gang;
	}
	if (cur_gang == cow_gang) {
		cur_cow++;
	} else {
		cur_cow--;
	}
}

int max_cow(int cur_cow, int cur_gang, vector<int> rest) {
	sort(rest.begin()+1, rest.end());
	while (rest[m-1] > 0) {
		for (int i = m-1; i > 0; i--) {
			rest[i]--;
			update(cur_cow, cur_gang, i);
			if (rest[i-1] <= rest[i]) {
				break;
			}
		}
	}
	for (int i = 1; i <= rest[0]; i++) {
		update(cur_cow, cur_gang, 0);
	}
	return cur_gang == 0 ? cur_cow : 0;
}

int main() {
	freopen("gangs.in", "r", stdin);
	freopen("gangs.out", "w", stdout);
	scanf("%d %d", &n, &m);
	vector<int> cows(m);
	for (int i = 0; i < m; i++) {	
		scanf("%d", &cows[i]);
	}
	int cur_cow = 0, cur_gang = 0;
	int rest = max_cow(cur_cow, cur_gang, cows);
	if (rest > 0) {
		puts("YES");
		printf("%d\n", rest);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < m; j++) {
				if (cows[j] > 0) {
					int cpy_cur_cow = cur_cow;
					int cpy_cur_gang = cur_gang;
					cows[j]--;
					update(cur_cow, cur_gang, j);
					if (max_cow(cur_cow, cur_gang, cows) == rest) {
						printf("%d\n", j+1);
						break;
					}
					cur_cow = cpy_cur_cow;
					cur_gang = cpy_cur_gang;
					cows[j]++;
				}
			}
		}
	} else {
		puts("NO");
	}
	return 0;
}
