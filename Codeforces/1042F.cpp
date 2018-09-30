#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

vector<int> g[N];
int n, k, ans;

int dfs(int u, int f = -1) {
  if (g[u].size() > 1) {
    vector<int> st;
    for (int i = 0; i < (int)g[u].size(); i++) {
      int v = g[u][i];
      if (v != f) {
        st.push_back(dfs(v, u) + 1);
      }
    }
    sort(st.begin(), st.end());
    while ((int)st.size() > 1) {
      if (st.back() + st[st.size()-2] <= k) {
        break;
      }
      st.pop_back();
      ans++;
    }
    return st.back();
  }
  return 0;
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    if (g[i].size() > 1) {
      dfs(i);
      break;
    }
  }
  printf("%d\n", ans + 1);
  return 0;
}
