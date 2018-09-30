#include <bits/stdc++.h>

using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3f;
const int N = 100000 + 5;

struct Segment {
  int l, r, d;
  Segment() {}
  Segment(int l, int r, int d) : l(l), r(r), d(d) {}
  bool operator < (const Segment &s) const {
    return d < s.d;
  }
} seg[N];

vector<int> vec;
int id(int x) {
  return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1;
}

int d[N];
int lft[N], rgt[N];
long long f[2][2];

void update(long long &x, long long y) {
  if (x > y) {
    x = y;
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &d[i]);
    vec.push_back(d[i]);
  }
  sort(vec.begin(), vec.end());
  vec.resize(unique(vec.begin(), vec.end())-vec.begin());
  for (int i = 1; i <= n; i++) {
    int x = id(d[i]);
    if (lft[x] == 0) {
      lft[x] = i;
    }
    rgt[x] = i;
  }
  int t = 0;
  f[t][0] = f[t][1] = INF;
  lft[0] = rgt[0] = 1;
  f[t][0] = f[t][1] = 0;
  for (int i = 0; i < (int)vec.size(); i++) {
    f[t^1][0] = f[t^1][1] = INF;
    for (int j = 0; j < 2; j++) {
      if (f[t][j] != INF) {
        int pos = (j ? rgt[i] : lft[i]);
        update(f[t^1][0], f[t][j] + abs(pos - rgt[i+1]) + rgt[i+1] - lft[i+1]);
        update(f[t^1][1], f[t][j] + abs(pos - lft[i+1]) + rgt[i+1] - lft[i+1]);
      }
    }
    t ^= 1;
  }
  printf("%lld\n", min(f[t][0], f[t][1]) + n);
  return 0;
}
