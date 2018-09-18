#include <bits/stdc++.h>

using namespace std;

const int N = 600 + 5;
const int INF = 0x3f3f3f3f;

struct Tooth {
  int c, p, id;
  Tooth() {}
  bool operator < (const Tooth &t) const {
    return p < t.p;
  }
} th[N];

int b[N];
int f[N][N], pre[N][N];

void dfs(int i, int j) {
  if (j) {
    printf("%d ", th[i].id);
    dfs(pre[i][j], j-1);
  }
}

bool update(int &x, int y) {
  if (x > y) {
    x = y;
    return true;
  }
  return false;
}

int main() {
  freopen("read.in", "r", stdin);
  freopen("write.out", "w", stdout);
  int n, k, p;
  scanf("%d %d %d", &n, &k, &p);
  for (int i = 1; i <= k; i++) {
    scanf("%d", &b[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &th[i].c, &th[i].p);
    th[i].id = i;
  }
  sort(th+1, th+1+n);
  memset(f, INF, sizeof f);
  for (int i = 0; i <= n; i++) {
    f[i][0] = 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      for (int k = j-1; k < i; k++) {
        if (update(f[i][j], f[k][j-1] + th[i].c + (th[k].p != th[i].p) * b[th[i].p])) {
          pre[i][j] = k;
        }
      }
    }
  }
  bool ok = false;
  for (int j = n; j >= 1 && !ok; j--) {
    for (int i = j; i <= n && !ok; i++) {
      if (f[i][j] <= p) {
        printf("%d\n", j);
        // dfs(i, j);
        ok = true;
      }
    }
  }
  if (!ok) {
    printf("0\n");
  }
  return 0;
}
