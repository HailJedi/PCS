#include <bits/stdc++.h>

using namespace std;

const int N = 20;

long long fac[N];

int main() {
  int n, k;
  cin >> n >> k;
  if (k > n) {
    cout << 0 << endl;
    return 0;
  }
  fac[0] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = fac[i-1] * i;
  }
  cout << (fac[n] / fac[k] / fac[n-k]) * (fac[n] / fac[k] / fac[n-k]) * fac[k] << endl;
  return 0;
}
