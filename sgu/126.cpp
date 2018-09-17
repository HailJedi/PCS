#include <bits/stdc++.h>

using namespace std;

const int INF = 2147483647;

int gcd(int a, int b) {
  return !b ? a : gcd(b, a % b);
}

int main() {
  // freopen("read.in", "r", stdin);
  // freopen("write.out", "w", stdout);
  int a, b;
  cin >> a >> b;
  if (a == 0 || b == 0) {
    cout << 0 << endl;
    return 0;
  }
  if (a > b) {
    swap(a, b);
  }
  int ans = 0;
  while (true) {
    if ((a ^ b) & 1) {
      ans = -1;
      break;
    }
    int g = gcd(a, b);
    a /= g;
    b /= g;
    b -= a;
    a += a;
    ans++;
    if (a > b) {
      swap(a, b);
    }
    if (a == 0) {
      break;
    }
  }
  printf("%d\n", ans);
  return 0;
}
