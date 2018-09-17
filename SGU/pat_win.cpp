#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

int main() {
  for (int T = 1; T <= 30; T++) {
    system("C:\\SGU\\gen.exe");
    system("C:\\SGU\\126.exe");
    system("C:\\SGU\\std.exe");
    if (system("fc write.out write2.out")) {
      cout << "WA" << endl;
    } else {
      cout << "AC" << endl;
    }
    Sleep(1000);
  }
  return 0;
}
