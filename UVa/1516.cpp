#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double INF = 1e60;
const int N = 100 + 5;
const int M = 1000 + 5;

struct BellmanFord {
	struct Edge {
		Edge *next;
		int u, v;
		double w;
		void *operator new(size_t, Edge *next, int u, int v, double w) {
			static Edge pool[M*10], *p = pool;
			if (p == pool + M*10) {
				p = pool;
			}
			Edge *ret = p++;
			ret->next = next;
			ret->u = u;
			ret->v = v;
			ret->w = w;
			return ret;
		}
	} *head[N];

	void add_edge(int u, int v, double w) {
		head[u] = new (head[u], u, v, w) Edge;
	}

	int n;
	int cnt[N];
	double dis[N][N];
	bool inq[N];
	
	void init(int n) {
		this->n = n;
		memset(head, 0x0, sizeof head);
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				dis[i][j] = INF;
			}
			dis[i][i] = 0;
		}
	}
	
	bool solve(int s) {
		memset(cnt, 0, sizeof cnt);
		memset(inq, false, sizeof inq);
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = false;
			for (Edge *e = head[u]; e; e = e->next) {
				if (dis[s][e->v] > dis[s][u] + e->w) {
					dis[s][e->v] = dis[s][u] + e->w;
					if (!inq[e->v]) {
						q.push(e->v);
						inq[e->v] = true;
						if (++cnt[e->v] > n) {
							return false;
						}
					}
				}
			}
		}
		return true;
	}
} solver;

string name[N];
map<string, int> id;
double x[N], y[N];
bool add[N];

double dis(int i, int j) {
	return sqrt(pow((x[i]-x[j]), 2) + pow(y[i]-y[j], 2));
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;
		solver.init(n);
		for (int i = 1; i <= n; i++) {
			cin >> name[i] >> x[i] >> y[i];
			id[name[i]] = i;
		}
		memset(add, false, sizeof add);
		int cnt = 0;
		vector<int> obj;
		for (int i = 1; i <= m; i++) {
			string wit, bfr, aft, t;
			cin >> wit >> t >> bfr >> t >> t >> aft;
			int ta = id[wit], tb = id[bfr], tc = id[aft];
			// tb + dis(a, b) <= tc + dis(a, c);
			solver.add_edge(tc, tb, (dis(ta, tc) - dis(ta, tb))/340);
			if (!add[tb]) {
				add[tb] = true;
				solver.add_edge(0, tb, 0);
				cnt++;
				obj.push_back(tb);
			}
			if (!add[tc]) {
				add[tc] = true;
				solver.add_edge(0, tc, 0);
				cnt++;
				obj.push_back(tc);
			}
		}
		if (!solver.solve(0)) {
			cout << "IMPOSSIBLE" << endl;
		} else {
			for (int i = 0; i < obj.size(); i++) {
				solver.solve(obj[i]);
			}
			vector<int> ans;
			while (cnt--) {
				bool ok = false;
				for (int i = 0; i < obj.size(); i++) {
					if (add[obj[i]]) {
						ok = true;
						for (int j = 0; j < obj.size() && ok; j++) {
							if (i != j && add[obj[j]]) {
								ok &= (solver.dis[obj[j]][obj[i]] < 0);
							}
						}
						if (ok) {
							ans.push_back(obj[i]);
							add[obj[i]] = false;
							break;
						}
					}
				}
				if (!ok) {
					break;
				}
			}
			if (cnt != -1) {
				cout << "UNKNOWN" << endl;
			} else {
				bool ok = false;
				for (int i = 0; i < ans.size(); i++) {
					if (ok) {
						cout << ' ';
					} ok = true;
					cout << name[ans[i]];
				}
				cout << endl;
			}
		}
	}
	return 0;
}