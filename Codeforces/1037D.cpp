/*
Created 2018-10-15
"Valid BFS?"
A BFS solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int n;
vector<int> g[N];
bool vis[N];
int order[N];

bool cmp(int x, int y) {
  return order[x] < order[y];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  queue<int> q, q2;
  for (int i = 1; i <= n; i++) {
    int u;
    scanf("%d", &u);
    order[u] = i;
    q2.push(u);
  }
  for (int i = 1; i <= n; i++) {
    sort(g[i].begin(), g[i].end(), cmp);
  }
  q.push(1);
  vis[1] = true;
  bool ok = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (u != q2.front()) {
      ok = false;
      break;
    }
    q2.pop();
    for (auto v: g[u]) {
      if (!vis[v]) {
        vis[v] = true;
        q.push(v);
      }
    }
  }
  printf("%s\n", ok ? "Yes" : "No");
  return 0;
}
