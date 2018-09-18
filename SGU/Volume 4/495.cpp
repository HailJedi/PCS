#include <bits/stdc++.h>

using namespace std;

int main() {
  double n, m;
  cin >> n >> m;
  double ans = 0;
  for (int i = 1; i <= m; i++) {
    ans += (n-ans) / n;
  }
  cout << fixed << setprecision(9) << ans << endl;
  return 0;
}
