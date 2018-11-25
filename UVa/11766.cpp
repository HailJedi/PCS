#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int A = 1500 + 5;

int w[A][A];
int f[N];

void update(int &x, int y) {
	if (x < y) {
		x = y;
	}
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		memset(w, 0, sizeof w);
		for (int i = 1; i <= n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			w[a+1][n-b]++;
		}
		f[0] = 0;
		for (int i = 1; i <= n; i++) {
			f[i] = 0;
			for (int j = 0; j < i; j++) {
				update(f[i], f[j] + min(w[j+1][i], i-j));
			}
		}
		printf("Case %d: %d\n", ++kase, n-f[n]);
	}
	return 0;
}