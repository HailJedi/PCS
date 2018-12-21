/*
Created 2018-12-13
"工艺"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;

int n;
int str[N];

int main() {
	// freopen("read.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &str[i]);
	}
	int i = 0, j = 1, k = 0;
	while (i < n && j < n && k < n) {
		int t = str[(i+k)%n] - str[(j+k)%n];
		if (t == 0) {
			k++;
		} else {
			if (t > 0) {
				i += k+1;
			} else {
				j += k+1;
			}
			j += i == j;
			k = 0;
		}
	}
	int st = min(i, j);
	printf("%d ", str[st]);
	for (int p = (st+1)%n; p != st; p = (p+1)%n) {
		printf("%d ", str[p]);
	}
	puts("");
	return 0;
}