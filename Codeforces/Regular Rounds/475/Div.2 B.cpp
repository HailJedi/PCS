#include <bits/stdc++.h>

using namespace std;

int t[1010];
int n, A, B, C, T;

int main() {
	scanf("%d %d %d %d %d", &n, &A, &B, &C, &T);
	for (int i = 1; i <= n; i++)
		scanf("%d", &t[i]);
	if (C-B <= 0) printf("%d\n", n*A);
	else {
		int D = C-B, ans = 0;
		for (int i = 1; i <= n; i++)
			ans += A + (T-t[i])*D;
		printf("%d\n", ans);
	}
	return 0;
}