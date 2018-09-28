#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int fa[N], rk[N];
pair<int, pair<int, int> > edge[N], query[N];
int ans[N];

int find(int x) {
  return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
  x = find(x), y = find(y);
  if (x != y) {
    if (rk[x] < rk[y]) {
      rk[y] += rk[x];
      fa[x] = y;
    } else {
      rk[x] += rk[y];
      fa[y] = x;
    }
  }
}

int main() {
  freopen("mootube.in", "r", stdin);
  freopen("mootube.out", "w", stdout);
  int n, q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    rk[i] = 1;
  }
  for (int i = 1; i < n; i++) {
    int u, v, r;
    scanf("%d %d %d", &u, &v, &r);
    edge[i] = make_pair(-r, make_pair(u, v));
  }
  sort(edge+1, edge+n);
  for (int i = 1; i <= q; i++) {
    int v, k;
    scanf("%d %d", &k, &v);
    query[i] = make_pair(-k, make_pair(v, i));
  }
  sort(query+1, query+1+q);
  int pt = 1;
  for (int i = 1; i <= q; i++) {
    while (pt < n && -edge[pt].first >= -query[i].first) {
      unite(edge[pt].second.first, edge[pt].second.second);
      pt++;
    }
    ans[query[i].second.second] = rk[find(query[i].second.first)];
  }
  for (int i = 1; i <= q; i++) {
    printf("%d\n", ans[i]-1);
  }
  return 0;
}
