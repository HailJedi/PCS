#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int K = 100 + 5;

struct Segment {
  int l, r;
  Segment() {}
  bool operator < (const Segment &s) const {
    if (l != s.l) {
      return l < s.l;
    }
    return r > s.r;
  }
} seg[N];

int n, k;
int hsh[N];
int f[N][K];
int lft[N];

void update(int &x, int y) {
  if (x < y) {
    x = y;
  }
}

int main() {
  freopen("lifeguards.in", "r", stdin);
  freopen("lifeguards.out", "w", stdout);
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &seg[i].l, &seg[i].r);
  }
  sort(seg+1, seg+1+n);
  int rp = 0, t = 0;
  for (int i = 1; i <= n; i++) {
    if (seg[i].r > rp) {
      seg[++t] = seg[i];
      rp = seg[i].r;
    }
  }
  k -= (n - t);
  n = t;
  if (k <= 0) {
    int rp = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
      ans += seg[i].r - max(rp, seg[i].l);
      rp = seg[i].r;
    }
    printf("%d\n", ans);
  } else {
    int p = 1;
    for (int i = 1; i <= n; i++) {
      while (seg[p].r < seg[i].l) {
        p++;
      }
      lft[i] = p;
    }
    memset(f, -1, sizeof f);
    f[1][0] = seg[1].r - seg[1].l;
    f[1][1] = 0;
    f[0][0] = 0;
    for (int i = 2; i <= n; i++) {
      for (int j = 0; j <= k; j++) {
        update(f[i][j], f[i-1][j]);
        int del = i - lft[i] + 1;
        if (j + del <= k) {
          update(f[i][j], f[lft[i]][j-del] + seg[i].r - seg[lft[i]].r);
        }

      }
    }
  }
  return 0;
}
