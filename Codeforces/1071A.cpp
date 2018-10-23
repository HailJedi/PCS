/*
Created 2018-10-23
"Cram Time"
A greedy solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

bool vis[N];

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	int p = 0;
	while (1LL * (p+1) * (p+2) / 2 <= a + b) {
		p++;
	}
	int suma = 0;
	for (int i = p; i >= 1; i--) {
		if (a >= i) {
			a -= i;
			suma++;
			vis[i] = true;
		}
	}
	printf("%d\n", suma);
	for (int i = 1; i <= p; i++) {
		if (vis[i]) {
			printf("%d ", i);
		}
	}
	printf("\n");
	printf("%d\n", p-suma);
	for (int i = 1; i <= p; i++) {
		if (!vis[i]) {
			printf("%d ", i);
		}
	}
	printf("\n");
	return 0;
}
