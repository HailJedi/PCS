#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int L = 20 + 5;
const int M = N * L * N * L;
const int S = N * L;

struct Edge {
	Edge *next;
	int u, v;
	void *operator new(size_t, Edge *next, int u, int v) {
		static Edge pool[M], *p = pool;
		if (p == pool + M) {
			p = pool;
		}
		Edge *ret = p++;
		ret->next = next;
		ret->u = u;
		ret->v = v;
		return ret;
	}
} *head[S];

void add_edge(int u, int v) {
	head[u] = new (head[u], u, v) Edge;
}

char weapon[N][L];
int id[N][L], idx, END;
int len[N];
bool dfn[S];

bool dfs(int u) {
	if (u == END) {
		return true;
	}
	dfn[u] = true;
	for (Edge *e = head[u]; e; e = e->next) {
		if (!dfn[e->v] && dfs(e->v)) {
			return true;
		}
	}
	return false;
}

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int n, kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		idx = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%s %s", weapon[i], weapon[i]);
			len[i] = strlen(weapon[i]);
			for (int j = 0; j < len[i]; j++) {
				id[i][j] = idx++;
			}
		}
		END = idx;
		memset(head, 0x0, sizeof head);
		for (int i = 1; i <= n; i++) {
			for (int s = 0; s <= len[i]; s++) {
				for (int j = 1; j <= n; j++) {
					if (i != j) {
						int t = 0;
						for (t = 0; t <= len[j] && s+t <= len[i]; t++) {
							if (weapon[i][s+t] != weapon[j][t]) {
								break;
							}
						}
						if (t >= len[j] && s+t >= len[i]) {
							add_edge(id[i][s], END);
						} else 
						if (t >= len[j]) {
							add_edge(id[i][s], id[i][s+t]);
						} else
						if (s+t >= len[i]) {
							add_edge(id[i][s], id[j][t]);
						}
					}
				}
			}
		}
		bool ambi = false;
		memset(dfn, false, sizeof dfn);
		for (int i = 1; i <= n && !ambi; i++) {
			if (!dfn[id[i][0]]) {
				ambi |= dfs(id[i][0]);
			}
		}
		printf("Case #%d: %s\n", ++kase, ambi ? "Ambiguous." : "Not ambiguous.");
	}
	return 0;
}