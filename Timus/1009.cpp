#include <bits/stdc++.h>

using namespace std;

const int N = 20;

long long f[N];

int main() {
  int n, k;
  cin >> n >> k;
  f[1] = k-1;
  f[2] = f[1] * f[1];
  for (int i = 3; i <= n; i++) {
    f[i] = (k - 1) * (f[i-1] + f[i-2]);
  }
  cout << f[n] + f[n-1] << endl;
  return 0;
}
