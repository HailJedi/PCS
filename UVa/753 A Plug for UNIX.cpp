#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
#include <cstdio>
#define maxn (500+5)
#define INF 0x3f3f3f3f
#define S 0
#define T 500
using namespace std;

struct Edge {
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};

struct EdmondsKarp {
	int N, M;
	vector<Edge> edges;
	vector<int> G[maxn];
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

int id;
map<string, int> dic;
int ID(string str) {
	if (!dic.count(str))
		dic[str] = id++;
	return dic[str];
}

int main() {
	int kase, N, M, K; 
	cin >> kase;
	while (kase--) {
		id = 1;
		dic.clear();
		Maxf.init(maxn);

		string str;

		cin >> N;
		for (int i = 1; i <= N; i++) {
			cin >> str;
			int id = ID(str);
			Maxf.AddEdge(id, T, 1);
		}
		cin >> M;
		for (int i = 1; i <= M; i++) {
			cin >> str; int dev = ID(str);
			cin >> str; int plug = ID(str);
			Maxf.AddEdge(dev, plug, 1);
			Maxf.AddEdge(S, dev, 1);
		}
		cin >> K;
		for (int i = 1; i <= K; i++) {
			cin >> str; int rec = ID(str);
			cin >> str; int plug = ID(str);
			Maxf.AddEdge(rec, plug, INF);
		}
		cout << M - Maxf.MaxFlow() << endl;
		if (kase) cout << endl;
	}
	return 0;
}