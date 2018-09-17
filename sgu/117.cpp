#include <bits/stdc++.h>

using namespace std;

int POW(int a, int n, int k) {
  int b = 1;
  while (n) {
    if (n & 1) {
      (b *= a) %= k;
    }
    (a *= a) %= k;
    n >>= 1;
  }
  return b;
}

int main() {
  int n, m, k, ans = 0;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    ans += (!POW(a, m, k));
  }
  cout << ans << endl;
  return 0;
}
