#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int INF = 0x3f3f3f3f;

int f[N][8];
int c[N], v[N];
string vit;

void update(int &x, int y) {
  if (x > y) {
    x = y;
  }
}

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> c[i] >> vit;
    sort(vit.begin(), vit.end());
    for (int j = 0; j < (int)vit.size(); j++) {
      v[i] |= (1 << (vit[j] - 'A'));
    }
  }
  memset(f, INF, sizeof f);
  f[0][0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 8; j++) {
      if (f[i][j] != INF) {
        update(f[i+1][j], f[i][j]);
        update(f[i+1][j | v[i+1]], f[i][j] + c[i+1]);
      }
    }
  }
  int ans = INF;
  for (int i = 1; i <= n; i++) {
    update(ans, f[i][7]);
  }
  cout << (ans == INF ? -1 : ans) << endl;
  return 0;
}
