#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("read.in", "w", stdout);
  srand(time(NULL));
  int n = rand() % 1000 + 1, k = rand() % 200 + 1, p = rand() % 999999999 + 2;
  cout << n << ' ' << k << ' ' << p << endl;
  return 0;
}
