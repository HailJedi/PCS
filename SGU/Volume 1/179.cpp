#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;

char brak[N];
int f[N];

int main() {
  scanf("%s", brak+1);
  int n = strlen(brak+1);
  for (int i = 1; i <= n; i++) {
    f[i] = f[i-1] + (brak[i] == '(' ? 1 : -1);
  }
  bool found = false;
  for (int i = n; i >= 1; i--) {
    if (brak[i] == '(' && f[i] > 1) {
      found = true;
      brak[i] = ')';
      f[i] -= 2;
      for (int j = i+1; j <= n; j++) {
        brak[j] = '(';
        f[j] = f[j-1] + 1;
      }
      for (int j = n; f[n]; j--, f[n] -= 2) {
        brak[j] = ')';
      }
      for (int j = 1; j <= n; j++) {
        printf("%c", brak[j]);
      }
      break;
    }
  }
  if (!found) {
    printf("No solution\n");
  }
  return 0;
}
