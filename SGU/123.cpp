#include <bits/stdc++.h>

using namespace std;

int main() {
  int k;
  cin >> k;
  if (k == 1) {
    cout << 1 << endl;
    return 0;
  }
  long long f[3];
  f[0] = 0, f[1] = 1;
  long long ans = 1;
  for (int i = 2; i <= k; i++) {
    f[2] = f[1] + f[0];
    f[0] = f[1];
    f[1] = f[2];
    ans += f[2];
  }
  cout << ans << endl;
  return 0;
}
