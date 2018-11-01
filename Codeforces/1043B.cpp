/*
Created 2018-11-01
"Lost Array"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];
int x[N];

int main() {
//	freopen("test.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	vector<int> ans;
	for (int k = 1; k < n; k++) {
		memset(x, INF, sizeof x);
		bool ok = true;
		x[0] = a[1];
		for (int j = 1; j < n; j++) {
			if (x[j%k] != INF && x[j%k] != a[j+1] - a[j]) {
				ok = false;
				break;
			}
			x[j%k] = a[j+1] - a[j];
		}
		if (ok) {
			ans.push_back(k);
		}
	}
	ans.push_back(n);
	printf("%d\n", (int)ans.size());
	for (int e: ans) {
		printf("%d ", e);
	}
	printf("\n");
	return 0;
}
