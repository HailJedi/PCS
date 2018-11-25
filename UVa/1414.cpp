#include <bits/stdc++.h>

using namespace std;

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n;
	while (scanf("%d", &n) == 1) {
		int to[3] = {-1, -1, -1};
		for (int i = 0; i < 6; i++) {
			char s[3];
			scanf("%s", s);
			if (to[s[0]-'A'] == -1) {
				to[s[0]-'A'] = s[1]-'A';
			}
		}
		int a = 0, b = 0;
		if (to[1] != 0 && to[2] != 0) {
			a = 3,  b = 0;
		} else
		if (to[to[0]] == 0) {
			a = 3, b = 2;
		} else {
			a = 2, b = 1;
		}
		int64_t f[2] = {0};
		f[1] = 1;
		int t = 1;
		for (int i = 2; i <= n; i++) {
			t ^= 1;
			f[t] = f[t^1] * a + b;
		}
		printf("%lld\n", f[t]);
	}
	return 0;
}