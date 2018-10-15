/*
Created 2018-10-15
"Trips"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int n, m, k;
vector<pair<int, int>> g[N];
int deg[N], u[N], v[N];
bool vis[N];
int ans[N];

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= m; i++) {
    scanf("%d %d", &u[i], &v[i]);
    g[u[i]].push_back(make_pair(v[i], i));
    g[v[i]].push_back(make_pair(u[i], i));
  }
  int cnt = n;
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    deg[i] = g[i].size();
    if (deg[i] < k) {
      q.push(i);
      cnt--;
    }
  }
  for (int i = m; i >= 1; i--) {
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto e: g[u]) {
        if (!vis[e.second]) {
          vis[e.second] = true;
          if (deg[e.first]-- == k) {
            q.push(e.first);
            cnt--;
          }
        }
      }
    }
    ans[i] = cnt;
    if (!vis[i]) {
      vis[i] = true;
      if (deg[u[i]]-- == k) {
        q.push(u[i]);
        cnt--;
      }
      if (deg[v[i]]-- == k) {
        q.push(v[i]);
        cnt--;
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
