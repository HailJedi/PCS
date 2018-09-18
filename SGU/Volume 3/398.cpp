#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;

vector<int> g[N];
bool mark[N];

int main() {
  int n, x;
  scanf("%d %d", &n, &x);
  for (int i = 1; i <= n; i++) {
    int k;
    scanf("%d", &k);
    while (k--) {
      int y;
      scanf("%d", &y);
      g[i].push_back(y);
    }
  }
  for (int i = 0; i < g[x].size(); i++) {
    mark[g[x][i]] = true;
  }
  int ans = 0;
  vector<int> vec;
  for (int i = 1; i <= n; i++) if (mark[i]) {
    for (int j = 0; j < g[i].size(); j++) {
      if (!mark[g[i][j]]) {
        ans++;
        vec.push_back(g[i][j]);
        mark[g[i][j]] = true;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
