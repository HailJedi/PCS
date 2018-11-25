#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
#include <cstdio>
#define maxn 50
#define INF 0x3f3f3f3f
#define S 0
#define T (R+C+1)
using namespace std;

int R, C;

struct Edge {
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};

vector<Edge> edges;
vector<int> G[maxn];
struct EdmondsKarp {
	int N, M;
	int a[maxn], p[maxn];

	void init(int n) {
		for (int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int cap) {
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));
		int m = edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}

	int MaxFlow() {
		int flow = 0;
		while (true) {
			memset(a, 0, sizeof(a));
			queue<int> Q;
			Q.push(S);
			a[S] = INF;
			while (!Q.empty()) {
				int x = Q.front(); Q.pop();
				for (int i = 0; i < G[x].size(); i++) {
					Edge &e = edges[G[x][i]];
					if (!a[e.to] && e.cap > e.flow) {
						p[e.to] = G[x][i];
						a[e.to] = min(a[x], e.cap - e.flow);
						Q.push(e.to);
					}
				}
				if (a[T]) break;
			}
			if (!a[T]) break;
			for (int u = T; u != S; u = edges[p[u]].from) {
				edges[p[u]].flow += a[T];
				edges[p[u]^1].flow -= a[T];
			}
			flow += a[T];
		}
		return flow;
	}
} Maxf;

int rsum[maxn], csum[maxn];
int acumr[maxn], acumc[maxn]; 
int id[maxn][maxn];

int main() {
	// freopen("read.in", "r", stdin);
	// freopen("write.out", "w", stdout);

	int kase;
	cin >> kase;
	for (int k = 1; k <= kase; k++) {
		cin >> R >> C;
		Maxf.init(R+C+5);

		for (int i = 1; i <= R; i++) {
			cin >> acumr[i];
			rsum[i] = acumr[i] - acumr[i-1] - C;
			Maxf.AddEdge(S, i, rsum[i]);
		}
		for (int i = 1; i <= C; i++) {
			cin >> acumc[i];
			csum[i] = acumc[i] - acumc[i-1] - R;
			Maxf.AddEdge(i+R, T, csum[i]);
		} 

		for (int i = 1; i <= R; i++)
			for (int j = 1; j <= C; j++) {
				Maxf.AddEdge(i, j+R, 19);
				id[i][j] = edges.size()-2;
			}

		Maxf.MaxFlow();
		cout << "Matrix " << k << endl;
		for (int i = 1; i <= R; i++) {
			for (int j = 1; j < G[i].size(); j++) {
				cout << edges[id[i][j]].flow +1 << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}