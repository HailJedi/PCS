/*
Created 2018-10-14
"Make a triangle!"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
  int a, b, c;
  cin >> a >> b >> c;
  int sum = a + b + c;
  int mx = max(a, max(b, c));
  if (sum - mx <= mx) {
    cout << mx - sum + mx + 1 << endl;
  } else {
    cout << 0 << endl;
  }
  return 0;
}
