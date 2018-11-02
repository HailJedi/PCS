#include <bits/stdc++.h>

using namespace std;

const int N = 10010;
const int M = 4000010;

int nxt[M], to[M];
int hd[N], lhd[N];
int n, m, ct;
int que[N], deg[N];
bool vis[N];
int mark[N], col[N];

void add(int h[], int u, int v) {
	to[++ct] = v;
	nxt[ct] = h[u];
	h[u] = ct;
}

void mcs() {
	for (int i = 1; i <= n; i++)
		add(lhd, 0, i);
	int idx = 0, e;
	for (int i = n; i >= 1; i--) {
		while (true) {
			for (e = lhd[idx]; e; e = nxt[e]) {
				if (!vis[to[e]]) break;
				lhd[idx] = nxt[e];
			}
			if (e) {
				int x = to[e];
				que[i] = x;
				vis[x] = true;
				for (e = hd[x]; e; e = nxt[e]) {
					int v = to[e];
					if (!vis[v]) {
						deg[v]++;
						add(lhd, deg[v], v);
						idx = max(idx, deg[v]);
					}
				}
				break;
			} else idx--;
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	int u, v;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		add(hd, u, v);
		add(hd, v, u);
	}
	mcs();
	int ans = -1, cnt;
	for (int i = n; i >= 1; i--) {
		for (int j = hd[que[i]]; j; j = nxt[j]) mark[col[to[j]]] = i;
		for (cnt = 1; mark[cnt] == i; cnt++);
		col[que[i]] = cnt;
		ans = max(ans, cnt);
	}
	printf("%d\n", ans);

	return 0;
}