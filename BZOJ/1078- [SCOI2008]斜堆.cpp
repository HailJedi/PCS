#include <bits/stdc++.h>

using namespace std;

const int N = 105;
int fa[N], lc[N], rc[N];
int n, d, root;
int ans[N];

void find(int u, int i) {
	if ((!lc[u] && !rc[u]) || (lc[u] && !rc[u] && lc[lc[u]])) {
		ans[i] = u;
		lc[fa[u]] = lc[u];
		fa[lc[u]] = fa[u];
		if (!fa[u]) {
			root = lc[u];
		}
	} else {
		find(lc[u], i);
		swap(lc[u], rc[u]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 2; i <= n + 1; i++) {
		cin >> d;
		d++;
		if (d < 100) {
			lc[d] = i;
		} else {
			d -= 100;
			rc[d] = i;
		}
		fa[i] = d;
	}
	root = 1;
	for (int i = 1; i <= n + 1; i++) {
		find(root, i);
	}
	for (int i = n + 1; i >= 2; i--) {
		cout << ans[i] - 1 << ' ';
	}
	cout << ans[1] - 1;
	return 0;
}