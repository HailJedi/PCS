/*
Created 2018-10-11
"Network Safety"
A counting problem on graph
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 500000 + 5;
const int K = 60 + 5;
const int mod = 1e9 + 7;

int n, m, k;
tuple<long long, int, int> edge[N];
long long c[N];
int pw[N];

int fa[N], sz[N];

int find(int x) {
  return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
  if (sz[x] < sz[y]) {
    fa[x] = y;
    sz[y] += sz[x];
  } else {
    fa[y] = x;
    sz[x] += sz[y];
  }
}

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &c[i]);
  }
  set<long long> st;
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    edge[i] = make_tuple(c[u] ^ c[v], u, v);
    st.insert(c[u] ^ c[v]);
  }
  sort(edge+1, edge+1+m);
  pw[0] = 1;
  for (int i = 1; i < N; i++) {
    pw[i] = 1LL * pw[i-1] * 2 % mod;
  }
  int ans = 1LL * pw[n] * (pw[k] - st.size() + mod) % mod;
  int pt = 1;
  vector<int> rec;
  for (int i = 1; i <= n; i++) {
    rec.push_back(i);
  }
  while (pt <= m) {
    for (int u: rec) {
      fa[u] = u;
      sz[u] = 1;
    }
    rec.clear();
    long long w = get<0>(edge[pt]);
    int cnt = n;
    while (pt <= m && get<0>(edge[pt]) == w) {
      int u = get<1>(edge[pt]), v = get<2>(edge[pt]);
      if (find(u) != find(v)) {
        unite(find(u), find(v));
        cnt--;
        rec.push_back(u);
        rec.push_back(v);
      }
      pt++;
    }
    ans = (ans + pw[cnt]) % mod;
  }
  printf("%d\n", ans);
  return 0;
}
