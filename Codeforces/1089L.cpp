/*
Created 2018-12-02
"Lazyland"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

bool taken[N];

struct Worker {
	int a, b;
	bool operator < (const Worker &wk) const {
		return b > wk.b;
	}
} worker[N];

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &worker[i].a);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &worker[i].b);
	}
	sort(worker+1, worker+1+n);
	vector<int> rest;
	int done = 0;
	for (int i = 1; i <= n; i++) {
		if (!taken[worker[i].a]) {
			taken[worker[i].a] = true;
			done++;
		} else {
			rest.push_back(worker[i].b);
		}
	}
	long long ans = 0;
	sort(rest.begin(), rest.end());
	for (int i = 0; i < (int)rest.size() && done < k; i++, done++) {
		ans += rest[i];
	}
	printf("%lld\n", ans);
	return 0;
}