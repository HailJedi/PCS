#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const long long INF = 0x3f3f3f3f3f3f3f3f;

struct Update {
  int y, d, t;
  Update() {}
  Update(int y, int d, int t) : y(y), d(d), t(t) {}
};

vector<Update> update[N];
long long f[N][2];
const int tr[2][3] = {
  -1, 0, 0,
   1, 0, 1
};

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int x, y, d, t;
    char s[20];
    scanf("%d %d %d %s", &x, &y, &d, s);
    if (strcmp(s, "Licensed") == 0) {
      t = 0;
    } else
    if (strcmp(s, "Pirated") == 0) {
      t = 1;
    } else {
      t = 2;
    }
    update[x].push_back(Update(y, d, t));
  }
  memset(f, INF, sizeof f);
  f[1][1] = 0;
  for (int x = 1; x < n; x++) {
    for (int t = 0; t < 2; t++) {
      if (f[x][t] != N)
      for (int i = 0; i < (int)update[x].size(); i++) {
        Update &up = update[x][i];
        int nt = tr[t][up.t];
        if (nt != -1) {
          f[up.y][nt] = min(f[up.y][nt], f[x][t] + up.d);
        }
      }
    }
  }
  long long ans = min(f[n][0], f[n][1]);
  if (ans < INF) {
    printf("Online\n");
    printf("%lld\n", ans);
  } else {
    printf("Offline\n");
  }
  return 0;
}
