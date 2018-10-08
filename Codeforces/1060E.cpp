/*
Created 2018-10-08
"Sergey and Subway"
A counting-on-tree problem
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

vector<int> g[N];
int bi[N];
long long ans;
int cnt_bi, n;

int dfs(int u, int f = 0, int bi = 0) {
  int sz = 1;
  cnt_bi += bi;
  for (int v: g[u]) {
    if (v != f) {
      sz += dfs(v, u, bi ^ 1);
    }
  }
  ans += 1LL * sz * (n - sz);
  return sz;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  ans += 1LL * cnt_bi * (n - cnt_bi);
  printf("%lld\n", ans / 2);
  return 0;
}
