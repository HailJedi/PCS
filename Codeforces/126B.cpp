/*
Created 2018-09-29
B. Password
A Z-function solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

char str[N];
int z[N];

int main() {
  scanf("%s", str);
  int n = strlen(str);
  int L = 0, R = 0;
  for (int i = 1; i < n; i++) {
    if (i > R) {
      L = R = i;
    } else {
      int k = i - L;
      if (z[k] < R-i+1) {
        z[i] = z[k];
        continue;
      }
      L = i;
    }
    while (R < n && str[R-L] == str[R]) {
      R++;
    }
    z[i] = R-L;
    R--;
  }
  int match = 0;
  for (int i = 1; i < n; i++) {
    if (z[i] == n-i && match >= z[i]) {
      for (int j = i, k = 1; k <= z[i]; k++, j++) {
        printf("%c", str[j]);
      }
      printf("\n");
      return 0;
    }
    match = max(match, z[i]);
  }
  printf("Just a legend\n");
  return 0;
}
