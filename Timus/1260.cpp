#include <bits/stdc++.h>

using namespace std;

const int N = 60;

long long f[N];

int main() {
  int n;
  cin >> n;
  f[1] = f[2] = 1;
  f[3] = 2;
  for (int i = 4; i <= n; i++) {
    f[i] = f[i-1] + f[i-3] + 1;
  }
  cout << f[n] << endl;
  return 0;
}
