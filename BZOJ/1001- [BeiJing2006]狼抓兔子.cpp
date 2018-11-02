#include <cstdio>
#include <queue>
#include <queue>

using namespace std;

typedef pair<int, int> Pair;
const int maxn = 1010;
const int maxg = maxn * maxn * 4;
const int INF = 1e9;

#define up(x) (x<<1)
#define down(x) (x<<1|1)
#define mp(x, y) make_pair(x, y)
#define read(x) scanf("%d", &x)
#define write(x) printf("%d\n", x)
#define ID(i, j) (j+(i-1)*(m-1))

int hd[maxg], nxt[maxg<<1];
int to[maxg<<1];
int w[maxg<<1];
int n, m, ct;

void Link(int u, int v, int c) {
	to[++ct] = v;
	nxt[ct] = hd[u];
	hd[u] = ct;
	w[ct] = c;
}

int dist[maxg];

void Dijkstra(int s, int t) {
	for (int i = s; i <= t; i++)
		dist[i] = INF;
	dist[s] = 0;
	priority_queue<Pair> que;
	que.push(mp(0, s));
	while (!que.empty()) {
		Pair st = que.top(); que.pop();
		int d = -st.first;
		int u = st.second;
		for (int i = hd[u]; i; i = nxt[i]) {
			int v = to[i];
			int d2 = w[i];
			if (d + d2 < dist[v]) {
				dist[v] = d + d2;
				que.push(mp(-dist[v], v));
			}
		}
	}
}

bool in[maxg];

void SPFA(int s, int t) {
	for (int i = s; i <= t; i++)
		dist[i] = INF;
	dist[s] = 0;
	queue<int> que;
	que.push(s);
	in[s] = true;
	while (!que.empty()) {
		int u = que.front();
		que.pop(); in[u] = false;
		for (int i = hd[u]; i; i = nxt[i]) {
			int v = to[i];
			if (dist[v] > dist[u] + w[i]) {
				dist[v] = dist[u] + w[i];
				if (!in[v]) {
					in[v] = true;
					que.push(v);
				}
			}
		}
	}
}

int wh[maxn][maxn], wv[maxn][maxn], ws[maxn][maxn];

int main() {
	read(n); read(m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m-1; j++)
			read(wh[i][j]);
	for (int i = 1; i <= n-1; i++)
		for (int j = 1; j <= m; j++)
			read(wv[i][j]);
	for (int i = 1; i <= n-1; i++)
		for (int j = 1; j <= m-1; j++)
			read(ws[i][j]);

	if (m == 1 && n == 1) {
		puts("0");
		return 0;
	} else 
	if (m == 1) {
		int ans = INF;
		for (int i = 1; i <= n-1; i++)
			ans = min(ans, wv[i][m]);
		write(ans);
		return 0;
	} else 
	if (n == 1) {
		int ans = INF;
		for (int j = 1; j <= m-1; j++)
			ans = min(ans, wh[n][j]);
		write(ans);
		return 0;
	}

	int s = 1, t = 2 * m * n;
	for (int i = 1; i <= n-1; i++) {
		Link(s, down(ID(i, 1)), wv[i][1]);
		Link(down(ID(i, 1)), s, wv[i][1]);
		Link(up(ID(i, m-1)), t, wv[i][m]);
		Link(t, up(ID(i, m-1)), wv[i][m]);
	} 
	for (int j = 1; j <= m-1; j++) {
		Link(s, down(ID(n-1, j)), wh[n][j]);
		Link(down(ID(n-1, j)), s, wh[n][j]);
		Link(up(ID(1, j)), t, wh[1][j]);
		Link(t, up(ID(1, j)), wh[1][j]);
	}
	for (int i = 1; i <= n-1; i++)
		for (int j = 1; j <= m-2; j++) {
			Link(up(ID(i, j)), down(ID(i, j+1)), wv[i][j+1]);
			Link(down(ID(i, j+1)), up(ID(i, j)), wv[i][j+1]);
		}
	for (int i = 1; i <= n-1; i++)
		for (int j = 1; j <= m-1; j++) {
			Link(up(ID(i, j)), down(ID(i, j)), ws[i][j]);
			Link(down(ID(i, j)), up(ID(i, j)), ws[i][j]);
		}
	for (int i = 1; i <= n-2; i++)
		for (int j = 1; j <= m-1; j++) {
			Link(down(ID(i, j)), up(ID(i+1, j)), wh[i+1][j]);
			Link(up(ID(i+1, j)), down(ID(i, j)), wh[i+1][j]);
		}
	SPFA(s, t);
	write(dist[t]);
	return 0;
}