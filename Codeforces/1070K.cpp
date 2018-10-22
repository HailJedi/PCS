/*
Created 2018-10-22
"Video Posts"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n, k;
int a[N];

int main() {
	scanf("%d %d", &n, &k);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		sum += a[i];
	}
	if (sum % k != 0) {
		printf("No\n");
		return 0;
	}
	int ave = sum / k, cnt = 0;
	sum = 0;
	vector<int> ans;
	for (int i = 1; i <= n; i++) {
		sum += a[i];
		cnt++;
		if (sum == ave) {
			ans.push_back(cnt);
			sum = 0;
			cnt = 0;
		}
		if (sum > ave) {
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	for (int e: ans) {
		printf("%d ", e);
	}
	printf("\n");
	return 0;
}
