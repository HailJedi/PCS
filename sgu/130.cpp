#include <bits/stdc++.h>

using namespace std;

const int N = 30;

long long ktl[N];

int main() {
  int k;
  cin >> k;
  ktl[1] = 1;
  for (int i = 2; i <= k; i++) {
    ktl[i] = (4 * i - 2) * ktl[i-1] / (i + 1);
  }
  cout << ktl[k] << ' ' << k + 1 << endl;
  return 0;
}
