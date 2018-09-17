#include <bits/stdc++.h>

using namespace std;

int main() {
  for (int T = 1; T <= 1000; T++) {
    system("./gen");
    system("./375");
    system("./checker");
    if (system("diff read.in checker.out")) {
      cout << "WA" << endl;
      return 0;
    }
  }
  cout << "AC" << endl;
  return 0;
}
