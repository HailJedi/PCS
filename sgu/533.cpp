#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  if (n < 28 && n != 21) {
    cout << -1 << endl;
    return 0;
  }
  int tow = n / 14, r = n % 14;
  if (2 <= r && r <= 12) {
    cout << tow << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}
