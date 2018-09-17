#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

long long a[N];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  long long ans = 0;
  for (int i = 62; i >= 0; i--) {
    for (int j = 1; j <= n; j++) {
      if ((a[j] >> i) & 1) {
        if (((ans >> i) & 1) == 0) {
          ans ^= a[j];
        }
        for (int k = 1; k <= n; k++) {
          if (((a[k] >> i) & 1) && k != j) {
            a[k] ^= a[j];
          }
        }
        a[j] = 0;
        break;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
