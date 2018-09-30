#include <bits/stdc++.h>

using namespace std;

long long A, B, C, x0;

long long f(long long x) {
  return (A * x + x % B) % C;
}

int main() {
  cin >> A >> B >> C;
  x0 = 1;
  long long x = f(x0), y = f(x);
  int v = 1;
  while (x != y && v <= 2e6) {
    x = f(x), y = f(f(y));
    v++;
  }
  if (v > 2e6) {
    cout << -1 << endl;
    return 0;
  }
  int u = 0;
  x = x0;
  while (x != y && u <= 2e6) {
    x = f(x), y = f(y);
    u++;
  }
  if (u > 2e6) {
    cout << -1 << endl;
    return 0;
  }
  int lam = 1;
  x = f(x);
  while (x != y && u+lam <= 2e6) {
    x = f(x);
    lam++;
  }
  if (u+lam > 2e6) {
    cout << -1 << endl;
    return 0;
  }
  cout << u + lam << endl;
  return 0;
}
