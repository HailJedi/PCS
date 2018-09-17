#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;

int col[N];

int main() {
  int n;
  cin >> n;
  int ans = -1;
  for (int i = 2; i <= n; i++) {
    for (int j = i*2; j <= n; j += i) {
      col[j] += (col[j] == col[i]);
    }
    ans = max(ans, col[i]);
  }
  cout << ans + 2 << endl << 1 << ' ';
  for (int i = 2; i <= n; i++) {
    cout << col[i] + 2 << ' ';
  }
  return 0;
}
