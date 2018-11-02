#include <cstdio>

using namespace std;

const int maxm = 200010;
const int maxn = 400010;

int n, m, ct;
int hd[maxn], to[maxm<<1], nxt[maxm<<1];

void Link(int x, int y) {
	to[++ct] = y;
	nxt[ct] = hd[x];
	hd[x] = ct;
}

int fa[maxn], rnk[maxn];

void InitSet() {
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
		rnk[i] = 0;
	}
}

int Find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = Find(fa[x]);
}

bool Unite(int x, int y) {
	x = Find(x), y = Find(y);
	if (x == y) return false;
	if (rnk[x] == rnk[y]) {
		fa[x] = y;
		rnk[y]++;
	} else 
	if (rnk[x] < rnk[y]) {
		fa[x] = y;
	} else {
		fa[y] = x;
	}
	return true;
}

int cc;
bool cut[maxn];
int stk[maxn];
int it;
int ans[maxn];
int pa[maxn];
int que[maxn<<3];

int Destroyed() {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (!pa[i] && !cut[i]) {
			cnt++;
			pa[i] = i;
			int head = 0, tail = 1;
			que[++head] = i;
			while (head <= tail) {
				int u = que[head++];
				for (int j = hd[u]; j; j = nxt[j]) {
					int v = to[j];
					if (cut[v] || v == pa[u]) continue;
					if (Unite(u, v)) {
						que[++tail] = v;
						pa[v] = u;
					}
				}
			}
		}
	}
	return cnt;
}

int Hope(int u) {
	int cnt = -1;
	for (int i = hd[u]; i; i = nxt[i]) {
		int v = to[i];
		if (cut[v]) continue;
		if (Unite(u, v)) cnt++;
	}
	return cnt;
}

int main() {
	scanf("%d %d", &n, &m);
	int x, y;
	while (m--) {
		scanf("%d %d", &x, &y);
		x++; y++;
		Link(x, y);
		Link(y, x);
	}
	int k, d;
	scanf("%d", &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d", &d);
		d++;
		stk[++it] = d;
		cut[d] = true;
	}
	InitSet();
	ans[1] = Destroyed();
	int j = 1;
	for (int i = it; i >= 1; i--, j++) {
		int plnt = stk[i];
		cut[plnt] = false;
		ans[j+1] = ans[j] - Hope(plnt);
	}

	for (int i = k+1; i >= 1; i--)
		printf("%d\n", ans[i]);

	return 0;
}