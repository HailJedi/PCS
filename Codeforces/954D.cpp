#include <bits/stdc++.h>

#define N 1010
#define eb emplace_back
#define psh push
#define ft front

#define INF 1e9

using namespace std;

int d[N], rd[N];
vector<int> g[N];
int n, m, s, t, u, v;
bool cnt[N][N];
bool in[N];

void bellman_ford(int *dist, int s, int t) {
	fill_n(dist, n+1, INF);
	fill_n(in, n+1, false);
	dist[s] = 0;
	queue<int> que;
	que.psh(s); in[s] = true;
	while (!que.empty()) {
		int u = que.ft(); que.pop();
		for (int v: g[u]) {
			if (dist[v] > dist[u] + 1) {
				dist[v] = dist[u] + 1;
				if (!in[v]) {
					in[v] = true;
					que.psh(v);
				}
			}
		}
	}
}

int main() {
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		g[u].eb(v);
		g[v].eb(u);
		cnt[u][v] = cnt[v][u] = true;
	}
	bellman_ford(d, s, t);
	bellman_ford(rd, t, s);
	
	int sp = d[t], ans = 0;
	for (int i = 1; i <= n; i++) 
		for (int j = i+1; j <= n; j++) 
			if (!cnt[i][j]) {
				int ad = min(d[i] + rd[j], d[j] + rd[i]) + 1;
				ans += (ad >= sp);
			}
	cout << ans << endl;

	return 0;
}	