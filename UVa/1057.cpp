#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;	

int dis[N][N];
int f[N][N];
bool inq[N][N];
vector<int> g1[N], g2[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, m, kase = 0;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 1; i <= n; i++) {
			g1[i].clear();
			g2[i].clear();
		}
		memset(dis, INF, sizeof dis);
		for (int i = 1; i <= n; i++) {
			dis[i][i] = 0;
		}
		for (int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			dis[u][v] = 1;
			g1[u].push_back(v);
			g2[v].push_back(u);
		}
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
				}
			}
		}
		printf("Network %d\n", ++kase);
		if (dis[1][2] != INF && dis[2][1] != INF) {
			memset(f, INF, sizeof f);
			f[1][1] = 1;
			queue<int> q1, q2;
			q1.push(1);
			q2.push(1);
			inq[1][1] = true;
			while (!q1.empty()) {
				int u1 = q1.front(), u2 = q2.front();
				q1.pop(); q2.pop();
				inq[u1][u2] = false;
				for (int i = 0; i < g1[u1].size(); i++) {
					int v1 = g1[u1][i];	
					int cand = f[u1][u2] + (v1 != u2);
					if (cand < f[v1][u2]) {
						f[v1][u2] = cand;
						if (!inq[v1][u2]) {
							q1.push(v1);
							q2.push(u2);
							inq[v1][u2] = true;
						}
					}
				}
				for (int i = 0; i < g2[u2].size(); i++) {
					int v2 = g2[u2][i];
					int cand = f[u1][u2] + (v2 != u1);
					if (cand < f[u1][v2]) {
						f[u1][v2] = cand;
						if (!inq[u1][v2]) {
							q1.push(u1);
							q2.push(v2);
							inq[u1][v2] = true;
						}
					}
				}
				if (u1 != u2 && f[u1][u2] + dis[u1][u2] - 1 < f[u2][u1]) {
					f[u2][u1] = f[u1][u2] + dis[u1][u2] - 1;
					if (!inq[u2][u1]) {
						q1.push(u2);
						q2.push(u1);
						inq[u2][u1] = true;
					}
				}
			}
			printf("Minimum number of nodes = %d\n", f[2][2]);
		} else {
			printf("Impossible\n");
		}
		printf("\n");
	}
	return 0;
}