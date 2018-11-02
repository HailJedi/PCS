#include <bits/stdc++.h>

using namespace std;

const int maxn = 10010;

int num[maxn];
int blk[maxn];
int n;

bool Try() {
	for (int i = 1; i <= n; i++) {
		blk[i+1] = num[i]-blk[i]-blk[i-1];
		if (blk[i+1] != 1 && blk[i+1] != 0) return false;
	}
	return !blk[n+1];
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	int ans = 0;
	blk[1] = 0;
	if (Try()) ans++;
	blk[1] = 1;
	if (Try()) ans++;
	printf("%d\n", ans);
	return 0;
}