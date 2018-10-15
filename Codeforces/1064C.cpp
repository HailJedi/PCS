/*
Created 2018-10-14
"Oh Those Palindromes"
A greedy solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

char s[N];
int cnt[26];
int n;

int main() {
  scanf("%d %s", &n, s+1);
  for (int i = 1; i <= n; i++) {
    cnt[s[i]-'a']++;
  }
  for (int i = 0; i < 26; i++) {
    while (cnt[i]--) {
      printf("%c", 'a'+i);
    }
  }
  printf("\n");
  return 0;
}
