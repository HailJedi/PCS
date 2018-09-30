#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int upper_sum[N], lower_sum[N], digit_sum[N];

int lowbit(int x) {
  return x & -x;
}

void add(int *bit, int p) {
  for (; p < N; p += lowbit(p)) {
    bit[p] += 1;
  }
}

int sum(int *bit, int p) {
  int ret = 0;
  for (; p; p -= lowbit(p)) {
    ret += bit[p];
  }
  return ret;
}

char password[N];

bool is_lower_case(char c) {
  return 'a' <= c && c <= 'z';
}

bool is_upper_case(char c) {
  return 'A' <= c && c <= 'Z';
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", password+1);
    int n = strlen(password+1);
    memset(lower_sum, 0, sizeof lower_sum);
    memset(upper_sum, 0, sizeof upper_sum);
    memset(digit_sum, 0, sizeof digit_sum);
    for (int i = 1; i <= n; i++) {
      if (is_lower_case(password[i])) {
        add(lower_sum, i);
      } else
      if (is_upper_case(password[i])) {
        add(upper_sum, i);
      } else {
        add(digit_sum, i);
      }
    }
    if (sum(digit_sum, n) > 0 && sum(lower_sum, n) > 0 && sum(upper_sum, n) > 0) {
      printf("%s\n", password+1);
      continue;
    }
    bool ok = false;
    for (int len = 1; len <= n && !ok; len++) {
      for (int l = 1; l + len - 1 <= n && !ok; l++) {
        int r = l + len - 1;
        int dsum = 0, lsum = 0, usum = 0;
        dsum = sum(digit_sum, n) - (sum(digit_sum, r) - sum(digit_sum, l-1));
        lsum = sum(lower_sum, n) - (sum(lower_sum, r) - sum(lower_sum, l-1));
        usum = sum(upper_sum, n) - (sum(upper_sum, r) - sum(upper_sum, l-1));
        int fix = (dsum == 0) + (lsum == 0) + (usum == 0);
        vector<char> fix_char;
        if (dsum == 0) {
          fix_char.push_back('0');
        }
        if (lsum == 0) {
          fix_char.push_back('a');
        }
        if (usum == 0) {
          fix_char.push_back('A');
        }
        if (fix <= len) {
          for (int i = 0; i < fix_char.size(); i++) {
            for (int j = l+i; j <= r; j++) {
              password[j] = fix_char[i];
            }
          }
          ok = true;
          for (int i = 1; i <= n; i++) {
            printf("%c", password[i]);
          }
          printf("\n");
        }
      }
    }
  }
  return 0;
}
