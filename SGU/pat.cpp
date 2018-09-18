#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

int main() {
  for (int T = 1; T <= 100; T++) {
    cout << "Case " << T << ' ';
    system("./gen");
    system("./std");
    system("./test");
    if (system("diff write.out write2.out")) {
      cout << "WA" << endl;
      return 0;
    }
    cout << "AC" << endl;
    usleep(1000000);
  }
  return 0;
}
