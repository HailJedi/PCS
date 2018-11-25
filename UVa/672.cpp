#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int K = 100 + 5;

struct Gans {
	int t, p, s;
	void *operator new(size_t, int t) {
		static Gans pool[N*N], *p = pool;
		Gans *ret = p++;
		ret->t = t;
		return ret;
	}
} *g[N];

struct cmp {
	bool operator ()(const Gans *p1, const Gans *p2) {
		return p1->t < p2->t;
	}
};

int f[N][K];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int T;
	cin >> T;
	while (T--) {
		int n, k, t;
		cin >> n >> k >> t;
		for (int i = 0; i <= n; i++) {
			g[i] = new (0) Gans;
		}
		for (int i = 1; i <= n; i++) {
			cin >> g[i]->t;
		}
		for (int i = 1; i <= n; i++) {
			cin >> g[i]->p;
		}
		for (int i = 1; i <= n; i++) {
			cin >> g[i]->s;
		}
		sort(g+1, g+1+n, cmp());
		memset(f, -1, sizeof f);
		f[0][0] = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= k; j++) {
				if (f[i][j] != -1) {
					int dur = g[i+1]->t - g[i]->t;
					for (int r = j; r >= max(0, j-dur); r--) {
						f[i+1][r] = max(f[i+1][r], f[i][j] + (g[i+1]->s == r ? 1 : 0) * g[i+1]->p);
					}
					for (int r = j; r <= min(k, j+dur); r++) {
						f[i+1][r] = max(f[i+1][r], f[i][j] + (g[i+1]->s == r ? 1 : 0) * g[i+1]->p);
					}
				}
			}
		}
		int ans = 0;
		for (int i = 0; i <= k; i++) {
			ans = max(ans, f[n][i]);
		}
		cout << ans << endl << (T ? "\n" : "");
	}
	return 0;
}