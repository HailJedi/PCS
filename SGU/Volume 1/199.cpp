#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int INF = 0x3f3f3f3f;

int lis[N];
int f[N];

struct Segment {
  int l, r, id;
  Segment() {}
  bool operator < (const Segment &s) const {
    if (l != s.l) {
      return l < s.l;
    }
    return r > s.r;
  }
} seg[N];

void dfs(int n, int i) {
  if (n) {
    printf("%d ", seg[i].id);
    for (int j = i-1; j >= 1; j--) {
      if (seg[j].r < seg[i].r && f[j] == f[i] - 1) {
        dfs(n-1, j);
        break;
      }
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &seg[i].l, &seg[i].r);
    seg[i].id = i;
  }
  sort(seg+1, seg+1+n);
  memset(lis, INF, sizeof lis);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int it = lower_bound(lis, lis+n, seg[i].r) - lis;
    f[i] = it + 1;
    ans = max(ans, f[i]);
    lis[it] = seg[i].r;
  }
  cout << ans << endl;
  for (int i = n; i >= 1; i--) {
    if (f[i] == ans) {
      dfs(n, i);
      break;
    }
  }
  return 0;
}
