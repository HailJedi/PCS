/*
Created 2018-09-29
A. In Search of an Easy Problem
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, a, b = 0;
  cin >> n;
  while (n--) {
    cin >> a;
    b |= a;
  }
  cout << (b ? "HARD" : "EASY") << endl;
  return 0;
}
