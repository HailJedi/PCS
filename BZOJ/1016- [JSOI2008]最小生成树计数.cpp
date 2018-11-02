#include <bits/stdc++.h>

using namespace std;

const int maxe = 1010;
const int maxn = 110;
const int mod = 31011;

struct Edge {
	int u, v, c;
	bool operator < (const Edge &e) const {
		return c < e.c;
	}
} e[maxe];

int n, m;

int fa[maxn];

void InitSet() {
	for (int i = 1; i <= n; i++)
		fa[i] = i;
}

int Find(int x) {
	return x == fa[x] ? x : Find(fa[x]);
}

bool Same(int x, int y) {
	return Find(x) == Find(y);
}

void Unite(int x, int y) {
	x = Find(x), y = Find(y);
	fa[x] = y;
}

vector<int> num, cost;

bool Kruskal() {
	int cnt = 0, it = -1, last = -1;
	InitSet();
	for (int i = 1; i <= m && cnt < n-1; i++) {
		if (!Same(e[i].u, e[i].v)) {
			Unite(e[i].u, e[i].v);
			cnt++;
			if (e[i].c != last) {
				num.push_back(1);
				cost.push_back(e[i].c);
				it++;
				last = e[i].c;
			} else {
				num[it]++;
			}
		}
	}
	return cnt == n-1;
}

int cpy[maxn], ok[maxn];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) 
		scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].c);
	
	sort(e+1, e+1+m);
	
	if (!Kruskal()) return puts("0"), 0;

	int ans = 1, it = 0;
	InitSet();
	for (int i = 1, j; i <= m; i = j) {
		j = i + 1;
		while (j <= m && e[j].c == e[i].c) j++;
		if (e[i].c != cost[it]) continue;
		int cnt = 0;
		memcpy(cpy, fa, sizeof(int)*(n+1));
		for (int s = (1<<(j-i))-1; s; s--) {
			if (__builtin_popcount(s) != num[it]) continue;
			memcpy(fa, cpy, sizeof(int)*(n+1));
			bool flag = true;
			for (int k = i; k < j; k++) {
				if (s & (1<<(k-i))) {
					if (Same(e[k].u, e[k].v)) {
						flag = false;
						break;
					} else {
						Unite(e[k].u, e[k].v);
					}
				}
			}
			if (flag) {
				cnt++;
				if (cnt == 1) memcpy(ok, fa, sizeof(int)*(n+1));
			}
		}
		memcpy(fa, ok, sizeof(int)*(n+1));
		(ans *= cnt) %= mod;
		it++;
	}

	printf("%d\n", ans % mod);

	return 0;
}