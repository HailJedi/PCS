#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int mst[40];
int f[1<<17];
int dmg[1<<17];
int n, shft;

int shl(int x) {
  return 1 << x;
}

int dam(int s) {
  if (dmg[s] != -1) {
    return dmg[s];
  }
  dmg[s] = 0;
  for (int i = 0; i < n-3; i++) {
    if (s & shl(i)) {
      dmg[s] += mst[i+shft];
    }
  }
  return dmg[s];
}

int dfs(int s) {
  if (f[s] != -1) {
    return f[s];
  }
  f[s] = INF;
  for (int i = 0; i+2 < n-3; i++) {
    int t = shl(i) | shl(i+1) | shl(i+2);
    if (s & t) {
      f[s] = min(f[s], dfs(s & (~t)) + dam(s & (~t)));
    }
  }
  return f[s];
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> mst[i];
    mst[i+n] = mst[i];
  }
  int ans = INF;
  for (int i = 1; i <= n; i++) {
    shft = i+3;
    memset(dmg, -1, sizeof dmg);
    memset(f, -1, sizeof f);
    f[0] = 0;
    ans = min(ans, dfs(shl(n-3)-1) + dam(shl(n-3)-1));
  }
  cout << ans << endl;
  return 0;
}
