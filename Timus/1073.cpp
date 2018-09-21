#include <bits/stdc++.h>

using namespace std;

const int N = 60000 + 5;

void update(int &x, int y) {
  if (x > y) {
    x = y;
  }
}

int f[N];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    f[i] = i;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 1; i + j * j <= n; j++) {
      update(f[i+j*j], f[i] + 1);
    }
  }
  cout << f[n] << endl;
  return 0;
}
