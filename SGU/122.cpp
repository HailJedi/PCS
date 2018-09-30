#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

int n, sz;
int ans[N];
bool G[N][N];
bool vis[N];

void reverse(int l, int r) {
  while (l < r) {
    swap(ans[l++], ans[r--]);
  }
}

void solve() {
  int s = 1, t = -1;
  for (t = 2; t <= n; t++) {
    if (G[s][t]) {
      break;
    }
  }
  ans[sz++] = s, ans[sz++] = t;
  vis[s] = vis[t] = true;
  bool found = false;
  while (true) {
    while (true) {
      found = false;
      for (int i = 1; i <= n; i++) {
        if (G[t][i] && !vis[i]) {
          t = i;
          ans[sz++] = t;
          vis[t] = true;
          found = true;
          break;
        }
      }
      if (!found) {
        break;
      }
    }
    reverse(0, sz-1);
    swap(s, t);
    while (true) {
      bool found = false;
      for (int i = 1; i <= n; i++) {
        if (G[t][i] && !vis[i]) {
          t = i;
          ans[sz++] = t;
          vis[t] = true;
          found = true;
          break;
        }
      }
      if (!found) {
        break;
      }
    }
    if (!G[s][t]) {
      for (int i = 1; i < sz-2; i++) {
        if (G[s][ans[i+1]] && G[ans[i]][t]) {
          t = ans[i+1];
          reverse(i+1, sz-1);
          break;
        }
      }
    }
    if (sz == n) {
      return;
    }
    found = false;
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        for (int j = 1; j < sz-1; j++) {
          if (G[i][ans[j]]) {
            s = ans[j-1];
            t = i;
            reverse(0, j-1);
            reverse(j, sz-1);
            ans[sz++] = i;
            vis[i] = true;
            found = true;
            break;
          }
        }
        if (found) {
          break;
        }
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int u = 1; u <= n; u++) {
    int v = 0;
    char c;
    while (scanf("%d%c", &v, &c) == 2) {
      G[u][v] = G[v][u] = 1;
      if (c == '\n') {
        break;
      }
    }
  }
  solve();
  for (int i = 0; i < sz; i++) {
    if (ans[i] == 1) {
      for (int j = i, f = 1; j != i || f; j = (j + 1) % n, f = 0) {
        printf("%d ", ans[j]);
      }
      printf("1\n");
      break;
    }
  }
  return 0;
}
