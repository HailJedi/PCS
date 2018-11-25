#include <bits/stdc++.h>

using namespace std;

const int N = 6;

int mix2[N][N];
int heat[N][N];

map<vector<int>, int> f;

int dp(vector<int> v) {
	if (f.count(v)) {
		return f[v];
	}
	f[v] = 1e9;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int amt = i == j;
			if (v[i] > amt && v[j] > amt) {
				int mix = mix2[i][j];
				int hit = heat[i][j];
				vector<int> u = v;
				u[i]--;
				u[j]--;
				u[mix]++;
				f[v] = min(f[v], hit + dp(u));
			}
		}
	}
	return f[v];
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int m;
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d %d", &mix2[i][j], &heat[i][j]);
				mix2[i][j]--;
			}
		}
		f.clear();
		vector<int> init(N, 0);
		for (int i = 0; i < N; i++) {
			init[i]++;
			f[init] = 0;
			init[i]--;
		}
		int k;
		scanf("%d", &k);
		for (int i = 1; i <= k; i++) {
			int c;
			scanf("%d", &c);
			init[c-1]++;
		}
		printf("%d\n", dp(init));
		char s[10];
		scanf("%s", s);
	}
	return 0;
}