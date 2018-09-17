#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;

int n;
char str[N], str2[N];
vector<int> pos, pos2;

int main() {
  int n;
  scanf("%s %s", str, str2);
  n = strlen(str);
  for (int i = 0; i < n; i++) {
    if (str[i] == '+') {
      pos.push_back(i);
    }
    if (str2[i] == '+') {
      pos2.push_back(i);
    }
  }
  if (pos.size() != pos2.size()) {
    printf("-1");
  } else {
    int ans = 0;
    for (int i = 0; i < (int)pos.size(); i++) {
      ans += abs(pos[i] - pos2[i]);
    }
    printf("%d\n", ans);
  }
  return 0;
}
