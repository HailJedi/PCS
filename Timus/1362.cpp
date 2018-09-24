#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

vector<int> g[N];

int dfs(int u, int f = 0) {
  int ret = 0;
  vector<int> vec;
  for (int i = 0; i < (int)g[u].size(); i++) {
    int v = g[u][i];
    if (v != f) {
      vec.push_back(dfs(v, u));
    }
  }
  sort(vec.begin(), vec.end(), greater<int>());
  for (int i = 0; i < (int)vec.size(); i++) {
    ret = max(ret, vec[i] + i);
  }
  return ret + 1;
}

int main() {
  scanf("%d", &n);
  for (int u = 1; u <= n; u++) {
    int v;
    while (scanf("%d", &v) == 1 && v) {
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }
  int root;
  scanf("%d", &root);
  printf("%d\n", dfs(root) - 1);
  return 0;
}
