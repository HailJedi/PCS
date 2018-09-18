#include <bits/stdc++.h>

using namespace std;

int main() {
  int T, n;
  cin >> T;
  while (T--) {
    cin >> n;
    int a, b, sum = 0;
    cin >> b;
    b %= 9;
    sum += b;
    for (int i = 2; i <= n; i++) {
      cin >> a;
      b = a % 9 * b % 9;
      sum += b;
    }
    sum %= 9;
    cout << (sum ? sum : 9) << endl;
  }
  return 0;
}
