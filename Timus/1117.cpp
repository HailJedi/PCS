#include <bits/stdc++.h>

using namespace std;

const int N = 32;

int f[N];

long long F(int x) {
  long long ret = 0;
  for (int i = N-1; i >= 0; i--) {
    if ((1LL << i) <= x) {
      ret += f[i];
      x -= (1LL << i);
      if (x) {
        ret += i-1;
      }
    }
  }
  return ret;
}

int main() {
  f[2] = 1;
  for (int i = 3; i < N; i++) {
    f[i] = 2 * f[i-1] + i-1;
  }
  int a, b;
  cin >> a >> b;
  cout << abs(F(a) - F(b)) << endl;
  return 0;
}
