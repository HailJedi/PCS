#include <bits/stdc++.h>

using namespace std;

const int N = 20000 + 5;

int fa[N], val[N];
int vis[N];
int n;

int find(int x) {
	if (x != fa[x]) {
		int f = fa[x];
		fa[x] = find(fa[x]);
		val[x] ^= val[f];
		return fa[x];
	}
	return x;
}

bool unite(int x, int y, int v) {
	int fx = find(x), fy = find(y);
	if (fx == fy) {
		return (val[x] ^ val[y]) == v;
	}
	if (fx == n) {
		swap(fx, fy);
	}
	fa[fx] = fy;
	val[fx] = val[x] ^ v ^ val[y];
	return true;
}

int main() {
	// freopen("read.in", "r", stdin);
	// freopen("write.out", "w", stdout);
	
	int Q, kase = 0;
	while (scanf("%d %d", &n, &Q) == 2 && n) {
		for (int i = 0; i <= n; i++) {
			fa[i] = i;
			val[i] = 0;
		}
		printf("Case %d:\n", ++kase);
		bool ok = true;
		int fact = 0;
		while (Q--) {
			char cmd[100], input[100];
			scanf("%s", cmd);
			if (cmd[0] == 'I') {
				gets(input);
				fact++;
				int x, y, v;
				if (sscanf(input, "%d %d %d", &x, &y, &v) == 2) {
					v = y;
					y = n;
				}
				if (!ok) {
					continue;
				}
				if (!unite(x, y, v)) {
					printf("The first %d facts are conflicting.\n", fact);
					ok = false;
				}
			} else {
				int k;
				scanf("%d", &k);
				vector<int> vec;
				int ans = 0;
				while (k--) {
					int x;
					scanf("%d", &x);
					ans ^= val[x];
					int fx = find(x);
					if (fx != n) {
						vis[fx] ^= 1;
						vec.push_back(fx);
					}
				}
				bool flag = true;
				for (int i = 0; i < vec.size(); i++) {
					flag &= (!vis[vec[i]]);
					vis[vec[i]] = 0;
				}
				if (!ok) {
					continue;
				}
				if (flag) {
					printf("%d\n", ans);
				} else {
					printf("I don't know.\n");
				}
			}
		}
		printf("\n");
	}
	return 0;
}
