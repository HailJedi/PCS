#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 100 + 5;

char str[N];
int f[N][N];
int pre[N][N];

bool update(int &x, int y) {
  if (x > y) {
    x = y;
    return true;
  }
  return false;
}

bool match(char l, char r) {
  return (l == '(' && r == ')') || (l == '[' && r == ']');
}

void print(int l, int r) {
  if (l > r) {
    return;
  }
  if (pre[l][r] == -2) {
    printf("%c", str[l]);
    print(l+1, r-1);
    printf("%c", str[r]);
  } else
  if (l == r) {
    printf("%s", (str[l] == '(' || str[l] == ')') ? "()" : "[]");
  } else {
    print(l, pre[l][r]);
    print(pre[l][r]+1, r);
  }
}

int main() {
  scanf("%s", str+1);
  int n = strlen(str+1);
  memset(f, INF, sizeof f);
  for (int i = 1; i <= n; i++) {
    f[i][i] = 1;
  }
  for (int i = 1; i <= n; i++) {
    f[i][i-1] = 0;
  }
  for (int len = 2; len <= n; len++) {
    for (int l = 1, r = l+len-1; r <= n; l++, r++) {
      if (match(str[l], str[r]) && update(f[l][r], f[l+1][r-1])) {
        pre[l][r] = -2;
      }
      for (int i = l; i < r; i++) {
        if (update(f[l][r], f[l][i] + f[i+1][r])) {
          pre[l][r] = i;
        }
      }
    }
  }
  print(1, n);
  return 0;
}
