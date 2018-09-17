#include <bits/stdc++.h>

using namespace std;

const int N = 16000 + 5;
const int INF = 1e9;

vector<int> g[N];
int n;
int sz[N];
int val[N];

int dfs(int u, int f, int &cen) {
  int szu = 1;
  val[u] = -INF;
  for (int i = 0; i < g[u].size(); i++) {
    int v = g[u][i];
    if (v != f) {
      int szv = dfs(v, u, cen);
      val[u] = max(val[u], szv);
      szu += szv;
    }
  }
  val[u] = max(val[u], n - szu);
  cen = min(cen, val[u]);
  return szu;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int cen = INF;
  dfs(1, 0, cen);
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    if (val[i] == cen) {
      ans.push_back(i);
    }
  }
  cout << cen << ' ' << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << ' ';
  }
  cout << endl;
  return 0;
}
