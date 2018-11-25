#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#define maxn 400
#define INF 0x3f3f3f3f
using namespace std;

typedef pair<int, int> Pair;

int n, m, s, t;
struct Edge {
	int u, v, a, b, d;
	Edge(int u, int v, int a, int b, int d) 
	: u(u), v(v), a(a), b(b), d(d) {}

};
vector<Edge> edges;
vector<int> G[maxn];
int dist[maxn];

int main() {
	int kase = 0;
	while (cin >> n >> m >> s >> t) {
		int u, v, a, b, d;
		for (int i = 1; i <= n; i++) G[i].clear();
		edges.clear();

		for (int i = 1; i <= m; i++) {
			cin >> u >> v >> a >> b >> d;
			int id = edges.size();
			if (d > a) continue;
			G[u].push_back(id);
			edges.push_back(Edge(u, v, a, b, d));
		}

		for (int i = 1; i <= n; i++) 
			dist[i] = INF; dist[s] = 0;

		priority_queue <Pair, vector<Pair>, greater<Pair> > que;
		que.push(make_pair(0, s));

		while (!que.empty()) {
			Pair p = que.top(); que.pop();
			int d = p.first, u = p.second;

			for (int i = 0; i < G[u].size(); i++) {
				Edge &e = edges[G[u][i]];

				int per = d % (e.a + e.b), arr;
				if (per + e.d <= e.a)
					arr = d + e.d;
				else
					arr = d + (e.a + e.b - per) + e.d;

				if (arr < dist[e.v]) {
					dist[e.v] = arr;
					que.push(make_pair(arr, e.v));
				}
			}
		}

		cout << "Case " << ++kase << ": ";
		cout << dist[t] << endl;
	}
	return 0;
}