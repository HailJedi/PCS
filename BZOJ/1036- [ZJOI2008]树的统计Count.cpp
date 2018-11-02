#include <cstdio>
#include <algorithm>

using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}

const int maxn = 30010;
const int logn = 20;
const int INF = 1e9;

int fa[maxn];
int prf[maxn], top[maxn];
int hd[maxn], nxt[maxn<<1];
int fm[maxn<<1], to[maxn<<1];
int sz[maxn], sgid[maxn];
int w[maxn<<1];
int n, ct, sg;
int dpth[maxn];

/* Segment Tree */
const int root = 1;
int mx[maxn<<2], sum[maxn<<2];
int l[maxn<<2], r[maxn<<2];
int val[maxn<<2];

void Build(int id, int L, int R) {
	l[id] = L; r[id] = R;
	if (L < R) {
		int mid = (L+R)>>1;
		Build(id<<1, L, mid);
		Build(id<<1|1, mid+1, R);
		mx[id] = max(mx[id<<1], mx[id<<1|1]);
		sum[id] = sum[id<<1] + sum[id<<1|1];
	} else {
		mx[id] = sum[id] = val[L];
	}
}

void Change(int o, int u, int v) {
	if (l[o] == u && r[o] == u) {
		mx[o] = sum[o] = v;
	} else {
		if (u <= r[o<<1]) Change(o<<1, u, v);
		else Change(o<<1|1, u, v);	
		mx[o] = max(mx[o<<1], mx[o<<1|1]);
		sum[o] = sum[o<<1] + sum[o<<1|1];
	}
}

int QuerySum(int o, int x, int y) {
	if (x <= l[o] && r[o] <= y)
		return sum[o];
	else {
		int v1 = 0, v2 = 0;
		if (r[o<<1] >= x) v1 = QuerySum(o<<1, x, y);
		if (l[o<<1|1] <= y) v2 = QuerySum(o<<1|1, x, y);
		return v1 + v2;
	}
}

int QueryMax(int o, int x, int y) {
	if (x <= l[o] && r[o] <= y)
		return mx[o];
	else {
		int v1 = -INF, v2 = -INF;
		if (r[o<<1] >= x) v1 = QueryMax(o<<1, x, y);
		if (l[o<<1|1] <= y) v2 = QueryMax(o<<1|1, x, y);
		return max(v1, v2);
	}
}

/* Heavy Light Decomposition */
int PathSum(int x, int y) {
	int sum = 0;
	while (top[x] != top[y]) {
		if (dpth[top[x]] < dpth[top[y]]) swap(x, y);
		sum += QuerySum(root, sgid[top[x]], sgid[x]);
		x = fa[top[x]];
	}
	if (sgid[x] > sgid[y]) swap(x, y);
	sum += QuerySum(root, sgid[x], sgid[y]);
	return sum;
}

int PathMax(int x, int y) {
	int mxx = -INF;
	while (top[x] != top[y]) {
		if (dpth[top[x]] < dpth[top[y]]) swap(x, y);
		mxx = max(mxx, QueryMax(root, sgid[top[x]], sgid[x]));
		x = fa[top[x]];
	}
	if (sgid[x] > sgid[y]) swap(x, y);
	mxx = max(mxx, QueryMax(root, sgid[x], sgid[y]));
	return mxx;
}

void DFS1(int u, int f) {
	sz[u] = 1;
	fa[u] = f;
	dpth[u] = dpth[f] + 1;
	for (int i = hd[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v != f) {
			DFS1(v, u);
			sz[u] += sz[v];
			if (sz[v] > sz[prf[u]])
				prf[u] = v;
		}
	}	
}

void DFS2(int u, int t) {
	top[u] = t;
	sgid[u] = ++sg;
	val[sg] = w[u];
	if (prf[u]) DFS2(prf[u], t);
	for (int i = hd[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v == prf[u] || v == fa[u]) continue;
		DFS2(v, v);
	}
}

void Link(int u, int v) {
	fm[++ct] = u; to[ct] = v;
	nxt[ct] = hd[u]; hd[u] = ct;
}

void Init() {
	n = read();
	int u, v;
	for (int i = 1; i < n; i++) {
		u = read(); v = read();
		Link(u, v);
		Link(v, u);
	}
	for (int i = 1; i <= n; i++) 
		w[i] = read();
	DFS1(1, 0);
	DFS2(1, 1);
	Build(1, 1, n);
}

int main() {
	Init();
	int q;
	q = read();
	char cmd[10];
	int x, y;
	while (q--) {
		scanf("%s", cmd);
		x = read(); y = read();
		if (cmd[1] == 'M') {
			// printf("Max value from %d to %d:\n", x, y);
			printf("%d\n", PathMax(x, y));
		}
		else if (cmd[1] == 'S') {
			// printf("Value sum from %d to %d:\n", x, y);
			printf("%d\n", PathSum(x, y));
		}
		else {
			val[sgid[x]] = y;
			Change(root, sgid[x], y);
		}
	}
	return 0;
}