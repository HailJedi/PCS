#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  if (!(n & 1)) {
    cout << "No solution" << endl;
    return 0;
  }
  queue<int> q;
  map<int, bool> inq;
  map<int, int> dist, pre;
  q.push(n);
  inq[n] = true;
  dist[n] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    inq[u] = false;
    if (u == 1) {
      break;
    }
    for (int i = -1; i <= 1; i += 2) {
      int v = (u + i) / 2;
      if ((v & 1) && (!dist.count(v) || dist[v] > dist[u] + 1)) {
        dist[v] = dist[u] + 1;
        pre[v] = u;
        if (!inq[v]) {
          q.push(v);
          inq[v] = true;
        }
      }
    }
  }
  if (!dist.count(1)) {
    printf("No solution\n");
  } else {
    vector<int> ans;
    int u = 1;
    while (u != n) {
      int v = pre[u];
      if (v == 2 * u - 1) {
        ans.push_back(1);
      } else {
        ans.push_back(2);
      }
      u = v;
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); i++) {
      printf("%d ", ans[i]);
    }
    printf("\n");
  }
  return 0;
}
