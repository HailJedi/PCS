/*
Created 2018-11-01
"Smallest Word"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

int ans[N];
char str[N], cpy[N];
int n;

int compare(char *s1, char *s2) {
	for (int i = 1; i <= n; i++) {
		if (s1[i] != s2[i]) {
			return s1[i] < s2[i] ? -1 : 1;
		}
	}
	return 0;
}

int main() {
//	freopen("test.in", "r", stdin);
	scanf("%s", str+1);
	n = strlen(str+1);
	for (int i = 2; i <= n; i++) {
		memcpy(cpy, str, sizeof str);
		char t = cpy[i];
		for (int j = i; j >= 2; j--) {
			cpy[j] = cpy[j-1];
		}
		cpy[1] = t;
		if (compare(cpy, str) < 0) {
			ans[i-1] ^= 1;
			ans[i] ^= 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
