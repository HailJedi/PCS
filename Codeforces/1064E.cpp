/*
Created 2018-10-14
"Dwarves, Hats and Extrasensory Abilities"
A constructive soluiton
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  int l = 0, r = 1e9;
  string base, res;
  cout << 0 << ' ' << 0 << endl;
  cout.flush();
  cin >> base;
  while (--n) {
    int mid = (l + r) / 2;
    cout << mid << ' ' << mid << endl;
    cout.flush();
    cin >> res;
    if (res == base) {
      l = mid;
    } else {
      r = mid;
    }
  }
  cout << l << ' ' << l+1 << ' ' << l+1 << ' ' << l << endl;
  cout.flush();
  return 0;
}
