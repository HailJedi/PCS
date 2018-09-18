#include <bits/stdc++.h>

using namespace std;

int main() {
  int k;
  cin >> k;
  if (k == 1) {
    cout << 8 << endl;
  } else
  if ((k - 1) % 6 == 0) {
    cout << 4 << endl;
  } else
  if ((k - 1) % 3 == 0) {
    cout << 3 << endl;
  } else {
    cout << 1 << endl;
  }
  return 0;
}
