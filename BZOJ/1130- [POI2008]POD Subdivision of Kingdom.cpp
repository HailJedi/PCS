// 未完成
#include <bits/stdc++.h>

using namespace std;

const int N = 26;
const int S = 1 << N;
int g[N][N], h[N][1<<(N/2)];
int Hash[S];
int n, m, u, v;
int f[S];
vector<int> rec[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		u--, v--;
		g[u][v] = g[v][u] = 1;
	}

	for (int i = 0; i < (1 << (n / 2)); i++) {
		rec[__builtin_popcount(i)].push_back(i);
	}
  	for (int i = 1; i < n / 2; i++) {
  		int j = n / 2 - i;
  		for (int k = 0; k < rec[i].size(); k++) {
  			for (int l = 0; l < rec[j].size(); l++) {
  				rec[n/2].push_back(rec[i][k] << (n / 2) | (rec[j][l]));
  			}
  		}
  	}
  	rec[n/2].push_back(((1<<n)-1)-((1<<(n/2))-1));

  	for (int i = 0; i < rec[n/2].size(); i++) {
  		Hash[rec[n/2][i]] = i;
  	}

  	

	int best = 1e9, ans = 0;

	for (int i = 0; i < rec[n/2].size(); i++) {
		int s = rec[n/2][i];
		
		if (f[s] < best) {
			best = f[s];
			ans = s;
		}
	}
	int full = (1 << n) - 1;
	ans & 1 ? ans : ans ^= full;
	for (int i = 0; i < n; i++) {
		if (ans & (1 << i)) {
			cout << i + 1 << ' ';
		}
	}
	cout << endl;
	return 0;
}
