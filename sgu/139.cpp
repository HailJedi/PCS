#include <bits/stdc++.h>

using namespace std;

int main() {
  int chess[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cin >> chess[i][j];
    }
  }
  int par = 0;
  for (int i = 0; i < 16; i++) {
    int r = i / 4, c = i % 4;
    if (chess[r][c] == 0) {
      par += 6 - r - c;
    }
    for (int j = i; j < 16; j++) {
      par += chess[r][c] > chess[j / 4][j % 4];
    }
  }
  cout << (par & 1 ? "YES" : "NO") << endl;
  return 0;
}
