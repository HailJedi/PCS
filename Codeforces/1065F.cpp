/*
Created 2018-10-16
"Up and Down the Tree"
A DP solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

int n, k;
vector<int> g[N];
int prt[N], dwn[N], shl[N];

void dfs(int u, int dp) {
  if (g[u].empty()) {
    shl[u] = dp;
    prt[u] = 1;
  } else {
    shl[u] = N;
    for (int v: g[u]) {
      dfs(v, dp+1);
      shl[u] = min(shl[u], shl[v]);
      if (shl[v] - dp <= k) {
        prt[u] += prt[v];
        dwn[u] = max(dwn[u], dwn[v] - prt[v]);
      } else {
        dwn[u] = max(dwn[u], dwn[v]);
      }
    }
  }
  dwn[u] += prt[u];
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 2; i <= n; i++) {
    int p;
    scanf("%d", &p);
    g[p].push_back(i);
  }
  dfs(1, 0);
  printf("%d\n", dwn[1]);
  return 0;
}
