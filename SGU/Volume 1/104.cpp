#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

int f[N][N], p[N][N], val[N][N];
int pos[N];

bool update(int &x, int y) {
  if (x < y) {
    x = y;
    return true;
  }
  return false;
}

int main() {
  int F, V;
  cin >> F >> V;
  for (int i = 1; i <= F; i++) {
    for (int j = 1; j <= V; j++) {
      cin >> val[i][j];
    }
  }
  memset(f, -INF, sizeof f);
  f[0][0] = 0;
  int ans = -1;
  for (int i = 1; i <= F; i++) {
    for (int j = i; j <= V; j++) {
      for (int k = 0; k < j; k++) {
        if (update(f[i][j], f[i-1][k] + val[i][j])) {
          p[i][j] = k;
        }
      }
      if (i == F && (ans == -1 || f[F][ans] < f[F][j])) {
        ans = j;
      }
    }
  }
  cout << f[F][ans] << endl;
  for (int i = F; i >= 1; i--) {
    pos[i] = ans;
    ans = p[i][ans];
  }
  for (int i = 1; i <= F; i++) {
    cout << pos[i] << ' ';
  }
  cout << endl;
  return 0;
}
