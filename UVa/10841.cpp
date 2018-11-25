#include <bits/stdc++.h>

using namespace std;

const int F = 256;
const int E = 128;
const int S = E * F;
const int M = S * E;
const int INF = 0x3f3f3f3f;

struct Dijkstra {
	struct Edge {
		Edge *next;
		int u, v, w;
		void *operator new(size_t, Edge *next, int u, int v, int w) {
			static Edge pool[M], *p = pool;
			if (p == pool + M) {
				p = pool;
			}
			Edge *ret = p++;
			ret->next = next;
			ret->u = u;
			ret->v = v;
			ret->w = w;
			return ret;
		}
	} *head[S];
	
	void add_edge(int u, int v, int w) {
		head[u] = new (head[u], u, v, w) Edge;
	}
	
	void init() {
		memset(head, 0x0, sizeof head);
	}
	
	struct State {
		int u, d;
		State() {}
		State(int u, int d) : u(u), d(d) {}
		bool operator < (const State &s) const {
			return d > s.d;
		}
	};

	int dis[S];
	int vis[S];
	int kase;

	int solve(int s, int t) {
		++kase;
		priority_queue<State> q;
		q.push(State(s, 0));
		memset(dis, INF, sizeof dis);
		dis[s] = 0;
		while (!q.empty()) {
			State cur = q.top();
			q.pop();
			if (cur.u == t) {
				break;
			}
			if (vis[cur.u] == kase) {
				continue;
			}
			vis[cur.u] = kase;
			for (Edge *e = head[cur.u]; e; e = e->next) {
				if (dis[e->v] > cur.d + e->w) {
					dis[e->v] = cur.d + e->w;
					q.push(State(e->v, dis[e->v]));
				}
			}
		}
		return dis[t];
	}
} solver;

vector<int> flor[E], elev[F];
int t[E];

int idx;
int id[E][F];
int ID(int ele, int flr) {
	return id[ele][flr] != -1 ? id[ele][flr] : id[ele][flr] = ++idx;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int n, k;
	while (cin >> n >> k) {
		for (int i = 1; i <= n; i++) {
			cin >> t[i];
		}
		for (int i = 0; i < F; i++) {
			elev[i].clear();
		}
		solver.init();
		memset(id, -1, sizeof id);
		idx = 0;
		while (getchar() != '\n');
		for (int i = 1; i <= n; i++) {
			flor[i].clear();
			string str;
			getline(cin, str);
			stringstream in(str);
			int f;
			while (in >> f) {
				flor[i].push_back(f);
				elev[f].push_back(i);
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < flor[i].size()-1; j++) {
				solver.add_edge(ID(i, flor[i][j]), ID(i, flor[i][j+1]), abs(flor[i][j]-flor[i][j+1])*t[i]);
				solver.add_edge(ID(i, flor[i][j+1]), ID(i, flor[i][j]), abs(flor[i][j]-flor[i][j+1])*t[i]);
			}
		}
		for (int i = 0; i < F; i++) {
			for (int j = 0; j < elev[i].size(); j++) {
				for (int k = 0; k < elev[i].size(); k++) {
					if (j != k) {
						int u = elev[i][j], v = elev[i][k];
						solver.add_edge(ID(u, i), ID(v, i), 5 + max(abs(i-flor[v][0]), abs(i-flor[v].back())) * t[v]);
					}
				}
			}
		}
		int s = ++idx, e = ++idx;
		for (int i = 1; i <= n; i++) {
			if (!flor[i].empty()) {
				solver.add_edge(s, ID(i, 0), flor[i].back() * t[i]);
			}
		}
		for (int i = 0; i < elev[k].size(); i++) {
			solver.add_edge(ID(elev[k][i], k), e, 0);
		}
		int ans = k ? solver.solve(s, e) : 0;
		if (ans != INF) {
			printf("%d\n", ans);
		} else {
			printf("IMPOSSIBLE\n");
		}
	}
	return 0;
}