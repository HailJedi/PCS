/*
Created 2018-10-14
"Equations of Mathematical Magic"
A xor problem
*/

#include <bits/stdc++.h>

using namespace std;

long long pw[40];

int main() {
  int t;
  scanf("%d", &t);
  pw[0] = 1;
  for (int i = 1; i < 40; i++) {
    pw[i] = pw[i-1] * 2;
  }
  while (t--) {
    int a;
    scanf("%d\n", &a);
    cout << pw[__builtin_popcount(a)] << endl;
  }
  return 0;
}
