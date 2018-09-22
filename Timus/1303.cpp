#include <bits/stdc++.h>

using namespace std;

const int M = 5000 + 5;
const int N = 100000 + 5;
const int INF = 0x3f3f3f3f;

struct Segment {
  int l, r;
  Segment() {}
  Segment(int l, int r) : l(l), r(r) {}
  bool operator < (const Segment &s) const {
    if (l != s.l) {
      return l < s.l;
    }
    return r > s.r;
  }
} seg[N];

int main() {
  int m;
  scanf("%d", &m);
  int n = 0, l = 0, r = 0;
  while (scanf("%d %d", &l, &r) == 2 && (l != 0 || r != 0)) {
    if (l != r) {
      seg[++n] = Segment(l, r);
    }
  }
  sort(seg+1, seg+1+n);
  int t = 1;
  for (int i = 2; i <= n; i++) {
    if (seg[i].r > seg[t].r) {
      seg[++t] = seg[i];
    }
  }
  n = t;
  t = 0;
  int p = 0;
  for (int i = 1; i <= n; i++) {
    if (seg[i].l > p || p >= m) {
      break;
    }
    if (i == n || seg[i+1].l > p) {
      seg[++t] = seg[i];
      p = seg[i].r;
    }
  }
  if (p < m) {
    printf("No solution\n");
  } else {
    printf("%d\n", t);
    for (int i = 1; i <= t; i++) {
      printf("%d %d\n", seg[i].l, seg[i].r);
    }
  }
  return 0;
}
