#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int K = 200 + 5;

int n, k, p;
long long f[2][K][K];

void add(long long &x, long long y) {
  x += y;
  if (x > p) {
    x -= p;
  }
}

int main() {
  cin >> n >> k >> p;
  int t = 0;
  f[t][1][0] = 1;
  for (int i = 1; i <= n; i++) {
    t ^= 1;
    memset(f[t], 0, sizeof f[t]);
    for (int mx = 2; mx <= k; mx++) {
      long long sum = f[t^1][mx][0];
      for (int lim = 1; lim < mx; lim++) {
        add(sum, f[t^1][mx][lim]);
        add(f[t][mx][lim], sum);
      }
    }
    for (int lim = 0; lim < k; lim++) {
      long long sum = 0;
      for (int mx = lim+1; mx <= k; mx++) {
        add(sum, f[t^1][mx][lim]);
        add(f[t][mx][lim], sum);
      }
    }
  }
  long long ans = 0;
  for (int mx = 1; mx <= k; mx++) {
    for (int lim = 0; lim < mx; lim++) {
      add(ans, f[t][mx][lim]);
    }
  }
  add(ans, 1);
  cout << ans << endl;
  return 0;
}
