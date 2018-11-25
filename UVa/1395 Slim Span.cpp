#include <cstdio>
#include <vector>
#include <algorithm>
#define maxn 110
using namespace std;

struct Edge {
	int from, to, weight;
	Edge(int f = 0, int t = 0, int w = 0) : from(f), to(t), weight(w) {}
	bool operator < (const Edge &rhs) const {
		return weight < rhs.weight;
	}
};
typedef vector<Edge> Graph;

Graph graph;

class Union_Find {
public:
	int fa[maxn];
	
	void init(int N) {
		for (int i = 1; i <= N; i++) fa[i] = i;
	}
	
	int find(int x) {
		return x == fa[x] ? x : find(fa[x]);
	}

	void unite(int x, int y) {
		fa[find(x)] = find(y);
	}

	bool united(int x, int y) {
		return find(x) == find(y);
	}
} union_set;

int N, M;

bool read() {
	scanf("%d %d", &N, &M);
	if (!N) return false;
	graph.clear();
	int u, v, w;
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &u, &v, &w);
		graph.push_back(Edge(u, v, w));
	}
	return true;
}

bool allUnited() {
	for (int i = 1; i <= N; i++)
		for (int j = i+1; j <= N; j++) {
			if (i == j) continue;
			if (!union_set.united(i, j)) return false;
		}
	return true;
}

void solve() {
	sort(graph.begin(), graph.end());
	int bound = graph.size();

	int ans = 1e9;
	for (int L = 0; L < bound; L++) {
		union_set.init(N);
		int cnt = N;
		for (int R = L; R < bound; R++) {
			Edge &e = graph[R];
			if (!union_set.united(e.from, e.to)) {
				union_set.unite(e.from, e.to);
				if (--cnt == 1) ans = min(ans, graph[R].weight - graph[L].weight); 
			}
		}
	}
	printf("%d\n", ans < 1e9 ? ans : -1);
}

int main() {
	while (read()) {
		solve();
	}
	return 0;
}