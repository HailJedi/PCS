/*
Created 2018-10-14
"Non-Coprime Partition"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  if (n <= 2) {
    printf("No\n");
    return 0;
  }
  printf("Yes\n");
  cout << 1 << ' ' << n << endl;
  cout << n-1 << ' ';
  for (int i = 1; i < n; i++) {
    cout << i << ' ';
  }
  cout << endl;
  return 0;
}
