#include <bits/stdc++.h>

using namespace std;

const int N = 16000 + 5;
const int INF = 0x3f3f3f3f;

int f[N][2];
vector<int> g[N];
int val[N];

void update(int &x, int y) {
  if (x < y) {
    x = y;
  }
}

void dfs(int u, int fa) {
  f[u][0] = 0;
  f[u][1] = val[u];
  for (int i = 0; i < (int)g[u].size(); i++) {
    int v = g[u][i];
    if (v != fa) {
      dfs(v, u);
      update(f[u][0], max(f[v][0], f[v][1]));
      f[u][1] += max(0, f[v][1]);
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  bool judge = false;
  int mx = -INF;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &val[i]);
    update(mx, val[i]);
    judge |= (val[i] >= 0);
  }
  if (!judge) {
    printf("%d\n", mx);
    return 0;
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  memset(f, -INF, sizeof f);
  dfs(1, 0);
  printf("%d\n", max(f[1][0], f[1][1]));
  return 0;
}
