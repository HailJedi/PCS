#include <cstdio>
#include <vector>
#include <algorithm>
#define maxn 1100
using namespace std;

struct Edge {
	int from, to, dist;
	Edge(int f = 0, int t = 0, int d = 0) : from(f), to(t), dist(d) {}
	bool operator < (const Edge &rhs) const {
		return dist < rhs.dist;
	}
};
typedef vector<Edge> Graph;

int fa[maxn];

void init(int N) {
	for (int i = 0; i < N; i++) fa[i] = i;
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

int pack[10][maxn];
int pcost[10];
int tot[10];
int x[maxn], y[maxn];
int N, Q;

int MST(int rest, Graph &use, Graph &creat) {
	if (!rest) return 0;
	int cost = 0;
	creat.clear();
	for (int i = 0; i < use.size(); i++) {
		Edge &e = use[i];
		if (!united(e.from, e.to)) {
			unite(e.from, e.to);
			creat.push_back(e);
			cost += e.dist;
			if (--rest == 0) break;
		}
	}
	return cost;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &tot[i], &pcost[i]);
			for (int j = 0; j < tot[i]; j++) {
				scanf("%d", &pack[i][j]);
				pack[i][j]--;
			}
		}

		Graph graph, need;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &x[i], &y[i]);
			for (int j = 0; j < i; j++)
				graph.push_back(Edge(i, j, (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j])));
		}

		sort(graph.begin(), graph.end());
		init(N);
		int ans = MST(N-1, graph, need);
		for (int i = 0; i < (1<<Q); i++) {
			int c = 0, rest = N-1;
			init(N);
			for (int p = 0; p < Q; p++) if (i & (1<<p)) { 
				c += pcost[p];
				for (int j = 1; j < tot[p]; j++) {
					if (!united(pack[p][j], pack[p][0])) {
						unite(pack[p][j], pack[p][0]);
						rest--;
					}
				}
			}
			Graph dummy;
			ans = min(ans, c + MST(rest, need, dummy));
		}
		printf("%d\n", ans);
		if (T) puts("");
	}
	return 0;
}