#include <bits/stdc++.h>

using namespace std;

const int N = 55;
int n, A, B;
int w[N][N];
int c[N], d[N], cnt[3], fa[N];
bool vis[N], in[N], used[N][N];
string s;
vector<int> g[N], pc[N];
map<char, int> mp;

void link(int u, int v, int d) {
	g[u].push_back(v);
	w[u][v] = d;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	mp['+'] = -1;
	mp['='] = 0;
	mp['-'] = 1;
	cin >> n >> A >> B;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		for (int j = 0; j < n; j++) {
			if (s[j] == '-') {
				link(i, j+1, 1);
				in[j+1] = true;
			} else 
			if (s[j] == '=') {
				link(i, j+1, 0);
				link(j+1, i, 0);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		d[i] = -10;
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i] && !in[i]) {
			d[i] = 0;
			queue<int> q;
			q.push(i);
			set<int> rec;
			while (!q.empty()) {
				int u = q.front(); 
				rec.insert(u);
				q.pop();
				vis[u] = true;
				for (int j = 0; j < g[u].size(); j++) {
					int v = g[u][j];
					if (!used[u][v] && d[v] < d[u] + w[u][v]) {
						d[v] = d[u] + w[u][v];
						used[u][v] = true;
						q.push(v);
					}
				}
			}
			int mn = 10, mx = -10;
			for (set<int>::iterator it = rec.begin(); it != rec.end(); ++it) {
				// cout << *it << ' ' << d[*it] << endl;
				fa[*it] = i;
				mn = min(mn, d[*it]);
				mx = max(mx, d[*it]);
			}
			// if (mx - mn == 2) {
				for (int j = 1; j <= 3; j++) {
					if (j + mx <= 3 && j + mn >= 1) {
						for (set<int>::iterator it = rec.begin(); it != rec.end(); ++it) {
							pc[*it].push_back(j + d[*it]);
						}
					}
				}
			// }
		}
	}
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 0; j < pc[i].size(); j++) {
	// 		cout << pc[i][j] << ' ';
	// 	}
	// 	cout << endl;
	// }
	for (int i = 1; i <= n; i++) {
		cout << fa[i] << ' ' << d[i] << endl;
	}
	cout << endl;
	for (int k = 1; k <= n; k++) {
		if (k != A && k != B) {
			for (int l = k + 1; l <= n; l++) {
				if (l != A && l != B) {
					for (int i = 0; i < pc[A].size(); i++) {
						for (int j = 0; j < pc[B].size(); j++) {
							int cnt2[3] = {0};
							for (int p = 0; p < pc[k].size(); p++) {
								for (int q = 0; q < pc[l].size(); q++) {
									int ac = pc[A][i], bc = pc[B][j];
									int kc = pc[k][p], lc = pc[l][q];
									if ((fa[A] != fa[B] || fa[A] == fa[B] && (ac == bc)(ac - bc) * (d[A] - d[B]) > 0) && (fa[A] != fa[k] || (fa[A] == fa[k] && ac - kc == d[A] - d[k]))
										&& (fa[A] != fa[l] || (fa[A] == fa[l] && ac - lc == d[A] - d[l])) && (fa[B] != fa[k] || (fa[B] == fa[k] && bc - kc == d[B] - d[k]))
										&& (fa[B] != fa[l] || (fa[B] == fa[l] && bc - lc == d[B] - d[l])) && (fa[k] != fa[l] || (fa[k] == fa[l] && kc - lc == d[k] - d[l]))) {
										int lw = ac + bc;
										int rw = kc + lc;
										cnt2[lw > rw ? 0 : lw == rw ? 1 : 2] = 1;
									}
								}
							}
							if (cnt2[0] + cnt2[1] + cnt2[2] == 1) {
								cnt[0] += cnt2[0], cnt[1] += cnt2[1], cnt[2] += cnt2[2];
							}
						}
					}
				}
			}
		}
	}
	cout << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << endl;
	return 0;
}