#include <bits/stdc++.h>

using namespace std;

const int N = 20000 + 5;

int fa[N], d[N];

int find(int x) {
	if (fa[x] != x) {
		int root = find(fa[x]);
		d[x] += d[fa[x]];
		return fa[x] = root;
	} else {
		return x;
	}
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, u, v;
		char cmd[10];
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			d[i] = 0;
		}
		while (scanf("%s", cmd) && cmd[0] != 'O') {
			if (cmd[0] == 'E') {
				scanf("%d", &u);
				find(u);
				printf("%d\n", d[u]);
			} else {
				scanf("%d %d", &u, &v);
				fa[u] = v;
				d[u] = abs(u-v) % 1000;
			}
		}
	}
	return 0;
}
	
