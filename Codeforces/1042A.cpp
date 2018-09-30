#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int a[N];
int n, m;

int main() {
  cin >> n >> m;
  int mx = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    mx = max(mx, a[i]);
  }
  int mn = 0;
  for (int i = 1; i <= n; i++) {
    mn += mx - a[i];
  }
  if (m <= mn) {
    cout << mx << ' ' << mx + m << endl;
  } else {
    cout << mx + (m-mn+n-1) / n << ' ' << mx + m << endl;
  }
  return 0;
}
