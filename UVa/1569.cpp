#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;

bool vis[N];
int pre[N];
int stp[N];
int d[N];

void print(int x) {
	if (x != -1 && pre[x] != -1 && stp[pre[x]] != -1) {
		print(pre[x]);
	}
	printf("%d", stp[x]);
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, m;
	while (scanf("%d", &n) == 1) {
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) {
			scanf("%d", &d[i]);
		}
		sort(d+1, d+1+m);
		if (n == 0) {
			puts("0");
			continue;
		}
		memset(stp, -1, sizeof stp);
		memset(pre, -1, sizeof pre);
		memset(vis, false, sizeof vis);
		queue<int> q;
		for (int i = 1; i <= m; i++) if (d[i]) {
			if (!vis[d[i] % n]) {
				vis[d[i] % n] = true;
				q.push(d[i] % n);
				pre[d[i] % n] = -1;
				stp[d[i] % n] = d[i];
			}
		}
		bool ok = false;
		while (!q.empty()) {
			int r = q.front();
			q.pop();
			if (r == 0) {
				print(r);
				ok = true;
				break;
			}
			for (int i = 1; i <= m; i++) {
				int nr = (r * 10 + d[i]) % n;
				if (!vis[nr]) {
					vis[nr] = true;
					pre[nr] = r;
					stp[nr] = d[i];
					q.push(nr);
				}
			}
		}
		if (!ok) {
			printf("0");
		}
		puts("");
	}
	return 0;
}