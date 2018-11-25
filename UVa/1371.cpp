#include <bits/stdc++.h>

using namespace std;

char x[5005], y[55];
int f[5005][55];
int n, m;

void update(int &x, int y) {
	if (x > y) {
		x = y;
	}
}

bool good(int k) {
	memset(f, 0x3f3f3f3f, sizeof f);
	f[0][0] = 0;
	for (int i = 0; i <= n; i++) {
		if (f[i][m] <= k) {
			f[i][0] = 0;
		}
		for (int j = 0; j <= m; j++) {
			if (f[i][j] > k) {
				continue;
			}
			f[i+1][j] = min(f[i+1][j], f[i][j] + 1);
			f[i+1][j+1] = min(f[i+1][j+1], f[i][j] + (x[i] != y[j]));
			f[i][j+1] = min(f[i][j+1], f[i][j] + 1);
		}
	}
	return f[n][m] <= k;
}	

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s %s", y, x);
		n = strlen(x);
		m = strlen(y);
		int l = -1, r = m;
    while (r - l > 1) {
			int mid = (l + r)/2;
      if (good(mid)) {
        r = mid;
			} else {
        l = mid;
			}
    }
    printf("%d\n", r);
	}
	return 0;
}