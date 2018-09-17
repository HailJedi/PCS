#include <bits/stdc++.h>

using namespace std;

int main() {
  double x, y, z, l;
  cin >> x >> y >> z;
  l = (y - x) * 60;
  z = l - z;
  double ans = 1.0 - (z * z) / (l * l);
  cout << fixed << setprecision(7) << ans << endl;
  return 0;
}
