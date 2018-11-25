#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int M = 10 + 5;
const int INF = 0x3f3f3f3f;

int id2j[M*N], id2k[M*N];
int id[M][N], idx;
int ID(int i, int j) {
	return id[i][j] ? id[i][j] : id[i][j] = ++idx;
}

int W[N][M*N];
bool S[N], T[N*M];
int Lx[N], Ly[N*M], mn[N*M];
int Left[N*M];
int m, n;

bool match(int i) {
	S[i] = true;
	for (int j = 1; j <= idx; j++) if (!T[j]) {
		int diff = Lx[i] + Ly[j] - W[i][j];
		if (diff == 0) {
			T[j] = true;
			if (!Left[j] || match(Left[j])) {
				Left[j] = i;
				return true;
			}
		} else {
			mn[j] = min(mn[j], diff);
		}
	}
	return false;
}

void update() {
	int a = INF;
	for (int i = 1; i <= idx; i++) if (!T[i]) {
		a = min(a, mn[i]);
	}
	for (int i = 1; i <= n; i++) if (S[i]) {
		Lx[i] -= a;
	}
	for (int i = 1; i <= idx; i++) {
		if (T[i]) Ly[i] += a;
		else mn[i] -= a;
	}
}
		
void KM() {
	memset(Lx, 0, sizeof Lx);
	memset(Ly, 0, sizeof Ly);
	memset(Left, 0, sizeof Left);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= idx; j++) {
			Lx[i] = max(Lx[i], W[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		memset(mn, INF, sizeof mn);
		while (true) {
			memset(S, false, sizeof S);
			memset(T, false, sizeof T);
			if (match(i)) {
				break;
			} else {
				update();
			}
		}
	}
}

int sto[M];
int tim[N][M];
int ans1[N], ans2[N], ans3[N];

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	int kase = 0;
	while (scanf("%d %d", &m, &n) == 2 && n) {
		for (int i = 1; i <= m; i++) {
			scanf("%d", &sto[i]);
		}
		memset(tim, INF, sizeof tim);
		for (int i = 1; i <= n; i++) {
			int k;
			scanf("%d", &k);
			while (k--) {
				int s, t;
				scanf("%d %d", &s, &t);
				for (int j = 1; j <= m; j++) {
					if (sto[j] >= s) {
						tim[i][j] = t;
					}
				}
			}
		}
		idx = 0;
		memset(id, 0, sizeof id);
		memset(W, -INF, sizeof W);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (tim[i][j] != INF) {
					for (int k = 0; k < n; k++) {
						W[i][ID(j, k)] = -(n-k) * tim[i][j];
						id2j[ID(j, k)] = j;
						id2k[ID(j, k)] = k;
					}
				}
			}
		}
		KM();
		vector< pair<int, int> > que[M];
		for (int i = 1; i <= idx; i++) {
			if (Left[i]) {
				int j = id2j[i], k = id2k[i];
				que[j].push_back(make_pair(k, Left[i]));
			}
		}
		double sum = 0;
		for (int i = 1; i <= m; i++) {
			sort(que[i].begin(), que[i].end());
			int t = 0;
			for (int j = 0; j < que[i].size(); j++) {
				int exe = que[i][j].second;
				ans1[exe] = i;
				ans2[exe] = t;
				ans3[exe] = t + tim[exe][i];
				sum += ans3[exe];
				t += tim[exe][i];
			}
		}
		printf("Case %d\n", ++kase);
		printf("Average turnaround time = %.2lf\n", sum / n);
		for (int i = 1; i <= n; i++) {
			printf("Program %d runs in region %d from %d to %d\n", i, ans1[i], ans2[i], ans3[i]);
		}
		puts("");
	}
	return 0;
}
