#include <bits/stdc++.h>

using namespace std;

const int maxn = 200010; 

int n, e;
int hd[maxn], nxt[maxn<<1];
int to[maxn<<1], deg[maxn];
vector<int> ans;

void Link(int u, int v) {
	to[++e] = v; 
	nxt[e] = hd[u];
	hd[u] = e;
}

bool out[maxn];

void Walk2(int u, int fa) {
	if (deg[u]&1 || out[u]) return;
	ans.push_back(u);
	out[u] = true;
	for (int i = hd[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v != fa) {
			deg[v]--;
			Walk2(v, u);
		}
	}
}

void Walk(int u, int fa) {
	if (fa) deg[u] = 1;
	for (int i = hd[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v != fa) {
			Walk(v, u);
			deg[u]++;
		}
	}
	if (!(deg[u]&1)) {
		deg[fa]--;
		Walk2(u, fa);
	}
}

int main() {
	scanf("%d", &n);
	int root;
	for (int i = 1; i <= n; i++) {
		int p;
		scanf("%d", &p);
		if (!p) root = i;
		else { 
			Link(p, i);
			Link(i, p);
		}
	}

	Walk(root, 0);

	if (ans.size() < n) puts("NO");
	else {
		puts("YES");
		for (int i = 0; i < n; i++)
			printf("%d\n", ans[i]);
	}

	return 0;
}