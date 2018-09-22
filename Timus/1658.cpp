#include <bits/stdc++.h>

using namespace std;

const int S1 = 900 + 20;
const int S2 = 8100 + 20;
const int INF = 0x3f3f3f3f;

int f[S1][S2];

void dfs(int s1, int s2) {
  if (s1 > 0) {
    for (int i = 1; i < 10; i++) {
      if (s1 - i >= 0 && s2-i*i >= 0 && f[s1-i][s2-i*i] == f[s1][s2] - 1) {
        printf("%d", i);
        dfs(s1-i, s2-i*i);
        return;
      }
    }
  }
}

void update(int &x, int y) {
  if (x >= y) {
    x = y;
  }
}

int main() {
  memset(f, INF, sizeof f);
  f[0][0] = 0;
  for (int i = 0; i <= 900; i++) {
    for (int j = 0; j <= 8100; j++) {
      if (f[i][j] < 100) {
        for (int k = 1; k < 10; k++) {
          update(f[i+k][j+k*k], f[i][j] + 1);
        }
      }
    }
  }
  int T;
  scanf ("%d", &T);
  while (T--) {
    int s1, s2;
    scanf("%d %d", &s1, &s2);
    if (s1 > 900 || s2 > 8100) {
      printf("No solution\n");
      continue;
    }
    if (f[s1][s2] > 100) {
      printf("No solution\n");
    } else {
      dfs(s1, s2);
      printf("\n");
    }
  }
  return 0;
}
