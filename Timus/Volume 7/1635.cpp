#include <bits/stdc++.h>

using namespace std;

const int N = 4000 + 5;
const int INF = 0x3f3f3f3f;

char str[N];
bool pal[N][N];
int pre[N];
int f[N];

bool update(int &x, int y) {
  if (x > y) {
    x = y;
    return true;
  }
  return false;
}

void dfs(int p) {
  if (p) {
    dfs(pre[p]);
    for (int i = pre[p]+1; i <= p; i++) {
      printf("%c", str[i]);
    }
    printf(" ");
  }
}

int main() {
  scanf("%s", str+1);
  int n = strlen(str+1);
  for (int i = 1; i <= n; i++) {
    pal[i][i] = true;
    int l = i, r = i;
    while (l > 1 && r < n && str[l-1] == str[r+1]) {
      l--, r++;
      pal[l][r] = true;
    }
  }
  for (int i = 1; i < n; i++) {
    int l = i, r = i+1;
    if (str[l] == str[r]) {
      pal[l][r] = true;
      while (l > 1 && r < n && str[l-1] == str[r+1]) {
        l--, r++;
        pal[l][r] = true;
      }
    }
  }
  memset(f, INF, sizeof f);
  f[0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j <= n; j++) {
      if (pal[i+1][j] && update(f[j], f[i] + 1)) {
        pre[j] = i;
      }
    }
  }
  printf("%d\n", f[n]);
  dfs(n);
  printf("\n");
  return 0;
}
