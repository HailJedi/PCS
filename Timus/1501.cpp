#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

bool f[N][N];
int pre[N][N];
int n;

void print(int p1, int p2) {
  if (p1 != 1 || p2 != 1) {
    assert(f[p1][p2] == true);
    if (pre[p1][p2] == 0) {
      print(p1-1, p2);
    } else {
      print(p1, p2-1);
    }
    printf("%d", pre[p1][p2] + 1);
  }
}

char pile[2][N];
int sum[2][2][N];

bool test(int i, int j) {
  return abs((sum[0][0][i] + sum[1][0][j]) - (sum[0][1][i] + sum[1][1][j])) <= 1;
}

int main() {
  scanf("%d %s %s", &n, pile[0]+1, pile[1]+1);
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j <= n; j++) {
      sum[i][0][j] = sum[i][0][j-1] + (pile[i][j] == '0');
      sum[i][1][j] = sum[i][1][j-1] + (pile[i][j] == '1');
    }
  }
  f[1][1] = true;
  for (int i = 1; i <= n+1; i++) {
    for (int j = 1; j <= n+1; j++) {
      if (f[i][j] == true) {
        if (i <= n && test(i, j-1)) {
          f[i+1][j] = true;
          pre[i+1][j] = 0;
        }
        if (j <= n && test(i-1, j)) {
          f[i][j+1] = true;
          pre[i][j+1] = 1;
        }
      }
    }
  }
  if (!f[n+1][n+1]) {
    printf("Impossible\n");
  } else {
    print(n+1, n+1);
  }
  return 0;
}
