#include <bits/stdc++.h>

using namespace std;

int rowlim, n, k;

void dfs(int d, int row, int ld, int rd, int &ans) {
  if (d == n) {
    ans += __builtin_popcount(row) == k;
  } else {
    dfs(d+1, row, ld << 1, rd >> 1, ans);
    int pos = rowlim & (~(row | ld | rd));
    while (pos) {
      int p = pos & -pos;
      pos -= p;
      dfs(d+1, row | p, (ld | p) << 1, (rd | p) >> 1, ans);
    }
  }
}

int main() {
  cin >> n >> k;
  if (k > n) {
    cout << 0 << endl;
    return 0;
  }
  int ans = 0;
  rowlim = (1 << n) - 1;
  dfs(0, 0, 0, 0, ans);
  cout << ans << endl;
  return 0;
}
