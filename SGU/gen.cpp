#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("read.in", "w", stdout);
  srand(time(NULL));
  int n = rand() % 10 + 1, m = rand() % 1000 + 1;
  cout << n << ' ' << m << endl;
  for (int i = 1; i <= n; i++) {
    cout << rand() % m + 1 << ' ';
  }
  cout << endl;
  return 0;
}
