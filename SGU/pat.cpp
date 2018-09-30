#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

int main() {
  for (int T = 1; T <= 100; T++) {
    cout << T << ' ';
    system("./gen");
    system("./std");
    system("./test");
    if (system("diff write.out write2.out")) {
      cout << "WA" << endl;
    } else {
      cout << "AC" << endl;
    }
    usleep(1000000);
  }
  return 0;
}
