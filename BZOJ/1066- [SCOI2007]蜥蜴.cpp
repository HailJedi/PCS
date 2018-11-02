#include <bits/stdc++.h>

using namespace std;

const int maxr = 50;
const int maxd = 5;
const int maxn = maxr*maxr*2;
const int maxe = maxn*maxn;
const int INF = 1e9;

int r, c;

inline int id(int x, int y) {
	return ((x-1)*c+y);
}

inline double dist(int i, int j, int x, int y) {
	return (i-x)*(i-x)+(j-y)*(j-y);
}

inline int disout(int i, int j) {
	return min(min(i, r-i+1), min(j, c-j+1));
}

inline bool inbound(int i, int j) {
	return ((1 <= i && i <= r) && (1 <= j && j <= c));
}

int d, s, t;
char col[maxn][maxn];
char liz[maxn][maxn];

int hd[maxn], nxt[maxe];
int fm[maxe], to[maxe], cap[maxe];
int e = 1;

void addEdge(int u, int v, int c) {
	fm[++e] = u; to[e] = v; cap[e] = c; nxt[e] = hd[u]; hd[u] = e;
	fm[++e] = v; to[e] = u; cap[e] = 0; nxt[e] = hd[v]; hd[v] = e;
}

int lvl[maxn];
int que[maxn<<5];
int head, tail;
int cnt[maxn];
int kase;

bool BFS() {
	// for (int i = s; i <= t; i++)
		// lvl[i] = -1;
	lvl[s] = 0;
	cnt[s] = ++kase;
	head = tail = 1;
	que[head] = s;
	while (head <= tail) {
		int u = que[head++];
		for (int i = hd[u]; i; i = nxt[i]) {
			if (cap[i] > 0 && cnt[to[i]] != kase) {
				lvl[to[i]] = lvl[u] + 1;
				que[++tail] = to[i];
				cnt[to[i]] = kase;
				if (to[i] == t) return true;
			}
		}
	}
	return false;
}

int cur[maxn];

int DFS(int u, int f) {
	if (u == t) return f;
	int vf = 0;
	for (int i = hd[u]; i; i = nxt[i]) {
		int v = to[i];
		if (cap[i] > 0 && lvl[u]+1 == lvl[v]) {
			int fl = DFS(v, min(cap[i], f));
			f -= fl;
			cap[i] -= fl;
			cap[i^1] += fl;
			vf += fl;
			if (!t) lvl[v] = 0;
		}
	}
	return vf;
}

int main() {
	scanf("%d %d %d", &r, &c, &d);
	d *= d;
	for (int i = 1; i <= r; i++)
		scanf("%s", col[i]+1);
	int liza = 0;
	for (int i = 1; i <= r; i++) {
		scanf("%s", liz[i]+1);
		for (int j = 1; j <= c; j++)
			if (liz[i][j] == 'L') liza++;
	}
	s = 0; t = r*c*2+1;

	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++) {
			if (col[i][j] == '0') continue;
			
			addEdge((id(i, j)), r*c+(id(i, j)), col[i][j]-'0');
			
			if (liz[i][j] == 'L') {
				addEdge(s, (id(i, j)), 1);
				liza++;
			}
			
			if (disout(i, j) <= d) 
				addEdge(r*c+(id(i, j)), t, INF);
				
			for (int x = 1; x <= r; x++)
				for (int y = 1; y <= c; y++) {
					if (col[x][y] == '0') continue;
					if (i == x && j == y) continue;
					if (dist(i, j, x, y) <= d) {
						addEdge(r*c+(id(i, j)), (id(x, y)), INF);
						addEdge(r*c+(id(x, y)), (id(i, j)), INF);
					}
				}
		}

	int maxf = 0, flow;
	while (maxf < liza && BFS()) {
		// for (int i = s; i <= t; i++)
			// cur[i] = hd[i];
		// ok = false;
		// while (maxf < liza && (flow = DFS(s, INF))) {
			// ok = true;
			// maxf += flow;
		// }
		maxf += DFS(s, INF);
	}

	printf("%d\n", liza - maxf);

	return 0;
}