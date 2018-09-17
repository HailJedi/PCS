#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

vector<int> g[N];
int lvl[N];
bool inq[N];
int sg[N];

void bfs() {
  queue<int> q;
  q.push(1);
  inq[1] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < g[u].size(); i++) {
      int v = g[u][i];
      if (!inq[v]) {
        inq[v] = true;
        q.push(v);
        lvl[v] = lvl[u] + 1;
      }
    }
  }
}

void dfs(int u) {
  sg[u] = 0;
  for (int i = 0; i < g[u].size() && !sg[u]; i++) {
    int v = g[u][i];
    if (lvl[v] == lvl[u] + 1) {
      dfs(v);
      sg[u] |= (!sg[v]);
    }
  }
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
  bfs();
  dfs(1);
  printf("%s\n", sg[1] ? "Vladimir" : "Nikolay");
  return 0;
}
