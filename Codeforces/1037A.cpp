/*
Created 2018-10-15
"Packets"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  int ans = 0;
  for (; n; ans++, n >>= 1);
  cout << ans << endl;
  return 0;
}
