/*
Created 2018-10-10
"You Are Given a Tree"
A counting on tree problem with greedy solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int BLOCK = 100;

int n;
int f[N][2];
vector<int> node;
vector<int> g[N];
int fa[N];

void dfs(int u, int f = 1) {
  for (auto v: g[u]) {
    if (v != f) {
      dfs(v, u);
    }
  }
  node.push_back(u);
  fa[u] = f;
}

int solve(int k) {
  for (int i = 1; i <= n; i++) {
    f[i][0] = f[i][1] = 0;
  }
  int ret = 0;
  for (int u: node) {
    if (f[u][0] + f[u][1] + 1 >= k) {
      ret++;
    } else {
      if (f[fa[u]][0] < f[u][0] + 1) {
        f[fa[u]][1] = f[fa[u]][0];
        f[fa[u]][0] = f[u][0] + 1;
      } else {
        f[fa[u]][1] = max(f[fa[u]][1], f[u][0] + 1);
      }
    }
  }
  return ret;
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
  int x = N, k = 1;
  while (x > BLOCK) {
    x = solve(k++);
    printf("%d\n", x);
  }
  for (int i = BLOCK; i >= 0; i--) {
    if (solve(k) != i || k > n) {
      continue;
    }
    int l = k, r = n + 1;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (solve(mid) == i) {
        l = mid;
      } else {
        r = mid;
      }
    }
    while (k <= l) {
      printf("%d\n", i);
      k++;
    }
  }
  return 0;
}
