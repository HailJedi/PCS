#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 233;
const int maxm = 21;
const int INF = 1e9;

#define s 1
#define t m
#define ID(u, v) ((u-1)*m+v)

int dp[maxn];
int f[maxn][maxn];
bool out[maxm<<1][maxn<<1];
int n, m, k;

int hd[maxm<<1], to[maxm*maxm*2];
int nxt[maxm*maxm*2], c[maxm*maxm*2];
bool cut[maxm];
int ct;

void Link(int u, int v, int w) {
	to[++ct] = v;
	nxt[ct] = hd[u];
	hd[u] = ct;
	c[ct] = w;
}

int dist[maxm<<1];
bool in[maxm<<1];
int que[maxm<<4];

int SPFA(int S, int T) {
	for (int i = 1; i <= m; i++) {
		dist[i] = INF;
		in[i] = false;
	}
	dist[S] = 0;
	in[S] = true;
	int head = 0, tail = 1;
	que[++head] = S;
	while (head <= tail) {
		int u = que[head++];
		in[u] = false;
		for (int i = hd[u]; i; i = nxt[i]) {
			int v = to[i];
			if (dist[v] > dist[u] + c[i]) {
				dist[v] = dist[u] + c[i];
				if (!in[v] && !cut[v]) {
					in[v] = true;
					que[++tail] = v;
				}
			}
		}
	}
	return dist[T];
}

void Solve() {
	
	for (int i = 1; i <= n; i++) {
		memset(cut, false, sizeof(cut));
		for (int j = i; j <= n; j++) {
			for (int k = 1; k <= m; k++)
				cut[k] |= out[k][j];
			f[i][j] = SPFA(s, t);
		}
	}

	dp[0] = -k;
	for (int i = 1; i <= n; i++) {
		dp[i] = INF;
		for (int j = 0; j < i; j++) {
			if (f[j+1][i] != INF)
				dp[i] = min(dp[i], dp[j] + f[j+1][i]*(i-j)+k);
		}
	}

	printf("%d\n", dp[n]);
}

int main() {
	int e, d, u, v, c, p, a, b;
	scanf("%d %d %d %d", &n, &m, &k, &e);
	while (e--) {
		scanf("%d %d %d", &u, &v, &c);
		Link(u, v, c); Link(v, u, c);
	}
	scanf("%d", &d);
	while (d--) {
		scanf("%d %d %d", &p, &a, &b);
		for (int i = a; i <= b; i++)
			out[p][i] = true;
	}
	Solve();
	return 0;
}