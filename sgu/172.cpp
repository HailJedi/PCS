#include <bits/stdc++.h>

using namespace std;

const int N = 400 + 5;
const int M = 30000 + 5;

vector<int> g[N];
int col[N];

bool dfs(int u, int c, int &cnt) {
  col[u] =  c;
  cnt += col[u] == col[1];
  for (int i = 0; i < (int)g[u].size(); i++) {
    int v = g[u][i];
    if (col[v] == col[u]) {
      return false;
    }
    if (col[v] == -1) {
      if (!dfs(v, c ^ 1, cnt)) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  memset(col, -1, sizeof col);
  int cnt = 0, ok = 1;
  for (int i = 1; i <= n && ok; i++) {
    if (col[i] == -1) {
      ok &= dfs(i, 0, cnt);
    }
  }
  if (!ok) {
    printf("no\n");
  } else {
    printf("yes\n%d\n", cnt);
    for (int i = 1; i <= n; i++) {
      if (col[i] == col[1]) {
        printf("%d ", i);
      }
    }
    printf("\n");
  }
  return 0;
}
