/*
Created 2018-10-14
"A Game on Strings"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n, q;
int sum[N];
int pre[26][N], suf[26][N];
int pref[26][N], suff[26][N];
bool vis[27];
char s[N];

int solve(int l, int r) {
  for (int c = 0; c <= 26; c++) {
    vis[c] = false;
  }
  for (int c = 0; c < 26; c++) {
    if (suf[c][l] <= r) {
      int x = suf[c][l], y = pre[c][r];
      vis[suff[c][l] ^ sum[x] ^ sum[y] ^ pref[c][r]] = true;
    }
  }
  for (int i = 0; ; i++) {
    if (!vis[i]) {
      return i;
    }
  }
}

int main() {
  scanf("%s", s+1);
  n = strlen(s+1);
  for (int i = 1; i <= n; i++) {
    for (int c = 0; c < 26; c++) {
      pre[c][i] = pre[c][i-1];
    }
    pre[s[i]-'a'][i] = i;
  }
  for (int c = 0; c < 26; c++) {
    suf[c][n+1] = n+1;
  }
  for (int i = n; i >= 1; i--) {
    for (int c = 0; c < 26; c++) {
      suf[c][i] = suf[c][i+1];
    }
    suf[s[i]-'a'][i] = i;
  }
  for (int i = 1; i <= n; i++) {
    int cc = s[i]-'a';
    if (pre[cc][i-1]) {
      sum[i] = sum[pre[cc][i-1]] ^ pref[cc][i-1];
    }
    for (int j = i-1; j > pre[cc][i-1]; j--) {
      suff[cc][j] = solve(j, i-1);
    }
    vector<pair<int, int>> todo;
    for (int c = 0; c < 26; c++) {
      if (pre[c][i]) {
        todo.push_back(make_pair(pre[c][i], c));
      }
    }
    sort(todo.begin(), todo.end(), greater<pair<int, int>>());
    for (auto p: todo) {
      int c = p.second;
      if (pre[c][i]+1 <= i) {
        pref[c][i] = solve(pre[c][i]+1, i);
      }
    }
  }
  scanf("%d", &q);
  while (q--) {
    int l, r;
    scanf("%d %d", &l, &r);
    printf("%s\n", solve(l, r) ? "Alice" : "Bob");
  }
  return 0;
}
