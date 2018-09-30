#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, k;
int fa[256], r[256], p[N];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for (int i = 0; i < 256; i++) fa[i] = i, r[i] = i;
	for (int i = 1; i <= n; i++) {
		if (find(p[i]) == p[i] && r[p[i]] == p[i]) {
			for (int j = max(0, r[p[i]]-k+1); j <= p[i]; j++) {
				int find_j = find(j);
				if (p[i] - find_j < k) {
					r[find_j] = p[i];
					for (int l = find_j; l <= p[i]; l++) fa[l] = find_j;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", find(p[i]));
	puts("");
	return 0;
}